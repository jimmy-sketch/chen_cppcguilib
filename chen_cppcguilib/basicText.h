#pragma once
#include "basicthing.h"
class basicText :
    public basicthing
{
public:
    basicText(string x);
    void changeText(string x);
private:
    string data;
};

