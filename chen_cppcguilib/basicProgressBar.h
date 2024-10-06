#pragma once
#include<string>
#include "component.h"

class basicProgressBar : public component
{
public:
	basicProgressBar(int length, int style);
	int getWidth() const override;
	int getHeight() const override;
	std::vector<std::string> getData() const override;

	void updateProgress(int progress);
	int getProgress() const;
	bool isDone() const;

private:
	int length, style, progress;
	char startChar = '[', fillChar = '=', seqChar = '>', gapChar = ' ', endChar = ']';
};