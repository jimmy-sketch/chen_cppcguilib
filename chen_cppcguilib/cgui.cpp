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

page::page(bool enableSelect)
    : enableSelect(enableSelect)
{}

int page::getWeight() const
{
    int ret = 0;
    for (auto&& [_, w] : lineWidthList) {
        ret += w;
    }
    return ret;
}

int page::getHeight() const
{
    int ret = 0;
    for (auto&& [_, h] : lineHeightList) {
        ret += h;
    }
    return ret;
}

std::vector<cgui::string> page::getData() const
{
    std::vector<cgui::string> lines(getHeight() + 1);
    for (auto&& [pos, c] : components) {
        int height = c->getHeight();
        int width = c->getWidth();
        auto data = c->getData();

        int lineHeight = lineHeightList.at(pos.row);
        int lineWidth = lineWidthList.at(pos.col);

        int yOffset = 0;
        for (int i = 0; i < pos.row; ++i) {
            yOffset += lineHeightList.at(i);
        }

        for (int i = 0; i < height; ++i) {
            lines[yOffset + i] += data[i] + cgui::string(lineWidth - data[i].length(), ' ');
        }
        for (int i = height; i < lineHeight; ++i) {
            lines[yOffset + i] += cgui::string(lineWidth, ' ');
        }
    }
    return lines;
}

std::string page::toString()
{
    std::vector<cgui::string> lines;
    if (enableSelect) {
        std::shared_ptr<component> rawSelectedComponent = components[selectedPos];
        setTo(selectedPos, std::make_shared<basicImage>(addOutline(rawSelectedComponent)));
        lines = getData();
        erase(selectedPos);
        setTo(selectedPos, rawSelectedComponent);
    }
    else {
        lines = getData();
    }

    std::string ret = "";
    for (auto& line : lines) {
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

void page::setEnableSelect(bool v)
{
    enableSelect = v;
}

void page::select(logicPos pos)
{
    selectedPos = pos;
}
