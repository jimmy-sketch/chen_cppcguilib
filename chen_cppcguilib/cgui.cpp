#include"cgui.h"
#include <iostream>

static std::vector<cgui::string> outlineComponent(std::shared_ptr<component> c) {
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

std::string page::toString()
{
    std::vector<std::vector<cgui::string>> lines;

    if (enableSelect) {
        lineHeightList[selectedPos.row] = std::max(lineHeightList[selectedPos.row], components[selectedPos]->getHeight() + 2);
        lineWidthList[selectedPos.col] = std::max(lineWidthList[selectedPos.col], components[selectedPos]->getWidth() + 2);
    }

    for (auto [pos, c] : components) {
        if (enableSelect && pos == selectedPos) {
            c = std::make_shared<basicImage>(outlineComponent(c));
        }

        int height = c->getHeight();
        int width = c->getWidth();
        auto data = c->getData();

        int lineHeight = lineHeightList[pos.row];
        int lineWidth = lineWidthList[pos.col];

        int yOffset = 0;
        for (int i = pos.row; i > 0; --i) {
            yOffset += lineHeightList[i-1];
        }

        if (yOffset + lineHeight + 1 > lines.size()) {
            lines.resize(yOffset + lineHeight + 1);
        }

        for (int i = 0; i < lineHeight; ++i) {
            if (i < height) {
                data[i] += cgui::string(lineWidth - data[i].length(), ' ');
                lines[yOffset + i].push_back(data[i]);
            }
            else {
                lines[yOffset + i].push_back(cgui::string(lineWidth, ' '));
            }
        }
    }

    if (enableSelect) {
        lineHeightList[selectedPos.row] = 0;
        lineWidthList[selectedPos.col] = 0;
        for (auto& [p, c] : components) {
            if (p.col == selectedPos.col) {
                lineWidthList[selectedPos.col] = std::max(lineWidthList[selectedPos.col], c->getWidth());
            }
            if (p.row == selectedPos.row) {
                lineHeightList[selectedPos.row] = std::max(lineHeightList[selectedPos.row], c->getHeight());
            }
        }
    }

    std::string ret = "";
    for (auto& line : lines) {
        for (auto& str : line) {
            ret += str.data();
        }
        ret += "\n";
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
