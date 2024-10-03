#pragma once
class basicProgressBar
{
public:
	basicProgressBar(int length, int style);
	~basicProgressBar() {};
	void updateProgress(int dProgress);
	string selfDraw();
private:
	int length, style, progress;
};