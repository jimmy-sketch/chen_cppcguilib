#include"cgui.h"
using namespace std;

static void addNewLinesTo(vector<vector<string>>& target, int n) {
    if (n > target.size()) {
        for (int i = 0; i < n - target.size(); ++i) {
            target.emplace_back();
        }
    }
}

string page::toString()
{
    vector<vector<string>> lines;
    for (auto& c : components) {
        int row = getAboveComponentHeight(c.first);
        // 如果上方无组件，且不是这行的第一个组件，则与左边组件对齐
        if (row == 0 && c.first.row != 0 && c.first.col != 0) {
            auto left = findNearestComponent(c.first, 0, -1);
            if (!isBadLogicPos(left)) {
                row = getAboveComponentHeight(left);
            }
        }

        addNewLinesTo(lines, row + 1);
        for (int l = 0; l < c.second->getHeight(); ++l) {
            addNewLinesTo(lines, row + l + 1);
            string str = c.second->getData()[l];
            int h = getLeftComponentHeight(c.first);
            if (h != 0 && h < c.second->getHeight() && l >= h) {
                str.insert(0, getAllLeftComponentWidth(c.first, l), ' ');
            }
            lines[row + l].push_back(str);
        }
        // 以后加入组件间距
    }
    string ret = "";
    for (auto& line : lines) {
        for (auto& str : line) {
            ret += str;
        }
        ret += "\n";
    }
    return ret;
}

void page::update()
{
    system("cls");
    cout << toString();
}

void page::setTo(logicPos pos, std::shared_ptr<component> src)
{
    components[pos] = src;
}

void page::clear()
{
    components.clear();
}

int page::getUpperComponentHeight(logicPos current) {
    logicPos upper = { current.row - 1, current.col };
    auto it = components.find(upper);
    if (it != components.end()) {
        return it->second->getHeight();
    }
    return 0;
}

int page::getAboveComponentHeight(logicPos current) {
    logicPos upper = current;
    int h = getUpperComponentHeight(upper);
    int ret = h;
    while (h != 0) {
        upper = { upper.row - 1, upper.col };
        h = getUpperComponentHeight(upper);
        ret += h;
    }
    return ret;
}

int page::getLeftComponentWidth(logicPos current) {
    logicPos left = { current.row, current.col - 1 };
    auto it = components.find(left);
    if (it != components.end()) {
        return it->second->getWidth();
    }
    return 0;
}

int page::getAllLeftComponentWidth(logicPos current, int row)
{
    logicPos left = current;
    int ret = 0;
    while (true) {
        int h = getLeftComponentHeight(left);
        if (h == 0 || row < h) {
            break;
        }
        left.col -= 1;
        ret += components[left]->getWidth();
    }
    return ret;
}

int page::getLeftComponentHeight(logicPos current) {
    logicPos left = { current.row, current.col - 1 };
    auto it = components.find(left);
    if (it != components.end()) {
        return it->second->getHeight();
    }
    return 0;
}

logicPos page::findNearestComponent(logicPos current, int y, int x)
{
    logicPos iter = { current.row + y, current.col + x };
    while (!isBadLogicPos(iter)) {
        auto it = components.find(iter);
        if (it != components.end()) {
            return it->first;
        }
        iter = { iter.col + y, iter.row + x };
    }
    return { -1, -1 };
}

bool page::isBadLogicPos(logicPos pos)
{
    return !(pos.col >= 0 && pos.row >= 0 && pos.col < 99 && pos.row < 99);
}
