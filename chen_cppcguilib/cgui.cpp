#include"cgui.h"
#include <iostream>

std::string page::toString()
{
    std::vector<std::vector<cgui::string>> lines;
    for (auto& [pos, c] : components) {
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

void page::clear()
{
    components.clear();
    lineHeightList.clear();
    lineWidthList.clear();
}
