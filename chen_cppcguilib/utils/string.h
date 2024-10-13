#pragma once
#include <string>

namespace cgui {

// std::string造成的bug太多了，为了便于使用只好再封装一层
// 这个string是为了控制台ui所专门设计的
// 
// 功能如下：
// 
// length()返回可见字符数量
// size()返回全部字符数量
// 
// 解决Unicode字符占用长度和显示长度不一致问题
// 
// 可直接插入rgb，会自动转成ascii序列
// 末尾会自动恢复默认颜色
// 
// 不会包含换行符，\n会变成空格
// 
class string {
public:
    string();
    string(const char* in);
    string(std::string_view in);
    string(size_t count, char c);

    size_t size() const;
    size_t length() const;
    
    void insert(int pos, const string& other);
    void insert(int pos, int count, char c);

    void pushBackDefaultRGB();
    void insertDefaultRGB(int pos);
    void pushBackRGB(int r, int g, int b);
    void insertRGB(int pos, int r, int g, int b);
    void pushBackBackgroundRGB(int r, int g, int b);
    void insertBackgroundRGB(int pos, int r, int g, int b);
    
    string& operator+(const string& other);
    string& operator+(char other);
    void operator+=(const string& other);
    void operator+=(char other);
    void operator=(const string& other);
    void operator=(std::string_view other);

    const char* data() const;

private:
    std::string str;
    size_t visibleLength = 0;
    int colorCount = 0; // 用于颜色的ascii转义字符数量

    size_t pushBackPos() const; // 如果有颜色，pos会在最后一个恢复默认颜色之前
    void calculateVisibleLength();
};
string operator+(std::string_view lhs, string& rhs);
string operator+(std::string_view lhs, string&& rhs);

}