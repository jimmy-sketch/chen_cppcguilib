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
        addNewLinesTo(lines, row + 1);
        for (int l = 0; l < c.second->getHeight(); ++l) {
            addNewLinesTo(lines, row + l + 1);
            auto str = c.second->getData()[l];
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

void page::setTo(int row, int col, std::shared_ptr<component> src)
{
    components[{ row, col }] = src;
}

void page::clear()
{
    components.clear();
}

int page::getUpperComponentHeight(const pos& current) {
    pos upper = { current.row - 1, current.col };
    auto it = components.find(upper);
    if (it != components.end()) {
        return it->second->getHeight();
    }
    return 0;
}

int page::getAboveComponentHeight(const pos& current) {
    pos upper = current;
    int h = getUpperComponentHeight(upper);
    int ret = h;
    while (h != 0) {
        upper = { upper.row - 1, upper.col };
        h = getUpperComponentHeight(upper);
        ret += h;
    }
    return ret;
}

int page::getLeftComponentWidth(const pos& current) {
    pos left = { current.row, current.col - 1 };
    auto it = components.find(left);
    if (it != components.end()) {
        return it->second->getWidth();
    }
    return 0;
}

int page::getAllLeftComponentWidth(const pos& current, int row)
{
    pos left = current;
    int ret = 0;
    while (true) {
        int h = getLeftComponentHeight(left);
        if (h == 0 || row < h) {
            break;
        }
        left = { left.row, left.col - 1 };
        ret += components[left]->getWidth();
    }
    return ret;
}

int page::getLeftComponentHeight(const pos& current) {
    pos left = { current.row, current.col - 1 };
    auto it = components.find(left);
    if (it != components.end()) {
        return it->second->getHeight();
    }
    return 0;
}