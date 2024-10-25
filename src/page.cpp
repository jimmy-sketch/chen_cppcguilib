#include <cgui/page.h>
#include <iostream>
#include <cgui/utils/config.h>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <sys/ioctl.h>  // for winsize, ioctl, TIOCGWINSZ
#include <unistd.h>     // for STDOUT_FILENO
#endif

static int terminalWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return 0;
#else
    winsize w{};
    const int status = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

static int terminalHeight() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return 0;
#else
    winsize w{};
    const int status = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
#endif
}

static void terminalClear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

size_t page::getWidth() const
{
    return table.getWidth();
}

size_t page::getHeight() const
{
    return table.getHeight();
}

std::vector<cgui::string> page::getData() const
{
    return table.getData();
}

std::string page::toString() const
{
    std::string ret = "";
    for (auto& line : getData()) {
        ret += std::string(line.data()) + "\n";
    }
    return ret;
}

static int oldWidth = 0;
static int oldHeight = 0;
void page::update() const
{
    int tWidth = terminalWidth();
    int tHeight = terminalHeight();
    if (oldWidth != tWidth || oldHeight != tHeight) {
        terminalClear();
        oldWidth = tWidth;
        oldHeight = tHeight;
    }

    std::string buffer = "";
    auto data = getData();
    for (int i = 0; i < tHeight; ++i) {
        if (i < getHeight()) {
            buffer += std::string(data[i].take(tWidth).data());
        }
        else {
            buffer += std::string(tWidth, cgui::getPaddingChar());
        }
        if (i + getHeight() < tHeight) {
            buffer += '\n';
        }
    }
    printf("\x1B[?25l\x1B[0;0H%s", buffer.data());
}

void page::set(cgui::logicPos pos, std::shared_ptr<component> src)
{
    table.set(pos, src);
}

void page::erase(cgui::logicPos pos)
{
    table.erase(pos);
}

void page::clear()
{
    table.clear();
}
