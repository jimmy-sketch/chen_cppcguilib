#pragma once
#include<iostream>
#include "utils/string.h"
#include "component.h"

class basicText : public component
{
public:
    basicText(std::string_view str);
    int getWidth() const override;
    int getHeight() const override;
    std::vector<std::string> getData() const override;
    
    void setText(std::string_view str);

private:
    cgui::string text;
};
