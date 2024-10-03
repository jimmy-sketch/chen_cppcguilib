#pragma once
#include<string>
#include<vector>
using namespace std;
class basicImage
{
public:
    basicImage(vector<string> _image);
    void changeImage(vector<string> _image);
    string selfDraw();
private:
    vector<string> image;
};

