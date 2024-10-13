#include "basicImage.h"
#include<vector>
#include <regex>

basicImage::basicImage(const std::vector<cgui::string>& image)
	: image(image)
{
	calculateWidth();
}

size_t basicImage::getWidth() const
{
	return width;
}

size_t basicImage::getHeight() const
{
	return image.size();
}

std::vector<cgui::string> basicImage::getData() const
{
	return image;
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
