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
static bool operator==(logicPos lhs, logicPos rhs) {
    return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

class page // : public component
{
public:
    size_t getWeight() const;
    size_t getHeight() const;
    std::vector<cgui::string> getData() const;

    // 把page中的内容格式化为字符串
    std::string toString();
    
    // 打印page
    void update();

    // 把某个控件放到...
    void setTo(logicPos pos, std::shared_ptr<component> src);

    // 删除某个控件
    void erase(logicPos pos);

    // 清空控件
    void clear();

private:
    std::map<logicPos, std::shared_ptr<component>> components;
    std::map<int, size_t> lineWidthList;
    std::map<int, size_t> lineHeightList;
};