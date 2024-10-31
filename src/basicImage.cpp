#include <cgui/components/basicImage.h>
#include <vector>


basicImage::basicImage(const std::vector<cgui::string>& image)
	: image(image)
{}

size_t basicImage::getWidth() const
{
	size_t maxWidth = 0;
	for (auto& line : image) {
		maxWidth = std::max(line.getWidth(), maxWidth);
	}
	return maxWidth;
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
}