#pragma once
#include "utils/string.h"
#include "component.h"

//多行文本相关类
class multiLineText : public component
{
public:
    multiLineText(std::vector<cgui::string> textByLine);
    int getWidth() const override;
    int getHeight() const override;
    std::vector<std::string> getData() const override;
    void setMultiText(std::vector<cgui::string> textByLine);

private:
    std::vector<cgui::string> textByLine;
    size_t calcuateLength() const;
};

