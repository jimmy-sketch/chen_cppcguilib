#pragma once
#include<iostream>
#include<string>
using namespace std;
class basicText
{
public:
    basicText() {}
    basicText(string x);
    void changeText(string x);
    string selfDraw();
    int getLength();
private:
    string data;
};

