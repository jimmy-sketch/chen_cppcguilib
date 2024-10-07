#include "basicImage.h"
#include<vector>
#include <regex>

basicImage::basicImage(const std::vector<cgui::string>& image)
	: image(image)
{
	calculateWidth();
}

int basicImage::getWidth() const
{
	return width;
}

int basicImage::getHeight() const
{
	return image.size();
}

std::vector<std::string> basicImage::getData() const
{
	std::vector<std::string> ret;
	for (auto& line : image) {
		ret.push_back(line.data());
	}
	return ret;
}

void basicImage::setImage(const std::vector<cgui::string>& image)
{
	this->image = image;
	calculateWidth();
}

void basicImage::calculateWidth()
{
	width = 0;
	for (auto& line : image) {
		width = std::max(line.length(), width);
	}
}
