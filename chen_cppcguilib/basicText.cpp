#include"basicText.h"
#include <regex>
using namespace std;

basicText::basicText(std::string_view str)
	: text(str)
{}

size_t basicText::getWidth() const
{
	return text.length();
}

size_t basicText::getHeight() const
{
	return 1;
}

std::vector<cgui::string> basicText::getData() const
{
	return { text };
}

void basicText::setText(std::string_view str)
{
	text = str;
}
