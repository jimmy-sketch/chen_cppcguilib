#include <cgui/utils/string.h>
#include <regex>

static const std::string defaultColor = "\x1b[0m";

cgui::string::string()
    : str(defaultColor)
{}

cgui::string::string(const char* in) 
    : str(in) 
{
    str += defaultColor;
    calculateVisibleLength();
}

cgui::string::string(std::string_view in) 
    : string(in.data()) 
{}

cgui::string::string(size_t count, char c) 
    : string(std::string(count, c).data())
{}

size_t cgui::string::size() const 
{ 
    return str.size();
}

size_t cgui::string::length() const 
{ 
    return visibleLength; 
}

const char* cgui::string::data() const
{
    return str.data();
}

void cgui::string::append(const string& other)
{
    str.insert(pushBackPos(), other.str.substr(0, other.pushBackPos()));
    visibleLength += other.visibleLength;
}

void cgui::string::pushBack(char other)
{
    append(string(1, other));
}

void cgui::string::insert(int pos, const string& other)
{
    str.insert(pos, other.str.substr(0, other.pushBackPos()));
    visibleLength += other.visibleLength;
}

void cgui::string::insert(int pos, int count, char c)
{
    insert(pos, string(count, c));
}

void cgui::string::appendDirectly(const string& other)
{
    str.insert(pushBackPos(), other.str);
    visibleLength += other.visibleLength;
}

void cgui::string::pushBackDefaultRGB() 
{
    append(defaultColor.data());
}

void cgui::string::insertDefaultRGB(int pos)
{
    insert(pos, defaultColor.data());
}

void cgui::string::pushBackRGB(int r, int g, int b) 
{
    append(colorAnsiEscapeCode(38, r, g, b).data());
}

void cgui::string::insertRGB(int pos, int r, int g, int b) 
{
    insert(pos, colorAnsiEscapeCode(38, r, g, b).data());
}

void cgui::string::pushBackBackgroundRGB(int r, int g, int b)
{
    append(colorAnsiEscapeCode(48, r, g, b).data());
}

void cgui::string::insertBackgroundRGB(int pos, int r, int g, int b)
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
    str = other.str;
    visibleLength = other.visibleLength;
    return *this;
}

cgui::string& cgui::string::operator=(std::string_view other)
{
    return operator=(string(other));
}

size_t cgui::string::pushBackPos() const
{
     return str.end() - str.begin() - defaultColor.size();
}

void cgui::string::calculateVisibleLength()
{
    visibleLength = 0;
    // 不能有\n \t
    for (auto& c : str) {
        if (c == '\n' || c == '\t') { c = ' '; }
    }
    // 移除ANSI转义序列
    std::regex ansiEscape(R"(\x1B\[[0-9;]*[A-Za-z])");
    std::string cleanLine = std::regex_replace(str, ansiEscape, "");
    // 处理unicode字符
    // todo
    visibleLength = cleanLine.size();
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
