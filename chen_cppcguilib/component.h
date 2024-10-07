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
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual std::vector<cgui::string> getData() const = 0;
};