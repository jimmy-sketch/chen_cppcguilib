#include <cgui/components/vContainer.h>
#include <cgui/utils/config.h>

size_t vContainer::getWidth() const
{
    size_t ret = 0;
    for (auto&& c : components) {
        ret = std::max(ret, c->getWidth());
    }
    return ret;
}

size_t vContainer::getHeight() const
{
    size_t ret = 0;
    for (auto&& c : components) {
        ret += c->getHeight();
    }
    return ret;
}

std::vector<cgui::string> vContainer::getData() const
{
    std::vector<cgui::string> lines(getHeight());
    size_t row = 0;
    for (auto&& c : components) {
        size_t height = c->getHeight();
        size_t width = c->getWidth();
        auto data = c->getData();

        size_t yOffset = 0;
        for (int i = 0; i < row; ++i) {
            yOffset += components.at(i)->getHeight();
        }

        for (size_t i = 0; i < height; ++i) {
            lines[yOffset + i].appendDirectly(data[i]);
            lines[yOffset + i] += cgui::string(getWidth() - data[i].getWidth(), cgui::getPaddingChar());
        }
        row += 1;
    }
    return lines;
}

vContainer::vContainer(std::initializer_list<std::shared_ptr<component>> initList) {
    for (auto& component : initList) {
        components.push_back(component);
    }
}

void vContainer::pushBack(std::shared_ptr<component> src) {
    components.push_back(src);
}

void vContainer::insert(size_t index, std::shared_ptr<component> src) {
    if (index <= components.size()) {
        components.insert(components.begin() + index, src);
    }
}

void vContainer::erase(size_t index) {
    if (index < components.size()) {
        components.erase(components.begin() + index);
    }
}

void vContainer::clear() {
    components.clear();
}

std::shared_ptr<component>& vContainer::operator[](size_t index)
{
    return components[index];
}
