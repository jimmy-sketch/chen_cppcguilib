#include <cgui/components/hContainer.h>
#include <cgui/utils/config.h>

size_t hContainer::getWidth() const
{
    size_t ret = 0;
    for (auto&& [_, c] : components) {
        ret += c->getWidth();
    }
    return ret;
}

size_t hContainer::getHeight() const
{
    size_t ret = 0;
    for (auto&& [_, c] : components) {
        ret = std::max(ret, c->getHeight());
    }
    return ret;
}

std::vector<cgui::string> hContainer::getData() const
{
    std::vector<cgui::string> lines(getHeight() + 1);
    for (auto&& [_, c] : components) {
        size_t height = c->getHeight();
        size_t width = c->getWidth();
        auto data = c->getData();

        for (size_t i = 0; i < height; ++i) {
            lines[i] += data[i] + cgui::string(width - data[i].length(), cgui::paddingChar);
        }
        for (size_t i = height; i < getHeight(); ++i) {
            lines[i] += cgui::string(width, cgui::paddingChar);
        }
    }
    return lines;
}

void hContainer::set(int col, std::shared_ptr<component> src)
{
    components[col] = src;
}

void hContainer::erase(int col)
{
    components.erase(col);
}

void hContainer::clear()
{
    components.clear();
}
