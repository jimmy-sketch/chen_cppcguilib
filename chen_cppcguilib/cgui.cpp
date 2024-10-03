#include"cgui.h"
using namespace std;

vector<thingMapper> allThings;
vector<basicImage> allImage;
vector<basicText> allText;
vector<basicProgressBar> allProgressBars;


//todo:加入排版
string summonFrame()
{
	string finalFrame = "";
	for (auto kv : allThings)
	{
		switch (kv.second)
		{

		case image:
			finalFrame += allImage[kv.first].selfDraw();//这里不加换行符是因为basicImage的selfDraw()中有换行了
			break;
		case progressBar:
			finalFrame = finalFrame + allProgressBars[kv.first].selfDraw() + '\n';
			break;
		case text:
			finalFrame = finalFrame + allText[kv.first].selfDraw() + '\n';
			break;
		default:
			break;
		}
	}
	return finalFrame;
}

void refreshScreen()
{
	string frame = summonFrame();
	system("cls");//基于windows(msvc),暂时不考虑加入Linux相关支持
	cout << frame;
	return;
}

//create相关函数，需要注意的是所有的排版相关参数(row/column)将会被忽略，在未来会加入相关功能
basicImage*  createImage(int row, int column, vector<string> imageByLine)
{
	basicImage returnThing(imageByLine);
	thingMapper thisThing = make_pair(allImage.size(),thingType::image);
	allImage.push_back(returnThing);
	allThings.push_back(thisThing);
	refreshScreen();
	return &allImage[allImage.size()-1];
}

basicText*  createText(int row, int column, string text)
{
	basicText returnThing(text);
	thingMapper thisThing = make_pair(allText.size(), thingType::text);
	allText.push_back(returnThing);
	allThings.push_back(thisThing);
	refreshScreen();
	return &allText[allText.size() - 1];
}

basicProgressBar*  createProgressBar(int row, int column, int length)
{
	basicProgressBar returnthing(length, 0);//改变样式将会在未来加入
	thingMapper thisThing = make_pair(allProgressBars.size(), thingType::progressBar);
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