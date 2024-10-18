#pragma once
#include "component.h"
#include <vector>
#include <map>
#include <memory>

class vContainer : public component
{
public:
    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;

    void set(int row, std::shared_ptr<component> src);
    void erase(int row);
    void clear();

private:
    std::map<int, std::shared_ptr<component>> components;
};
