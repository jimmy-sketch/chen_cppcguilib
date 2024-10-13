#include "multiLineText.h"

multiLineText::multiLineText(std::vector<cgui::string> textByLine)
{
    this->textByLine = textByLine;
}

size_t multiLineText::getWidth() const
{
    return calcuateLength();
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

size_t multiLineText::calcuateLength() const
{
    size_t maxLength = 0;
    for (auto& line : textByLine) {
        maxLength = std::max(line.length(), maxLength);
    }
    return maxLength;
}
