#pragma once
#include "component.h"
#include<vector>
#include "cgui/utils/string.h"
#include "cgui/utils/pos.h"

enum colors { black = 40, red, green, yellow, blue, lime, cyan };
enum LayoutType{stack,tile};//表示窗口布局方式：层叠/平铺（未实现）

class window :public component //一个窗口
{
	window(size_t weight, size_t height);
	window(size_t weight, size_t height, std::initializer_list<component> initList);
	

	std::vector<cgui::string> getData();
	size_t getWidth() const;
	size_t getHeight() const;
};

class windowScreen : public component //窗口的“显示屏”（也是一个容器）
{
public:
	windowScreen(size_t weight, size_t height);

	void addWindow(window& window, cgui::logicPos pos);
	void clearWindow();
	void changeWindowShadow(bool type);
	void changeLayout(LayoutType type);//TODO，layout相关功能
	void deleteWindow(window& what);
	void setBgColor(colors bgcolor);//支持颜色：黑红绿黄蓝紫青

	std::vector<cgui::string> getData();
	size_t getWidth() const;
	size_t getHeight() const;
};