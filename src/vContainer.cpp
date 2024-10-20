#include <cgui/components/vContainer.h>
#include <cgui/utils/config.h>

size_t vContainer::getWidth() const
{
    size_t ret = 0;
    for (auto&& [_, c] : components) {
        ret = std::max(ret, c->getWidth());
    }
    return ret;
}

size_t vContainer::getHeight() const
{
    size_t ret = 0;
    for (auto&& [_, c] : components) {
        ret += c->getHeight();
    }
    return ret;
}

std::vector<cgui::string> vContainer::getData() const
{
    std::vector<cgui::string> lines(getHeight() + 1);
    for (auto&& [row, c] : components) {
        size_t height = c->getHeight();
        size_t width = c->getWidth();
        auto data = c->getData();

        size_t yOffset = 0;
        for (int i = 0; i < row; ++i) {
            if (components.find(i) != components.end()) {
                yOffset += components.at(i)->getHeight();
            }
        }

        for (size_t i = 0; i < height; ++i) {
            lines[yOffset + i].appendDirectly(data[i]);
            lines[yOffset + i] += cgui::string(getWidth() - data[i].length(), cgui::getPaddingChar());
        }
    }
    return lines;
}

void vContainer::set(int row, std::shared_ptr<component> src)
{
    components[row] = src;
}

void vContainer::erase(int row)
{
    components.erase(row);
}

void vContainer::clear()
{
    components.clear();
}