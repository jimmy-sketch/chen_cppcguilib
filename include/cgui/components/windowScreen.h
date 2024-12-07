#pragma once
#include "component.h"
#include<vector>
#include "cgui/utils/string.h"
#include "cgui/utils/pos.h"

enum windowColors { black = 40, red, green, yellow, blue, lime, cyan };
enum LayoutType{stack,tile};//表示窗口布局方式：层叠/平铺（未实现）

class window :public component //一个窗口
{
public:
	window(size_t weight, size_t height);
	window(size_t weight, size_t height, std::initializer_list<component> initList);

	void addComponent(component& what, cgui::logicPos pos);
	void setWindowColor(windowColors color);
	void resizeWindow(size_t weight, size_t height);
	void clearWindow();

	std::vector<cgui::string> getData() const override;
	size_t getWidth() const override;
	size_t getHeight() const override;
private:
	std::vector<cgui::string> data;
};

class windowScreen : public component //窗口的“显示屏”（也是一个容器）
{
public:
	windowScreen(size_t weight, size_t height);

	void addWindow(window& window, cgui::logicPos pos);
	void clearScreen();
	void changeWindowShadow(bool type);
	void changeLayout(LayoutType type);//TODO，layout相关功能
	void setBgColor(windowColors bgcolor);//支持颜色：黑红绿黄蓝紫青
	void resizeWindow(size_t weight, size_t height);

	std::vector<cgui::string> getData() const override;
	size_t getWidth() const override;
	size_t getHeight() const override;
};