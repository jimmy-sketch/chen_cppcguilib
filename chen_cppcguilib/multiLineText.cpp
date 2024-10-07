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

std::vector<std::string> multiLineText::getData() const
{
    std::vector<std::string> ret;
    for (auto& line : textByLine) {
        ret.push_back(line.data());
    }
    return ret;
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
