#include <cgui.h>
#include <string>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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
                line += "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m█";
            }
        }
        line += "\033[0m";
        lines.push_back(line);
    }
    stbi_image_free(pixels);
    return lines;
}

int main() {
    auto image = setImage(0, 0, getImageByLines("apple.png"));
    auto text = setText(0, 1, "Hello World!");
    auto text2 = setText(1, 0, "\033[38;2;255;0;0mRed Text\033[0m");
    auto progressBar = setProgressBar(2, 0, 10);

    while (!progressBar->isDone()) {
        this_thread::sleep_for(200ms);
        updateProgress(progressBar, progressBar->getProgress() + 10);
    }
    modifyImage(image, getImageByLines("diamond_sword.png"));
    setTo(0, 2, image);
    modifyText(text, "\033[5mHello CGUI!\033[0m"); // 以后改成跨多行的大字符串
    return 0;
}