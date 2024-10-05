#include"cgui.h"
using namespace std;
//tmd这几个破组件耦合在一起了！
vector<thingMapper> allThings;
vector<basicImage> allImage;
vector<basicText> allText;
vector<basicProgressBar> allProgressBars;


//todo:加入排版

thingMapper::thingMapper(pair<int, thingType> x, int _row, int _column)
{
	mapper = x;
	row = _row, column = _column;
}

string summonFrame()
{
	string finalFrame = "";
	return finalFrame;
}

void refreshScreen()
{
	string frame = summonFrame();
	// 使用ANSI编码清屏
	cout << "\033[H" << frame;
	return;
}

//create相关函数，需要注意的是所有的排版相关参数(row/column)将会被忽略，在未来会加入相关功能
basicImage*  createImage(int row, int column, vector<string> imageByLine)
{
	basicImage returnThing(imageByLine);
	thingMapper thisThing = thingMapper(make_pair(allThings.size(), thingType::image), row, column);
	allImage.push_back(returnThing);
	allThings.push_back(thisThing);
	refreshScreen();
	return &allImage[allImage.size()-1];
}

basicText*  createText(int row, int column, string text)
{
	basicText returnThing(text);
	thingMapper thisThing = thingMapper(make_pair(allThings.size(), thingType::text), row, column);
	allText.push_back(returnThing);
	allThings.push_back(thisThing);
	refreshScreen();
	return &allText[allText.size() - 1];
}

basicProgressBar*  createProgressBar(int row, int column, int length)
{
	basicProgressBar returnthing(length, 0);//改变样式将会在未来加入
	thingMapper thisThing = thingMapper(make_pair(allThings.size(), thingType::progressBar), row, column);
	allProgressBars.push_back(returnthing);
	allThings.push_back(thisThing);
	refreshScreen();
	return &allProgressBars[allProgressBars.size() - 1];
}

//change相关函数
void  changeImage(basicImage* youwant, vector<string> imageByLine)
{
	youwant->changeImage(imageByLine);
	refreshScreen();
	return;
}

void  changeProgress(basicProgressBar* youwant, int progress)
{
	youwant->updateProgress(progress);
	refreshScreen();
	return;
}

void changeText(basicText* youwant, string text)
{
	youwant->changeText(text);
	refreshScreen();
	return;
}
