#include "basicProgressBar.h"

basicProgressBar::basicProgressBar(int _length, int _style)
{
	length = _length;
	style = _style;
	progress = 0;
}

void basicProgressBar::updateProgress(int dProgress)
{
	progress = dProgress;
}

string basicProgressBar::selfDraw()
{
	string ret = "";
	//样式部分：TODO
	
	char startChar = '[', fillChar = '=', seqChar = '>', endChar = ']';
	double actualLength = (1.0 * progress / 100.0) * (length);
	ret += startChar;
	for (double i = 1; i <= actualLength; i += 1)
		ret += fillChar;
	if (progress != 100)
	{
		ret += seqChar;
		for (double i = 1; i <= (length - actualLength); i++)
			ret += ' ';
		ret += endChar;
	}
	else
	{
		ret += endChar;
	}
	return ret;
}