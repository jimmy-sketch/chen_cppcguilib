#pragma once
#include<vector>
#include "component.h"

class basicImage : public component
{
public:
    basicImage(const std::vector<cgui::string>& image);
    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;
    
    void setImage(const std::vector<cgui::string>& image);

private:
    std::vector<cgui::string> image;
    size_t width;
    void calculateWidth();
};
