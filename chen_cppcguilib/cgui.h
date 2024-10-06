#pragma once
#include"basicImage.h"
#include"basicProgressBar.h"
#include"basicText.h"
#include"multiLineText.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

struct logicPos {
    int row, col;
};
static bool operator<(logicPos lhs, logicPos rhs) {
    return (lhs.row < rhs.row) || (lhs.row == rhs.row && lhs.col < rhs.col);
}

class page
{
public:
    //重要函数：刷新、呈现控件内容
    std::string toString();
    void update();

    //把某个控件放到...
    void setTo(logicPos pos, std::shared_ptr<component> src);

    //清空控件
    void clear();

private:
    std::map<logicPos, std::shared_ptr<component>> components;
    // 获得组件上方一个组件的高
    int getUpperComponentHeight(logicPos current);
    // 获得组件上方所有组件的高的总和
    int getAboveComponentHeight(logicPos current);
    // 获得左边组件的宽
    int getLeftComponentWidth(logicPos current);
    // 获得左边所有低于自身组件的宽，碰到同行的也停止
    int getAllLeftComponentWidth(logicPos current, int row);
    // 获得左边组件的高
    int getLeftComponentHeight(logicPos current);
    // 找最近的存在的组件，y表示每次向下走格数，x表示每次向右走格数，可以为负，有则返回位置，无则返回-1,-1
    logicPos findNearestComponent(logicPos current, int y, int x);
    // 判断位置是不是不合理的
    bool isBadLogicPos(logicPos pos);
};