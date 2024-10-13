#pragma once
#include <vector>
#include <string>
#include "utils/string.h"

/*
* 所有组件的基类
* 
*/

class component
{
public:
    virtual size_t getWidth() const = 0;
    virtual size_t getHeight() const = 0;
    virtual std::vector<cgui::string> getData() const = 0;
};