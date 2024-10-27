#include <cgui/cgui.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <csignal>
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
                line += "  ";
            }
            else {
                line.pushBackRGB(r, g, b);
                line += "██";
            }
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
    signal(SIGINT, [](int s) {
        printf("\x1B[?25h");
        exit(0);
        });
    initFont();

    auto space = std::make_shared<basicText>("   ");
    auto progressBar = std::make_shared<basicProgressBar>(10, 0);
    auto progressBar1 = std::make_shared<basicProgressBar>(15, 1);
    auto progressBar2 = std::make_shared<basicProgressBar>(20, 2);
    auto progressBar3 = std::make_shared<basicProgressBar>(25, 2);
    std::vector<cgui::string> multiText = { 
        "CGUI是跨平台的控制台UI库",
        "CGUI支持UTF8字符：あ감ڠ😊⨌",
        "CGUI支持彩色字符"
    };
    multiText[0].setRGB(0, 255, 0, 0);
    multiText[1].setRGB(0, 0, 255, 0);
    // 彩虹色
    multiText[2].setRGB(0, 255, 0, 0);
    multiText[2].setRGB(1, 255, 165, 0);
    multiText[2].setRGB(2, 255, 255, 0);
    multiText[2].setRGB(3, 0, 255, 0);
    multiText[2].setRGB(4, 0, 255, 255);
    multiText[2].setRGB(5, 0, 0, 255);
    multiText[2].setRGB(6, 238, 130, 238);
    multiText[2].setRGB(7, 255, 0, 0);
    multiText[2].setRGB(8, 255, 165, 0);
    multiText[2].setRGB(9, 255, 255, 0);

    page p;
    p.set({ 0, 0 }, 
        std::make_shared<vContainer>(vContainer{
            std::make_shared<hContainer>(hContainer{
                std::make_shared<basicImage>(getImageByLines("../../asserts/textures/diamond_sword.png")),
                space,
                std::make_shared<basicImage>(bigChar('C')),
                space,
                std::make_shared<basicImage>(bigChar('G')),
                space,
                std::make_shared<basicImage>(bigChar('U')),
                space,
                std::make_shared<basicImage>(bigChar('I')),
                space
            }),
            std::make_shared<hContainer>(hContainer{
                std::make_shared<basicText>("progress bars:"),
                std::make_shared<vContainer>(vContainer{
                    progressBar,
                    progressBar1,
                    progressBar2,
                    progressBar3
                })
            })
        }));
    p.set({ 0, 1 }, std::make_shared<vContainer>(vContainer{
        std::make_shared<multiLineText>(multiText),
        std::make_shared<basicImage>(getImageByLines("../../asserts/textures/apple.png"))
        }));

    while (true) {
        p.update();
        std::this_thread::sleep_for(500ms);
        progressBar->updateProgress(progressBar->getProgress() + 10);
        progressBar1->updateProgress(progressBar1->getProgress() + 10);
        progressBar2->updateProgress(progressBar2->getProgress() + 10);
        progressBar3->updateProgress(progressBar3->getProgress() + 10);
        if (progressBar->isDone()) {
            progressBar->updateProgress(0);
            progressBar1->updateProgress(0);
            progressBar2->updateProgress(0);
            progressBar3->updateProgress(0);
        }
    }
    return 0;
}