#include "basicProgressBar.h"
#include <cassert>

basicProgressBar::basicProgressBar(int _length, int _style)
	: length(_length), style(_style), progress(0)
{
	assert(length > 3);
}

size_t basicProgressBar::getWidth() const
{
	if (progress < 10)
		return length + 2;
	if (progress < 100)
		return length + 3;
	if (this->isDone())
		return length + 4;
	return 0;
}

size_t basicProgressBar::getHeight() const
{
	return 1;
}

std::vector<cgui::string> basicProgressBar::getData() const
{
	std::string ret = "";
	int fillCount = (int)((double)progress * (double)(length - 2) / 100.0);
	ret = ret + std::to_string(this->progress) + "%";
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
	return { ret.data() };
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