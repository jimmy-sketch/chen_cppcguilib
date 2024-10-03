#pragma once
#include<string>
using namespace std;

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