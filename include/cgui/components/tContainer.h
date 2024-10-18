#pragma once
#include "component.h"
#include "../utils/pos.h"
#include <vector>
#include <map>
#include <memory>

class tContainer : public component
{
public:
    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;

    void set(cgui::logicPos pos, std::shared_ptr<component> src);
    void erase(cgui::logicPos pos);
    void clear();

private:
    std::map<cgui::logicPos, std::shared_ptr<component>> components;
};
