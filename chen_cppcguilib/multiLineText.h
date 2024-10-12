#pragma once
#include "component.h"

//多行文本相关类
class multiLineText : public component
{
public:
    multiLineText(std::vector<cgui::string> textByLine);
    int getWidth() const override;
    int getHeight() const override;
    std::vector<cgui::string> getData() const override;
    void setMultiText(std::vector<cgui::string> textByLine);

private:
    std::vector<cgui::string> textByLine;
    int calcuateLength() const;
};

