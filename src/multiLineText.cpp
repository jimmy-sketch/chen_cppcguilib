#include <cgui/components/multiLineText.h>

multiLineText::multiLineText(std::vector<cgui::string> textByLine)
    : textByLine(textByLine) {}

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

void multiLineText::pushBack(const cgui::string& newLine) {
    textByLine.push_back(newLine);
}

cgui::string& multiLineText::operator[](size_t index) {
    return textByLine.at(index);
}

const cgui::string& multiLineText::operator[](size_t index) const {
    return textByLine.at(index);
}