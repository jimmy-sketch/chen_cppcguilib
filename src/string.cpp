#include <cgui/utils/string.h>
#include <cgui/utils/config.h>
#include <wtswidth.h>

static const std::string defaultColor = "\x1b[0m";

static size_t utf8CharSize(char firstByte) {
    if ((firstByte & 0x80) == 0x00) return 1;
    else if ((firstByte & 0xE0) == 0xC0) return 2;
    else if ((firstByte & 0xF0) == 0xE0) return 3;
    else if ((firstByte & 0xF8) == 0xF0) return 4;
    else return 0;
}

static size_t charSize(const char* src) {
    if (!src) {
        return 0;
    }
    if (src[0] == '\x1b') {
        size_t ret = 1;
        for (; src[ret] != 0; ++ret) {
            if (src[ret] == 'm') {
                return ret + 1;
            }
        }
        return ret;
    }
    size_t ret = 0;
    for (; (ret < utf8CharSize(src[0])) && (src[ret] != 0 && src[ret] != '\x1b'); ++ret);
    return ret;
}

static size_t charWidth(const char* src) {
    if (!src) {
        return 0;
    }
    if (src[0] == '\x1b') {
        return 0;
    }
    size_t ret = 0;
    for (; (ret < utf8CharSize(src[0])) && (src[ret] != 0 && src[ret] != '\x1b'); ++ret);
    return wts8width(src, ret);
}

cgui::Char::Char(const char* src)
    : p(src)
{}

size_t cgui::Char::getSize() const
{
    return charSize(p);
}

size_t cgui::Char::getWidth() const
{
    return charWidth(p);
}

cgui::string::string()
    : bytes(defaultColor)
{}

cgui::string::string(const char* in) 
    : bytes(in)
{
    bytes += defaultColor;
    removeBadChar();
    calculateWidth();
}

cgui::string::string(std::string_view in) 
    : string(in.data()) 
{}

cgui::string::string(size_t count, char c) 
    : string(std::string(count, c).data())
{}

size_t cgui::string::size() const 
{ 
    return bytes.size();
}

size_t cgui::string::length() const 
{ 
    return width; 
}

const char* cgui::string::data() const
{
    return bytes.data();
}

void cgui::string::append(const string& other)
{
    bytes.insert(pushBackPos(), other.bytes.substr(0, other.pushBackPos()));
    width += other.width;
}

void cgui::string::pushBack(char other)
{
    append(string(1, other));
}

void cgui::string::insert(size_t pos, const string& other)
{
    bytes.insert(pos, other.bytes.substr(0, other.pushBackPos()));
    width += other.width;
}

void cgui::string::insert(size_t pos, int count, char c)
{
    insert(pos, string(count, c));
}

void cgui::string::appendDirectly(const string& other)
{
    bytes.insert(pushBackPos(), other.bytes);
    width += other.width;
}

cgui::string cgui::string::take(size_t n) {
    auto it = begin();
    auto last = it;
    size_t currentWidth = 0;
    for (; (currentWidth < n) && (it != end()); ++it) {
        last = it;
        currentWidth += charWidth(it);
    }
    if (currentWidth == n) {
        return { std::string(begin().p, it.p).data() };
    }
    else if (currentWidth > n) {
        currentWidth -= charWidth(last);
    }
    std::string ret(begin().p, last.p);
    ret += std::string(n - currentWidth, cgui::getPaddingChar());
    return { ret.data() };
}

cgui::string cgui::string::takeComplete(size_t n)
{
    auto it = begin();
    auto last = it;
    size_t currentWidth = 0;
    for (; (currentWidth < n) && (it != end()); ++it) {
        last = it;
        currentWidth += charWidth(it);
    }
    if (currentWidth == n) {
        return { std::string(begin().p, it.p).data() };
    }
    else if (currentWidth > n) {
        currentWidth -= charWidth(last);
    }
    std::string ret(begin().p, last.p);
    ret += std::string(n - currentWidth, cgui::getPaddingChar());
    return { ret.data() };
}

void cgui::string::pushBackDefaultRGB() 
{
    append(defaultColor.data());
}

void cgui::string::pushBackRGB(int r, int g, int b) 
{
    append(colorAnsiEscapeCode(38, r, g, b).data());
}

void cgui::string::pushBackBackgroundRGB(int r, int g, int b)
{
    append(colorAnsiEscapeCode(48, r, g, b).data());
}

void cgui::string::insertDefaultRGB(size_t pos)
{
    insert(pos, defaultColor.data());
}

void cgui::string::insertRGB(size_t pos, int r, int g, int b)
{
    insert(pos, colorAnsiEscapeCode(38, r, g, b).data());
}

void cgui::string::insertBackgroundRGB(size_t pos, int r, int g, int b)
{
    insert(pos, colorAnsiEscapeCode(48, r, g, b).data());
}

cgui::string cgui::string::operator+(const string& other)
{
    string ret = *this;
    ret.append(other);
    return ret;
}

cgui::string cgui::string::operator+(char other)
{
    string ret = *this;
    ret.pushBack(other);
    return ret;
}

cgui::string& cgui::string::operator+=(const string& other) {
    append(other);
    return *this;
}

cgui::string& cgui::string::operator+=(char other)
{
    pushBack(other);
    return *this;
}

cgui::string& cgui::string::operator=(const string& other)
{
    bytes = other.bytes;
    width = other.width;
    return *this;
}

cgui::string& cgui::string::operator=(std::string_view other)
{
    return operator=(string(other));
}

cgui::string::iterator cgui::string::begin()
{
    return { bytes.data() };
}

cgui::string::iterator cgui::string::end()
{
    return { bytes.data() + bytes.size() };
}

size_t cgui::string::pushBackPos() const
{
     return bytes.end() - bytes.begin() - defaultColor.size();
}

void cgui::string::removeBadChar()
{
    for (auto& byte : bytes) {
        if (byte == '\n' || byte == '\t') {
            byte = ' ';
        }
    }
}

void cgui::string::calculateWidth()
{
    width = 0;
    for (auto c : *this) {
        width += c.getWidth();
    }
}

std::string cgui::string::colorAnsiEscapeCode(int mod, int r, int g, int b)
{
    return "\x1b[" + std::to_string(mod) + ";2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

cgui::string cgui::operator+(std::string_view lhs, string& rhs)
{
    return string(lhs) + rhs;
}

cgui::string cgui::operator+(std::string_view lhs, string&& rhs)
{
    return string(lhs) + rhs;
}

cgui::string::iterator& cgui::string::iterator::operator++()
{
    p += charSize(p);
    return *this;
}

bool cgui::string::iterator::operator==(const iterator& other) const
{
    return p == other.p;
}

cgui::Char cgui::string::iterator::operator*() const
{
    return Char(p);
}

cgui::string::iterator::operator char* ()
{
    return p;
}
