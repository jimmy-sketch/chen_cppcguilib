#pragma once
#include "component.h"
#include <vector>
#include <map>
#include <memory>

class hContainer : public component
{
public:
    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;

    void set(int col, std::shared_ptr<component> src);
    void erase(int col);
    void clear();

private:
    std::map<int, std::shared_ptr<component>> components;
};
