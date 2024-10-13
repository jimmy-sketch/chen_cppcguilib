#pragma once
#include "components/component.h"
#include "logicPos.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

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
};