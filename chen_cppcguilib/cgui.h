#pragma once
#include"basicImage.h"
#include"basicProgressBar.h"
#include"basicText.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

struct pos {
    int row, col;
};
static bool operator<(const pos& lhs, const pos& rhs) {
    return (lhs.row < rhs.row) || (lhs.row == rhs.row && lhs.col < rhs.col);
}

class page
{
public:
    //重要函数：刷新、呈现控件内容
    std::string summonFrame();
    void refreshScreen();

    //生成并放置控件
    template<class T, class...Args>
    std::shared_ptr<T> set(pos pos, Args...args)
    {
        auto ret = std::make_shared<T>(args...);
        components[pos] = ret;
        refreshScreen();
        return ret;
    }
    std::shared_ptr<basicImage> setImage(int row, int col, std::vector<std::string> imageByLine);
    std::shared_ptr<basicText> setText(int row, int col, std::string text);
    std::shared_ptr<basicProgressBar>  setProgressBar(int row, int col, int len);

    //把某个控件放到...
    void setTo(int row, int col, std::shared_ptr<component> src);

    //更改控件
    void  modifyImage(std::shared_ptr<basicImage> src, std::vector<std::string> imageByLine);
    void  modifyText(std::shared_ptr<basicText> src, std::string text);
    void  updateProgress(std::shared_ptr<basicProgressBar> src, int progress);

private:
    std::map<pos, std::shared_ptr<component>> components;
    // 获得组件上方一个组件的高
    int getUpperComponentHeight(const pos& current);
    // 获得组件上方所有组件的高的总和
    int getAboveComponentHeight(const pos& current);
    // 获得左边组件的宽
    int getLeftComponentWidth(const pos& current);
    // 获得左边所有低于自身组件的宽，碰到同行的也停止
    int getAllLeftComponentWidth(const pos& current, int row);
    // 获得左边组件的高
    int getLeftComponentHeight(const pos& current);
};