#include <cgui/utils/config.h>

char paddingChar = ' ';

char cgui::getPaddingChar()
{
    return paddingChar;
}

void cgui::setPaddingChar(char c)
{
    paddingChar = c;
}
