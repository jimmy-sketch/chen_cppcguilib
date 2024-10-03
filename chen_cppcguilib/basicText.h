#pragma once
#include<iostream>
#include<string>
using namespace std;
class basicText
{
public:
    basicText(string x);
    void changeText(string x);
    string selfDraw();
private:
    string data;
};

