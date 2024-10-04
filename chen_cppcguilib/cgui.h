#pragma once
#include<map>
#include"basicImage.h"
#include"basicProgressBar.h"
#include"basicText.h"
#include<iostream>
#include<algorithm>
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
basicImage*  createImage(int row, int column, vector<string> imageByLine);
basicText*  createText(int row, int column, string text);
basicProgressBar*  createProgressBar(int row, int column, int Length);
//更改控件
void  changeImage(basicImage* youwant, vector<string> imageByLine);
void  changeText(basicText* youwant, string text);
void  changeProgress(basicProgressBar* youwant, int progress);

//一些其他函数……
//排版相关
template<typename T> void changeLocation(thingType type, T* thing, int row, int column);