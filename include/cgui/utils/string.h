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

    // 字符串占用的字节数
    size_t getSize() const;
    // 字符串的宽度
    size_t getWidth() const;
    // C风格字符串
    const char* getData() const;
    
    // 追加字符串，会移除结尾的“恢复默认颜色”
    void append(const string& other);
    // 追加一个字符
    void pushBack(char other);
    // 插入字符串，会移除结尾的“恢复默认颜色”
    void insert(size_t pos, const string& other);
    // 插入一个字符
    void insert(size_t pos, int count, char c);
    // 追加字符串，不会移除结尾的“恢复默认颜色”
    void appendDirectly(const string& other);
    // 从头开始，获取一个宽度为n的子字符串
    // 如果宽度w处截断了某个UTF-8字符，会把这个字符转化为一些peddingChar，保证宽度w
    string take(size_t w) const;
    // 从头开始，获取一个宽度为n的子字符串
    // 如果宽度w处截断了某个UTF-8字符，会补全这个字符，尽管这样会超过宽度w
    string takeComplete(size_t w) const;

    // 追加颜色
    void pushBackDefaultRGB();
    void pushBackRGB(int r, int g, int b);
    void pushBackBackgroundRGB(int r, int g, int b);
    // 插入颜色
    void insertDefaultRGB(size_t pos);
    void insertRGB(size_t pos, int r, int g, int b);
    void insertBackgroundRGB(size_t pos, int r, int g, int b);
    
    // 与append相同，会移除结尾的“恢复默认颜色”
    string operator+(const string& other);
    string operator+(char other);
    string& operator+=(const string& other);
    string& operator+=(char other);
    // 赋值给当前字符串
    string& operator=(const string& other);
    string& operator=(std::string_view other);

    // 迭代器
    struct iterator {
        iterator& operator++();
        bool operator==(const iterator& other) const;
        char* operator*();
        operator char* ();

        char* p; // => cgui::string::bytes
    };
    struct constIterator {
        constIterator& operator++();
        bool operator==(const constIterator& other) const;
        const char* operator*() const;
        operator const char* () const;

        const char* p; // => cgui::string::bytes
    };
    iterator begin();
    iterator end();
    constIterator begin() const;
    constIterator end() const;

private:
    std::string bytes;
    size_t width = 0;

    // 返回末尾的“恢复默认颜色”的前面一个位置
    size_t pushBackPos() const;
    // 移除\n \t
    void removeBadChar();
    // 计算可见字符的宽度
    void calculateWidth();
    // rgb转换为ANSI转义序列
    std::string colorAnsiEscapeCode(int mod, int r, int g, int b);
};
string operator+(std::string_view lhs, string& rhs);
string operator+(std::string_view lhs, string&& rhs);

}