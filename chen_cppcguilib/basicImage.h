#pragma once
#include<vector>
#include "basicthing.h"
class basicImage
{
public:
    basicImage(vector<string> _image);
    void changeImage(vector<string> _image);
    string selfDraw();
private:
    vector<string> image;
};

