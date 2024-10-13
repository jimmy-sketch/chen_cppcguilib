#pragma once
#include "component.h"

class basicText : public component
{
public:
    basicText(std::string_view str);
    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;
    
    void setText(std::string_view str);

private:
    cgui::string text;
};
