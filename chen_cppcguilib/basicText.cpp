#include"basicText.h"
using namespace std;

basicText::basicText(string x)
{
	data = x;
}

string basicText::selfDraw()
{
	return data;
}

int basicText::getLength()
{
	return data.length();
}

void basicText::changeText(string x)
{
	data = x;
}