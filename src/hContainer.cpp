#include <cgui/components/hContainer.h>
#include <cgui/utils/config.h>

size_t hContainer::getWidth() const
{
    size_t ret = 0;
    for (auto&& c : components) {
        ret += c->getWidth();
    }
    return ret;
}

size_t hContainer::getHeight() const
{
    size_t ret = 0;
    for (auto&& c : components) {
        ret = std::max(ret, c->getHeight());
    }
    return ret;
}

std::vector<cgui::string> hContainer::getData() const
{
    std::vector<cgui::string> lines(getHeight() + 1);
    for (auto&& c : components) {
        size_t height = c->getHeight();
        size_t width = c->getWidth();
        auto data = c->getData();

        for (size_t i = 0; i < height; ++i) {
            lines[i].appendDirectly(data[i]);
            lines[i] += cgui::string(width - data[i].length(), cgui::getPaddingChar());
        }
        for (size_t i = height; i < getHeight(); ++i) {
            lines[i] += cgui::string(width, cgui::getPaddingChar());
        }
    }
    return lines;
}

hContainer::hContainer(std::initializer_list<std::shared_ptr<component>> initList) {
    for (auto& component : initList) {
        components.push_back(component);
    }
}

void hContainer::pushBack(std::shared_ptr<component> src) {
    components.push_back(src);
}

void hContainer::insert(size_t index, std::shared_ptr<component> src) {
    if (index <= components.size()) {
        components.insert(components.begin() + index, src);
    }
}

void hContainer::erase(size_t index) {
    if (index < components.size()) {
        components.erase(components.begin() + index);
    }
}

void hContainer::clear() {
    components.clear();
}

std::shared_ptr<component>& hContainer::operator[](size_t index)
{
    return components[index];
}
