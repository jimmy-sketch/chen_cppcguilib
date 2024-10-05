#pragma once
#include<string>
#include<vector>
#include "component.h"

class basicImage : public component
{
public:
    basicImage(const std::vector<std::string>& image);
    int getWidth() const override;
    int getHeight() const override;
    std::vector<std::string> getData() const override;
    
    void setImage(const std::vector<std::string>& image);

private:
    std::vector<std::string> image;
    size_t width;
    void checkImage();
    void calculateWidth();
};
