#pragma once
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<climits>
#include<map>
using namespace std;

//一些重要函数……

void refreshScreen();//最主要的函数，用于刷新屏幕，显示控件
//重要：当前只支持简单堆叠，按先后顺序一个控件一行，所以所有的row和column会被忽略

//数据结构

class basicThing //基本对象
{
public:
	basicThing();
	~basicThing();
	string selfDraw();
	
private:
	
};

class basicText :public basicThing
{
public:
	basicText(string text)
	{
		selfText = text;
	}
	void updateText(string text)
	{
		selfText = text;
	}
	string selfDraw()
	{
		return selfText;
	}
private:
	string selfText;
};

class basicImage:public basicThing
{
public:
	basicImage(vector<string> _imageByLine)
	{
		imageByline = _imageByLine;
	}
	void updateImage(vector<string> _imageByLine)
	{
		imageByline = _imageByLine;
	}
	string selfDraw()
	{
		string lastString = "";
		for (auto kv : imageByline)
		{
			lastString += kv;
			lastString += "\n";
		}
		return lastString;
	}
private:
	vector<string> imageByline;
};

class basicProgressBar :public basicThing
{
public:
	basicProgressBar(int styles,int _length)
	{
		{};
		//样式部分：TODO

		progress = 0;
		length = _length;
	}
	void updateProgress(int _progress)//范围：0-100
	{
		progress = _progress;
	}
	void switchStyle(int styles)
	{
		//TODO
	}
	string selfDraw()
	{
		char beginChar = '[', endChar = ']', fillChar = '=', progressChar = '>', blankChar = ' ';
		//下方是样式部分,TODO
		{};
		//具体的显示
		string result = "";
		result += beginChar;
		result += to_string(progress);
		result += "%";
		for (double i = 1; i < length * (1.0 * progress / 100.0); i += 1)
			result += fillChar;
		if (progress == 100)
			result = result + fillChar + endChar;
		else
		{
			result = result + ">";
			for (double i = 1; i < length * (1.0 * (100-progress) / 100.0); i += 1)
				result += blankChar;
			result += endChar;
		}
		return result;
	}
private:
	int progress;
	int style=-1;
	int length;//进度条的长度,单位：字符；不包括头尾
};


//一些不那么重要的……

//1. 文字相关

basicText createText(int row, int column, string text);
void updateText(basicText& youwant, string text);

//2. 图片相关

basicImage createImage(int row, int column, vector<string> image);
void updateImage(basicImage& youwant,vector<string> image);

//3.进度条相关

basicImage createProgressBar(int row, int column);
void updateProgressBar(basicProgressBar& youwant, int progress);

//4.通用操作

template<typename T>
void changeLocation(T& youwant);