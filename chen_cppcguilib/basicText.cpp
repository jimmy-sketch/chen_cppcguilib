#include"basicText.h"
#include <regex>
using namespace std;

basicText::basicText(std::string_view str)
	: text(str)
{}

int basicText::getWidth() const
{
	return text.length();
}

int basicText::getHeight() const
{
	return 1;
}

std::vector<std::string> basicText::getData() const
{
	return { text.data() };
}

void basicText::setText(std::string_view str)
{
	text = str;
}
