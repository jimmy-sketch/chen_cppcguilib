#include"cgui.h"
using namespace std;

enum thingType { text, image, progressbar };
typedef pair<int, thingType> thingmapper;

extern vector<thingmapper> mapAllOfThings;
extern vector<basicText> allOfText;
extern vector<basicImage> allOfImage;
extern vector<basicProgressBar> allOfBars;

__declspec(dllexport) basicText __stdcall createText(int row, int column, string _text)
{
	//创建一个文本控件
	// TODO:加入排版
	//1.先在控件总列表中分配一个位置
	thingmapper tmp = make_pair(allOfText.size(), text);
	mapAllOfThings.push_back(tmp);
	//2.构造控件，将其放入文本控件列表中
	basicText ret(_text);
	allOfText.push_back(ret);
	//3.刷新屏幕
	refreshScreen();
	//4.返回对象
	return ret;
}

__declspec(dllexport) void __stdcall updateText(basicText& youwant, string _text)
{
	youwant.updateText(_text);
	refreshScreen();
	return;
}

__declspec(dllexport) basicImage __stdcall createImage(int row, int column, vector<string> images)
{
	//TODO:加入排版
	//流程同createText
	thingmapper tmp = make_pair(allOfImage.size(), image);
	mapAllOfThings.push_back(tmp);
	basicImage ret(images);
	allOfImage.push_back(images);
	refreshScreen();
	return ret;
}

 __declspec(dllexport) void __stdcall updateImage(basicImage& youwant, vector<string> images)
{
	youwant.updateImage(images);
	refreshScreen();
}

__declspec(dllexport) basicProgressBar __stdcall createProgressBar(int row, int column, int length)
{
	thingmapper tmp = make_pair(allOfBars.size(), progressbar);
	mapAllOfThings.push_back(tmp);
	//TODO:进度条样式
	basicProgressBar ret(0, length);
	allOfBars.push_back(ret);
	refreshScreen();
	return ret;
}

__declspec(dllexport) void __stdcall updateProgressBar(basicProgressBar& youwant, int progress)
{
	youwant.updateProgress(progress);
	refreshScreen();
	return;
}