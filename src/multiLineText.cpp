#include <cgui/components/multiLineText.h>

multiLineText::multiLineText(std::vector<cgui::string> textByLine)
{
    this->textByLine = textByLine;
}

size_t multiLineText::getWidth() const
{
    size_t maxWidth = 0;
    for (auto& line : textByLine) {
        maxWidth = std::max(line.getWidth(), maxWidth);
    }
    return maxWidth;
}

size_t multiLineText::getHeight() const
{
    return textByLine.size();
}

std::vector<cgui::string> multiLineText::getData() const
{
    return textByLine;
}

void multiLineText::setMultiText(std::vector<cgui::string> textByLine)
{
    this->textByLine = textByLine;
}
