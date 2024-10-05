#include"cgui.h"
using namespace std;
//tmd这几个破组件耦合在一起了！
vector<shared_ptr<thingMapper>> allThings;
vector<shared_ptr<basicImage>> allImage;
vector<shared_ptr<basicText>> allText;
vector<shared_ptr<basicProgressBar>> allProgressBars;


//todo:加入排版

thingMapper::thingMapper(pair<int, thingType> x, int _row, int _column)
{
	mapper = x;
	row = _row, column = _column;
}

bool thingCmp(std::shared_ptr<thingMapper> a, std::shared_ptr<thingMapper> b)
{
	if (a->row == b->row)
		return a->column < b->column;
	else
		return a->row < b->row;
}

bool allZero(vector<int> vec)
{
	for (auto kv : vec)
		if (kv)
			return false;
	return true;
}

string summonFrame()
{
	string finalFrame = "";
	
	sort(allThings.begin(), allThings.end(), thingCmp);
	int maxRow = allThings[allThings.size() - 1]->row;
	//按逻辑行拆分
	vector<vector<thingMapper> > thingsByRow(maxRow + 2);
	for (auto kv : allThings)
		thingsByRow[kv->row].push_back(*kv);
	//按逻辑行渲染
	for (int i = 1; i <= maxRow; i++)
	{
		//1.生成每个控件的总实际行数
		vector<int> linesPerThing = {};
		for (auto kv : thingsByRow[i])
		{
			switch (kv.mapper.second)
			{
			case image:
				linesPerThing.push_back(allImage[kv.mapper.first]->getTotalLines());
				break;
			case text:
				linesPerThing.push_back(1);
				break;
			case progressBar:
				linesPerThing.push_back(1);
				break;
			default:
				break;
			}
		}
		
		//2.按实际行一行一行显示
		//由于控件之间的间距功能还未加入，所以默认左边空一右边空一
		string oneLogicLine = "";
		while (!allZero(linesPerThing))
		{
			for (int j = 0; j < linesPerThing.size(); j++)
			{
				if (linesPerThing[j] == 0)
				{
					//具体控件具体判断……
					switch (thingsByRow[i][j].mapper.second)
					{
					case image:
					{
						for (int k = 1; k <= allImage[thingsByRow[i][j].mapper.first]->getMaxLineLength(); k++)
							oneLogicLine += " ";
						break;
					}
					case text:
					{
						for (int k = 1; k <= allText[thingsByRow[i][j].mapper.first]->getLength(); k++)
							oneLogicLine += " ";
						break;
					}
					case progressBar:
					{
						for (int k = 1; k <= allProgressBars[thingsByRow[i][j].mapper.first]->getLength(); k++)
							oneLogicLine += " ";
						break;
					}
					default:
						break;
					}
				}
				else
				{
					//具体控件具体判断……
					switch (thingsByRow[i][j].mapper.second)
					{
					case image:
					{
						//输出图片的一行
						auto thisImage = allImage[thingsByRow[i][j].mapper.first];
						oneLogicLine += thisImage->getOneLine(thisImage->getTotalLines() - linesPerThing[j] + 1);
						if (thisImage->getOneLine(thisImage->getTotalLines() - linesPerThing[j] + 1).length() < thisImage->getMaxLineLength())
						{
							for (int k = 1; k <= thisImage->getOneLine(thisImage->getTotalLines() - linesPerThing[j] + 1).length() - thisImage->getMaxLineLength(); k++)
								oneLogicLine += " ";
						}
						linesPerThing[j]--;
						break;
					}
					case text:
					{
						auto& thisText = allText[thingsByRow[i][j].mapper.first];
						oneLogicLine += thisText->selfDraw();
						linesPerThing[j]--;
						break;
					}
					case progressBar:
					{
						auto thisProgressBar = allProgressBars[thingsByRow[i][j].mapper.first];
						oneLogicLine += thisProgressBar->selfDraw();
						linesPerThing[j]--;
						break;
					}
					default:
						break;
					}
				}
				oneLogicLine = oneLogicLine + " ";
			}
			oneLogicLine = oneLogicLine + "\n";
		}
		finalFrame = finalFrame + oneLogicLine;
	}

	return finalFrame;
}

void refreshScreen()
{
	string frame = summonFrame();
	// 使用ANSI编码清屏
	system("cls");
	cout << frame;
	return;
}

//create相关函数，需要注意的是所有的排版相关参数(row/column)将会被忽略，在未来会加入相关功能
shared_ptr<basicImage>  createImage(int row, int column, vector<string> imageByLine)
{
	allImage.emplace_back(make_shared<basicImage>(imageByLine));
	allThings.emplace_back(make_shared<thingMapper>(make_pair(allImage.size() - 1, thingType::image), row, column));
	refreshScreen();
	return allImage.back();
}

shared_ptr<basicText>  createText(int row, int column, string text)
{
	allText.emplace_back(make_shared<basicText>(text));
	allThings.emplace_back(make_shared<thingMapper>(make_pair(allText.size() - 1, thingType::text), row, column));
	refreshScreen();
	return allText.back();
}

shared_ptr<basicProgressBar>  createProgressBar(int row, int column, int length)
{
	allProgressBars.emplace_back(make_shared<basicProgressBar>(length, 0));
	allThings.emplace_back(make_shared<thingMapper>(make_pair(allProgressBars.size() - 1, thingType::progressBar), row, column));
	refreshScreen();
	return allProgressBars.back();
}

//change相关函数
void  changeImage(shared_ptr<basicImage> youwant, vector<string> imageByLine)
{
	youwant->changeImage(imageByLine);
	refreshScreen();
	return;
}

void  changeProgress(shared_ptr<basicProgressBar> youwant, int progress)
{
	youwant->updateProgress(progress);
	refreshScreen();
	return;
}

void changeText(shared_ptr<basicText> youwant, string text)
{
	youwant->changeText(text);
	refreshScreen();
	return;
}