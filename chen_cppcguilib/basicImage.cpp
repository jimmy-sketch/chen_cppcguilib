#include "basicImage.h"
#include<vector>
using namespace std;

basicImage::basicImage(vector<string> x)
{
	image = x;
}

string basicImage::selfDraw()
{
	string ret = "";
	for (auto kv : image)
		ret = ret + kv + "\n";
	return ret;
}

string basicImage::getOneLine(int lineNumber)
{
	return image[lineNumber - 1];
}

int basicImage::getTotalLines()
{
	return image.size();
}

void basicImage::changeImage(vector<string> x)
{
	image = x;
}