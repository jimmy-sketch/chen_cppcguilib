#pragma once
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<climits>
#include<map>
using namespace std;

//一些重要函数……
__declspec(dllexport) void __stdcall refreshScreen();//最主要的函数，用于刷新屏幕，显示控件
	//重要：当前只支持简单堆叠，按先后顺序一个控件一行，所以所有的row和column会被忽
//数据结构

class basicThing //基本对象
{
public:
	basicThing() {};
	~basicThing() {};
	string __stdcall selfDraw() {};
	
private:
	
};

class basicText :public basicThing
{
public:
	__declspec(dllexport) __stdcall basicText(string text)
	{
		selfText = text;
	}
	__declspec(dllexport) void __stdcall updateText(string text)
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
	__declspec(dllexport) _stdcall basicImage(vector<string> _imageByLine)
	{
		imageByline = _imageByLine;
	}
	__declspec(dllexport) void __stdcall updateImage(vector<string> _imageByLine)
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
	 __declspec(dllexport) _stdcall basicProgressBar(int styles,int _length)
	{
		{};
		//样式部分：TODO

		progress = 0;
		length = _length;
	}
	__declspec(dllexport) void __stdcall updateProgress(int _progress)//范围：0-100
	{
		progress = _progress;
	}
	__declspec(dllexport) void __stdcall switchStyle(int styles)
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

__declspec(dllexport) basicText __stdcall createText(int row, int column, string text);
__declspec(dllexport) void __stdcall updateText(basicText& youwant, string text);

//2. 图片相关

__declspec(dllexport) basicImage __stdcall createImage(int row, int column, vector<string> image);
__declspec(dllexport) void __stdcall updateImage(basicImage& youwant, vector<string> image);

//3.进度条相关

__declspec(dllexport) basicProgressBar __stdcall createProgressBar(int row, int column, int length);
__declspec(dllexport) void __stdcall updateProgressBar(basicProgressBar& youwant, int progress);

//4.通用操作
	
template<typename T>
  void changeLocation(T& youwant);