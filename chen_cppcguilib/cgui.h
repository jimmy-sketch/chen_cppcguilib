#pragma once
#include"basicImage.h"
#include"basicProgressBar.h"
#include"basicText.h"
#include<algorithm>
#include<iostream>
#include<map>
#include <memory>
using namespace std;

enum thingType{image,text,progressBar};

struct thingMapper
{
	pair<int, thingType> mapper;
	int row, column;
	thingMapper(pair<int, thingType> x, int row, int column);
};
//typedef pair<int, thingType> thingMapper;
//first代表这一个控件在单独的控件列表中的下标

//重要函数：刷新、呈现控件内容
string summonFrame();
void refreshScreen();


//创建控件
std::shared_ptr<basicImage>  createImage(int row, int column, vector<string> imageByLine);
std::shared_ptr<basicText>   createText(int row, int column, string text);
std::shared_ptr<basicProgressBar>  createProgressBar(int row, int column, int Length);
//更改控件
void  changeImage(std::shared_ptr<basicImage> youwant, vector<string> imageByLine);
void  changeText(std::shared_ptr<basicText> youwant, string text);
void  changeProgress(std::shared_ptr<basicProgressBar> youwant, int progress);

//一些其他函数……
//排版相关
template<typename T> void changeLocation(thingType type, T* thing, int row, int column);