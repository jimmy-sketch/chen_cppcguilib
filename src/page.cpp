#include <cgui/page.h>
#include <iostream>

static std::vector<cgui::string> addOutline(std::shared_ptr<component> c) {
    std::vector<cgui::string> ret;
    ret.push_back("+" + cgui::string(c->getWidth(), '-') + "+");
    for (auto& line : c->getData()) {
        ret.push_back("|" + line + "|");
    }
    ret.push_back("+" + cgui::string(c->getWidth(), '-') + "+");
    return ret;
}

size_t page::getWeight() const
{
    size_t ret = 0;
    for (auto&& [_, c] : components) {
        ret += c->getWidth();
    }
    return ret;
}

size_t page::getHeight() const
{
    size_t ret = 0;
    for (auto&& [_, c] : components) {
        ret += c->getHeight();
    }
    return ret;
}

std::vector<cgui::string> page::getData() const
{
    std::vector<cgui::string> lines(getHeight() + 1);
    std::map<int, size_t> lineWidthList;
    std::map<int, size_t> lineHeightList;
    for (auto& [p, c] : components) {
        lineWidthList[p.col] = std::max(lineWidthList[p.col], c->getWidth());
        lineHeightList[p.row] = std::max(lineHeightList[p.row], c->getHeight());
    }
    for (auto&& [pos, c] : components) {
        size_t height = c->getHeight();
        size_t width = c->getWidth();
        auto data = c->getData();

        size_t lineHeight = lineHeightList.at(pos.row);
        size_t lineWidth = lineWidthList.at(pos.col);

        size_t yOffset = 0;
        for (int i = 0; i < pos.row; ++i) {
            if (lineHeightList.find(i) != lineHeightList.end()) {
                yOffset += lineHeightList.at(i);
            }
        }

        for (size_t i = 0; i < height; ++i) {
            lines[yOffset + i] += data[i] + cgui::string(lineWidth - data[i].length(), ' ');
        }
        for (size_t i = height; i < lineHeight; ++i) {
            lines[yOffset + i] += cgui::string(lineWidth, ' ');
        }
    }
    return lines;
}

std::string page::toString()
{
    std::string ret = "";
    for (auto& line : getData()) {
        ret += std::string(line.data()) + "\n";
    }
    return ret;
}

void page::update()
{
    system("cls");
    std::cout << toString();
}

void page::setTo(logicPos pos, std::shared_ptr<component> src)
{
    components[pos] = src;
}

void page::erase(logicPos pos)
{
    components.erase(pos);
}

void page::clear()
{
    components.clear();
}
