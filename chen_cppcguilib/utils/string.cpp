#include "string.h"

using namespace cgui;

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

void string::pushBackRGB(int r, int g, int b) {
    str += "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}
void string::insertRGB(int pos, int r, int g, int b) {
    str.insert(pos, "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
}

string& string::operator+(const string& other) {
    str += other.str;
    visibleLength += other.visibleLength;
    return *this;
}
void string::operator+=(const string& other) {
    str += other.str;
    visibleLength += other.visibleLength;
}

cgui::string::operator const std::string&()
{
    return str;
}

void string::calculateVisibleLength() {
    visibleLength = 0;
    // 不能有换行符
    for (auto& c : str) {
        if (c == '\n') { c == ' '; }
    }
    // 移除ANSI转义序列
    std::regex ansiEscape(R"(\x1B\[[0-9;]*[A-Za-z])");
    std::string cleanLine = std::regex_replace(str, ansiEscape, "");
    // 处理unicode字符
    
}