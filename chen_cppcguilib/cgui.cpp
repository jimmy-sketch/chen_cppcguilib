#include"cgui.h"
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
    for (auto&& [_, w] : lineWidthList) {
        ret += w;
    }
    return ret;
}

size_t page::getHeight() const
{
    size_t ret = 0;
    for (auto&& [_, h] : lineHeightList) {
        ret += h;
    }
    return ret;
}

std::vector<cgui::string> page::getData() const
{
    std::vector<cgui::string> lines(getHeight() + 1);
    for (auto&& [pos, c] : components) {
        size_t height = c->getHeight();
        size_t width = c->getWidth();
        auto data = c->getData();

        size_t lineHeight = lineHeightList.at(pos.row);
        size_t lineWidth = lineWidthList.at(pos.col);

        size_t yOffset = 0;
        for (int i = 0; i < pos.row; ++i) {
            yOffset += lineHeightList.at(i);
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
    lineWidthList[pos.col] = std::max(lineWidthList[pos.col], src->getWidth());
    lineHeightList[pos.row] = std::max(lineHeightList[pos.row], src->getHeight());
}

void page::erase(logicPos pos)
{
    components.erase(pos);
    lineWidthList[pos.col] = 0;
    lineHeightList[pos.row] = 0;
    for (auto& [p, c] : components) {
        if (p.col == pos.col) {
            lineWidthList[pos.col] = std::max(lineWidthList[pos.col], c->getWidth());
        }
        if (p.row == pos.row) {
            lineHeightList[pos.row] = std::max(lineHeightList[pos.row], c->getHeight());
        }
    }
}

void page::clear()
{
    components.clear();
    lineHeightList.clear();
    lineWidthList.clear();
}
