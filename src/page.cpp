#include <cgui/page.h>
#include <iostream>

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

void page::update() const
{
    system("cls");
    std::cout << toString();
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
