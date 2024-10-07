#include "string.h"
#include <regex>

using namespace cgui;

static const std::string defaultColor = "\033[0m";

string::string(const char* in) : str(in) { calculateVisibleLength(); }
string::string(std::string_view in) : str(in) { calculateVisibleLength(); }
string::string(int count, char c) : str(count, c) {}

size_t string::size() const { return str.size(); }
int string::length() const { return visibleLength; }

void string::insert(int pos, const string& other) {
    str.insert(pos, other.str);
    visibleLength += other.visibleLength;
}
void string::insert(int pos, int count, char c) {
    str.insert(pos, count, c);
}

void string::pushBackDefaultRGB() {
    str.insert(pushBackPos(), defaultColor);
}
void cgui::string::insertDefaultRGB(int pos)
{
    str.insert(pos, defaultColor);
}
void string::pushBackRGB(int r, int g, int b) {
    str.insert(pushBackPos(), "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
    ++colorCount;
    if (colorCount == 1) { str += defaultColor; }
}
void string::insertRGB(int pos, int r, int g, int b) {
    str.insert(pos, "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
    ++colorCount;
    if (colorCount == 1) { str += defaultColor; }
}
void cgui::string::pushBackBackgroundRGB(int r, int g, int b)
{
    str.insert(pushBackPos(), "\x1b[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
    ++colorCount;
    if (colorCount == 1) { str += defaultColor; }
}
void cgui::string::insertBackgroundRGB(int pos, int r, int g, int b)
{
    str.insert(pos, "\x1b[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
    ++colorCount;
    if (colorCount == 1) { str += defaultColor; }
}

string& string::operator+(const string& other) {
    str.insert(pushBackPos(), other.str);
    visibleLength += other.visibleLength;
    return *this;
}
string& cgui::string::operator+(char other)
{
    str.insert(pushBackPos(), 1, other);
    visibleLength += 1;
    return *this;
}
void string::operator+=(const string& other) {
    str.insert(pushBackPos(), other.str);
    visibleLength += other.visibleLength;
}
void cgui::string::operator+=(char other)
{
    str.insert(pushBackPos(), 1, other);
    visibleLength += 1;
}

const char* cgui::string::data() const
{
    return str.data();
}

int cgui::string::pushBackPos() const
{
    if (colorCount == 0) {
        return str.end() - str.begin();
    }
    else {
        return str.end() - str.begin() - defaultColor.size();
    }
}

void string::calculateVisibleLength() {
    visibleLength = 0;
    // 不能有换行符
    for (auto& c : str) {
        if (c == '\n') { c = ' '; }
    }
    // 移除ANSI转义序列
    std::regex ansiEscape(R"(\x1B\[[0-9;]*[A-Za-z])");
    std::string cleanLine = std::regex_replace(str, ansiEscape, "");
    // 处理unicode字符
    // todo
    visibleLength = cleanLine.size();
}