#pragma once
#include <string>

namespace cgui {

// 一个没有\n \t，结尾会自动添加“恢复默认颜色”的字符串
class string {
public:
    string();
    string(const char* in);
    string(std::string_view in);
    string(size_t count, char c);

    // 全部字符数量
    size_t size() const;
    // 可见字符的总宽度
    size_t length() const;
    // C风格字符串
    const char* data() const;
    
    // 追加字符串，会移除结尾的“恢复默认颜色”
    void append(const string& other);
    // 追加一个字符
    void pushBack(char other);
    // 插入字符串，会移除结尾的“恢复默认颜色”
    void insert(int pos, const string& other);
    // 插入一个字符
    void insert(int pos, int count, char c);
    // 追加字符串，不会移除结尾的“恢复默认颜色”
    void appendDirectly(const string& other);

    // 插入/添加颜色
    void pushBackDefaultRGB();
    void insertDefaultRGB(int pos);
    void pushBackRGB(int r, int g, int b);
    void insertRGB(int pos, int r, int g, int b);
    void pushBackBackgroundRGB(int r, int g, int b);
    void insertBackgroundRGB(int pos, int r, int g, int b);
    
    // 与append相同，会移除结尾的“恢复默认颜色”
    string operator+(const string& other);
    string operator+(char other);
    string& operator+=(const string& other);
    string& operator+=(char other);
    // 赋值给当前字符串
    string& operator=(const string& other);
    string& operator=(std::string_view other);

private:
    std::string str;
    size_t visibleLength = 0;

    // 返回末尾的“恢复默认颜色”的前面一个位置
    size_t pushBackPos() const;
    // 计算可见字符的宽度
    void calculateVisibleLength();
    // rgb转换为ANSI转义序列
    std::string colorAnsiEscapeCode(int mod, int r, int g, int b);
};
string operator+(std::string_view lhs, string& rhs);
string operator+(std::string_view lhs, string&& rhs);

}