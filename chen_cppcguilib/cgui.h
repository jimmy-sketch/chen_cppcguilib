#pragma once
#include"basicImage.h"
#include"basicProgressBar.h"
#include"basicText.h"
#include <memory>

//重要函数：刷新、呈现控件内容
std::string summonFrame();
void refreshScreen();

//生成并放置控件
std::shared_ptr<basicImage>  setImage(int row, int col, std::vector<std::string> imageByLine);
std::shared_ptr<basicText>   setText(int row, int col, std::string text);
std::shared_ptr<basicProgressBar>  setProgressBar(int row, int col, int len);
//把某个控件放到...
void setTo(int row, int col, std::shared_ptr<component> src);
//更改控件
void  modifyImage(std::shared_ptr<basicImage> target, std::vector<std::string> imageByLine);
void  modifyText(std::shared_ptr<basicText> target, std::string text);
void  updateProgress(std::shared_ptr<basicProgressBar> target, int progress);
