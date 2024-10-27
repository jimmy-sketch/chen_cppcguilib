#pragma once
#include "component.h"

//多行文本相关类
class multiLineText : public component {
public:
    multiLineText(std::vector<cgui::string> textByLine);

    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;
    
    // 设置多行文本
    void setMultiText(std::vector<cgui::string> newTextByLine);
    // 添加新的行
    void pushBack(const cgui::string& newLine);
    
    cgui::string& operator[](size_t index);
    const cgui::string& operator[](size_t index) const;

private:
    std::vector<cgui::string> textByLine;
};
