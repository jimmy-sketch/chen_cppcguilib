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

size_t multiLineText::calcuateLength() const
{
    size_t maxLength = 0;
    for (auto kv : textByLine)
        maxLength = std::max(kv.size(), maxLength);
    return maxLength;
}
