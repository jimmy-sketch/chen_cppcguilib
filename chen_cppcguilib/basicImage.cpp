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

void basicImage::changeImage(vector<string> x)
{
	image = x;
}