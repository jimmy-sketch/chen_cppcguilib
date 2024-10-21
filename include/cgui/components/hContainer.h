#pragma once
#include "component.h"
#include <vector>
#include <memory>

class hContainer : public component {
public:
    hContainer() = default;
    hContainer(std::initializer_list<std::shared_ptr<component>> initList);

    size_t getWidth() const override;
    size_t getHeight() const override;
    std::vector<cgui::string> getData() const override;

    void pushBack(std::shared_ptr<component> src);
    void insert(size_t index, std::shared_ptr<component> src);
    void erase(size_t index);
    void clear();

    std::shared_ptr<component>& operator[](size_t index);

private:
    std::vector<std::shared_ptr<component>> components;
};