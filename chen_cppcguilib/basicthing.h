#pragma once
#include<iostream>
#include<string>
using namespace std;

class basicthing
{
public:
	basicthing(string data);
	~basicthing();
	string selfDraw();
private:
	string data;
};
