#pragma once
#include"basicImage.h"
#include"basicProgressBar.h"
#include"basicText.h"
#include"multiLineText.h"
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
    std::string toString();
    void update();

    //把某个控件放到...
    void setTo(int row, int col, std::shared_ptr<component> src);

    //清空控件
    void clear();

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