#include"cgui.h"
using namespace std;

enum thingType{text,image,progressbar};

typedef pair<int, thingType> thingmapper;
//first:在allof*中对应的下标

vector<thingmapper> mapAllOfThings;

vector<basicText> allOfText;
vector<basicImage> allOfImage;
vector<basicProgressBar> allOfBars;

vector<string> summonFrame()
{
	vector<string> frame = {};
	for (auto kv : mapAllOfThings)
	{
		switch (kv.second)
		{
		case text:
			frame.push_back(allOfText[kv.first].selfDraw());
			break;
		case image:
			frame.push_back(allOfImage[kv.first].selfDraw());
			break;
		case progressbar:
			frame.push_back(allOfImage[kv.first].selfDraw());
			break;
		}
	}
	return frame;
}

__declspec(dllexport) void __stdcall refreshScreen()
{
	vector<string> framePerLine = summonFrame();
	system("cls");
	for (auto kv : framePerLine)
		cout << kv << endl;
	return;
}
//主函数定义在此