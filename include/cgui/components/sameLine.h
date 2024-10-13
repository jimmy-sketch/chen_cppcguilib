#pragma once
#include "component.h"
#include <vector>
#include <map>
#include <memory>

class sameLine : public component
{
public:
    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;

    void setTo(int col, std::shared_ptr<component> src);

private:
    std::map<int, std::shared_ptr<component>> components;
    size_t lineHeight = 0;
};
