#include "basicProgressBar.h"
#include <cassert>

using namespace std;

basicProgressBar::basicProgressBar(int _length, int _style)
	: length(_length), style(_style), progress(0)
{
	assert(length > 3);
}

int basicProgressBar::getWidth() const
{
	return length;
}

int basicProgressBar::getHeight() const
{
	return 1;
}

std::vector<std::string> basicProgressBar::getData() const
{
	string ret = "";
	double actualLength = ((double)progress / 100.0) * (length);
	ret += startChar;
	for (double i = 1; i <= actualLength; i += 1)
		ret += fillChar;
	if (progress != 100)
	{
		ret += seqChar;
		for (double i = 1; i <= (length - actualLength); i++)
			ret += gapChar;
	}
	ret += endChar;
	return { ret };
}

void basicProgressBar::updateProgress(int progress)
{
	this->progress = progress;
}

int basicProgressBar::getProgress() const
{
	return progress;
}

bool basicProgressBar::isDone() const
{
	return progress >= 100;
}