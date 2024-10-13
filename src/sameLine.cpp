#include <cgui/components/sameLine.h>

size_t sameLine::getWidth() const
{
    size_t ret = 0;
    for (auto&& [_, c] : components) {
        ret += c->getWidth();
    }
    return ret;
}

size_t sameLine::getHeight() const
{
    return lineHeight;
}

std::vector<cgui::string> sameLine::getData() const
{
    std::vector<cgui::string> lines(getHeight() + 1);
    for (auto&& [_, c] : components) {
        size_t height = c->getHeight();
        size_t width = c->getWidth();
        auto data = c->getData();

        for (size_t i = 0; i < height; ++i) {
            lines[i] += data[i] + cgui::string(width - data[i].length(), ' ');
        }
        for (size_t i = height; i < lineHeight; ++i) {
            lines[i] += cgui::string(width, ' ');
        }
    }
    return lines;
}

void sameLine::setTo(int col, std::shared_ptr<component> src)
{
    components[col] = src;
    lineHeight = std::max(lineHeight, src->getHeight());
}
