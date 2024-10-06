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
	int fillCount = (int)((double)progress * (double)(length - 2) / 100.0);
	ret += beginChar;
	for (int i = 0; i < length - 2; ++i) {
		if (i < fillCount) {
			ret += fillChar;
		}
		else if (i == fillCount) {
			ret += seqChar;
		}
		else {
			ret += gapChar;
		}
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