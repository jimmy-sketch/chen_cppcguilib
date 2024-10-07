#pragma once
#include <string>
#include <regex>

namespace cgui {

// std::string造成的bug太多了，为了便于使用只好再封装一层
// 这个string是为了控制台ui所专门设计的
// 现有的代码并没有转用新string，以后会转成新string的
// 
// 功能如下：
// 
// length()返回可见字符数量
// size()返回全部字符数量
// 
// 解决Unicode字符占用长度和显示长度不一致问题
// 
// 可直接插入rgb，会自动转成ascii序列
// 
// 不会包含换行符，\n会变成空格
// 
class string {
public:
    string(const char* in);
    string(std::string_view in);
    string(int count, char c);

    size_t size() const;
    int length() const;
    
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

    const char* data() const;

private:
    std::string str;
    int visibleLength = 0;

    void calculateVisibleLength();
};

}