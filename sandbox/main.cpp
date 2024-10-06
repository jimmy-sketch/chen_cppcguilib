#include <cgui.h>
#include <string>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
using namespace std;

static vector<string> getImageByLines(const std::string& imageFile) {
    vector<string> lines;
    int width = 0, height = 0, channels = 0;
    auto pixels = stbi_load(imageFile.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    for (int y = 0; y < height; ++y) {
        string line = "";
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            int r = pixels[i], g = pixels[i + 1], b = pixels[i + 2], a = pixels[i + 3];
            if (a < 128) {
                line += " ";
            }
            else {
                line += "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m¨€";
            }
        }
        line += "\033[0m";
        lines.push_back(line);
    }
    stbi_image_free(pixels);
    return lines;
}

stbtt_fontinfo font;
unsigned char ttf_buffer[1 << 25];
static vector<string> bigChar(char c) {
    int w = 0, h = 0, s = 20;
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0, 0);
    std::vector<string> image;
    for (int j = 0; j < h; ++j) {
        string str = "";
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
    vector<string> multiText = { "hello","world","CGUI!" };
    auto multiLine = std::make_shared<multiLineText>(multiText);

    p.setTo(0, 0, image);
    p.setTo(1, 0, std::make_shared<basicText>("\033[38;2;255;0;0mRed Text\033[0m"));
    p.setTo(0, 1, std::make_shared<basicText>("Hello World!"));
    p.setTo(2, 0, progressBar);
    p.setTo(3, 0, multiLine);
    p.update();

    while (!progressBar->isDone()) {
        this_thread::sleep_for(200ms);
        progressBar->updateProgress(progressBar->getProgress() + 10);
        p.update();
    }
    image->setImage(getImageByLines("diamond_sword.png"));

    p.clear();

    auto space = make_shared<basicText>("   ");

    p.setTo(0, 0, image);
    p.setTo(0, 1, space);
    p.setTo(0, 2, make_shared<basicImage>(bigChar('C')));
    p.setTo(0, 3, space);
    p.setTo(0, 4, make_shared<basicImage>(bigChar('G')));
    p.setTo(0, 5, space);
    p.setTo(0, 6, make_shared<basicImage>(bigChar('U')));
    p.setTo(0, 7, space);
    p.setTo(0, 8, make_shared<basicImage>(bigChar('I')));
    p.setTo(0, 9, space);
    p.setTo(0, 10, image);
    p.update();

    return 0;
}