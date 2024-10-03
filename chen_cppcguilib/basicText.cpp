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

void basicText::changeText(string x)
{
	data = x;
}