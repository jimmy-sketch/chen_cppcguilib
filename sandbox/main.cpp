#include <cgui.h>
#include <string>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

using namespace std::literals;

static std::vector<cgui::string> getImageByLines(std::string_view imageFile) {
    std::vector<cgui::string> lines;
    int width = 0, height = 0, channels = 0;
    auto pixels = stbi_load(imageFile.data(), &width, &height, &channels, STBI_rgb_alpha);
    for (int y = 0; y < height; ++y) {
        cgui::string line = "";
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            int r = pixels[i], g = pixels[i + 1], b = pixels[i + 2], a = pixels[i + 3];
            if (a < 128) {
                line.pushBackDefaultRGB();
            }
            else {
                line.pushBackBackgroundRGB(r, g, b);
            }
            line += " ";
        }
        line.pushBackDefaultRGB();
        lines.push_back(line);
    }
    stbi_image_free(pixels);
    return lines;
}

stbtt_fontinfo font;
unsigned char ttf_buffer[1 << 25];
static std::vector<cgui::string> bigChar(char c) {
    int w = 0, h = 0, s = 20;
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0, 0);
    std::vector<cgui::string> image;
    for (int j = 0; j < h; ++j) {
        cgui::string str = "";
        for (int i = 0; i < w; ++i)
            str += " .:ioVM@"[bitmap[j * w + i] >> 5];
        image.push_back(str);
    }
    return image;
}

void initFont() {
    FILE* f = nullptr;
    fopen_s(&f, "simhei.ttf", "rb");
    fread(ttf_buffer, 1, static_cast<size_t>(1) << 25, f);
    stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
}

int main() {
    initFont();
    page p;

    auto image = std::make_shared<basicImage>(getImageByLines("apple.png"));
    auto progressBar = std::make_shared<basicProgressBar>(10, 0);

    std::vector<cgui::string> multiText = { "Red Red Red","Green Green Green","Blue Blue Blue" };
    multiText[0].insertRGB(0, 255, 0, 0);
    multiText[1].insertRGB(0, 0, 255, 0);
    multiText[2].insertRGB(0, 0, 0, 255);
    auto multiLine = std::make_shared<multiLineText>(multiText);

    p.setTo({ 0, 0 }, image);
    p.setTo({ 1, 0 }, std::make_shared<basicText>("\033[38;2;255;0;0mRed Text\033[0m"));
    p.setTo({ 0, 1 }, std::make_shared<basicText>("Hello World!"));
    p.setTo({ 2, 0 }, progressBar);
    p.setTo({ 2, 1 }, multiLine);
    p.update();

    while (!progressBar->isDone()) {
        std::this_thread::sleep_for(200ms);
        progressBar->updateProgress(progressBar->getProgress() + 10);
        p.update();
    }
    image->setImage(getImageByLines("diamond_sword.png"));

    p.clear();

    auto space = std::make_shared<basicText>("   ");

    p.setTo({ 0, 0 }, image);
    p.setTo({ 0, 1 }, space);
    p.setTo({ 0, 2 }, std::make_shared<basicImage>(bigChar('C')));
    p.setTo({ 0, 3 }, space);
    p.setTo({ 0, 4 }, std::make_shared<basicImage>(bigChar('G')));
    p.setTo({ 0, 5 }, space);
    p.setTo({ 0, 6 }, std::make_shared<basicImage>(bigChar('U')));
    p.setTo({ 0, 7 }, space);
    p.setTo({ 0, 8 }, std::make_shared<basicImage>(bigChar('I')));
    p.setTo({ 0, 9 }, space);
    p.setTo({ 0, 10 }, image);
    p.update();

    return 0;
}