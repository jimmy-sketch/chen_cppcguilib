#pragma once
#include "component.h"
class multiLineText :
    public component
{
public:
    multiLineText(std::vector<std::string> textByLine);
    int getWidth() const override;
    int getHeight() const override;
    std::vector<std::string> getData() const override;
    void setMultiText(std::vector<std::string> textByLine);
private:
    std::vector<std::string> textByLine;
    size_t calcuateLength() const;
};

