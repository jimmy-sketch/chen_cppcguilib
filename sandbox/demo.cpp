#include <cgui/cgui.h>
#include <thread>
#include <iostream>
#include <fstream>
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
        lines.push_back(line);
    }
    stbi_image_free(pixels);
    return lines;
}

stbtt_fontinfo font;
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

static void initFont() {
    std::ifstream file("../../asserts/simhei.ttf", std::ios::binary);
    assert(file);
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    unsigned char* ttf_buffer = new unsigned char[size];
    file.read((char*)ttf_buffer, size);
    stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
}

int main() {
    initFont();

    auto image = std::make_shared<basicImage>(getImageByLines("../../asserts/textures/apple.png"));
    auto space = std::make_shared<basicText>("   ");
    auto title = std::make_shared<hContainer>();
    title->set(0, image);
    title->set(1, space);
    title->set(2, std::make_shared<basicImage>(bigChar('C')));
    title->set(3, space);
    title->set(4, std::make_shared<basicImage>(bigChar('G')));
    title->set(5, space);
    title->set(6, std::make_shared<basicImage>(bigChar('U')));
    title->set(7, space);
    title->set(8, std::make_shared<basicImage>(bigChar('I')));
    title->set(9, space);
    title->set(10, image);
    
    auto progressBar = std::make_shared<basicProgressBar>(10, 0);
    auto progressBar1 = std::make_shared<basicProgressBar>(10, 1);
    auto progressBar2 = std::make_shared<basicProgressBar>(10, 2);
    auto progressBar3 = std::make_shared<basicProgressBar>(10, 2);
    auto progressBars = std::make_shared<vContainer>();
    progressBars->set(0, progressBar);
    progressBars->set(1, progressBar1);
    progressBars->set(2, progressBar2);
    progressBars->set(3, progressBar3);

    std::vector<cgui::string> multiText = { "Red Red Red","Green Green Green","Blue Blue Blue" };
    multiText[0].insertRGB(0, 255, 0, 0);
    multiText[1].insertRGB(0, 0, 255, 0);
    multiText[2].insertRGB(0, 0, 0, 255);
    auto multiLine = std::make_shared<multiLineText>(multiText);
    auto line1 = std::make_shared<hContainer>();
    line1->set(0, multiLine);
    line1->set(1, std::make_shared<basicText>("progress bars:"));
    line1->set(2, progressBars);

    page p;
    p.set({ 0, 0 }, title);
    p.set({ 1, 0 }, line1);
    p.update();
    while (!progressBar->isDone()) {
        std::this_thread::sleep_for(500ms);
        progressBar->updateProgress(progressBar->getProgress() + 10);
        progressBar1->updateProgress(progressBar1->getProgress() + 10);
        progressBar2->updateProgress(progressBar2->getProgress() + 10);
        progressBar3->updateProgress(progressBar3->getProgress() + 10);
        p.update();
    }
    return 0;
}