#pragma once
#include "components/tContainer.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class page
{
public:
    size_t getWidth() const;
    size_t getHeight() const;
    std::vector<cgui::string> getData() const;

    // 把page中的内容格式化为字符串
    std::string toString() const;

    // 打印page
    void update() const;

    // 把某个控件放到...
    void set(cgui::logicPos pos, std::shared_ptr<component> src);

    // 删除某个控件
    void erase(cgui::logicPos pos);

    // 清空控件
    void clear();

private:
    tContainer table;
};