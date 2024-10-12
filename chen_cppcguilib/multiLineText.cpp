#include "multiLineText.h"

multiLineText::multiLineText(std::vector<cgui::string> textByLine)
{
    this->textByLine = textByLine;
}

int multiLineText::getWidth() const
{
    return calcuateLength();
}

int multiLineText::getHeight() const
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

int multiLineText::calcuateLength() const
{
    int maxLength = 0;
    for (auto& line : textByLine) {
        maxLength = std::max(line.length(), maxLength);
    }
    return maxLength;
}
