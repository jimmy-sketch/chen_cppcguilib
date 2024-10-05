#include"cgui.h"
#include <map>
using namespace std;

struct pos {
    int row, col;
};
static bool operator<(const pos& lhs, const pos& rhs) {
    return (lhs.row < rhs.row) || (lhs.row == rhs.row && lhs.col < rhs.col);
}
map<pos, shared_ptr<component>> components;

// 获得组件上方一个组件的高
static int getUpperComponentHeight(const pos& current) {
    pos upper = { current.row - 1, current.col };
    auto it = components.find(upper);
    if (it != components.end()) {
        return it->second->getHeight();
    }
    return 0;
}

// 获得组件上方所有组件的高的总和
static int getAboveComponentHeight(const pos& current) {
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

// 获得左边组件的宽
static int getLeftComponentWidth(const pos& current) {
    pos left = { current.row, current.col - 1 };
    auto it = components.find(left);
    if (it != components.end()) {
        return it->second->getWidth();
    }
    return 0;
}

// 获得左边组件的高
static int getLeftComponentHeight(const pos& current) {
    pos left = { current.row, current.col - 1 };
    auto it = components.find(left);
    if (it != components.end()) {
        return it->second->getHeight();
    }
    return 0;
}

// target的长度一直加到n
static void addNewLinesTo(vector<vector<string>>& target, int n) {
    if (n > target.size()) {
        for (int i = 0; i < n - target.size(); ++i) {
            target.emplace_back();
        }
    }
}

string summonFrame()
{
    vector<vector<string>> lines;
    for (auto& c : components) {
        int row = getAboveComponentHeight(c.first);
        addNewLinesTo(lines, row + 1);
        for (int l = 0; l < c.second->getHeight(); ++l) {
            addNewLinesTo(lines, row + l + 1);
            auto str = c.second->getData()[l];
            // 如果左边短，右边长，右边应该补齐一些空格
            // 同时也要注意，左右同时占行的部分中间不要加空格
            int h = getLeftComponentHeight(c.first);
            if (h != 0 && h < c.second->getHeight() && l >= h) {
                str.insert(0, getLeftComponentWidth(c.first), ' ');
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

void refreshScreen()
{
    system("cls");
    cout << summonFrame();
}

template<class T, class...Args>
shared_ptr<T> set(pos pos, Args...args)
{
    auto ret = make_shared<T>(args...);
    components[pos] = ret;
    refreshScreen();
    return ret;
}
shared_ptr<basicImage>  setImage(int row, int col, vector<string> imageByLine)  { return set<basicImage>({ row,col }, imageByLine); }
shared_ptr<basicText>  setText(int row, int col, string text)			    	{ return set<basicText>({ row,col }, text); }
shared_ptr<basicProgressBar>  setProgressBar(int row, int col, int len)		    { return set<basicProgressBar>({ row,col }, len, 0); }

void setTo(int row, int col, std::shared_ptr<component> src)
{
    components[{ row, col }] = src;
}

void modifyImage(shared_ptr<basicImage> target, vector<string> imageByLine)
{
    target->setImage(imageByLine);
    refreshScreen();
}
void modifyText(shared_ptr<basicText> target, string text)
{
    target->setText(text);
    refreshScreen();
}
void updateProgress(shared_ptr<basicProgressBar> target, int progress)
{
    target->updateProgress(progress);
    refreshScreen();
}