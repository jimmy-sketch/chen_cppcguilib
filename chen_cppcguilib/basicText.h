#pragma once
#include<iostream>
#include<string>
#include "component.h"

class basicText : public component
{
public:
    basicText(const std::string& str);
    int getWidth() const override;
    int getHeight() const override;
    std::vector<std::string> getData() const override;
    
    void setText(const std::string& str);

private:
    std::string text;
    size_t width;
    void checkText();
    void calculateWidth();
};
