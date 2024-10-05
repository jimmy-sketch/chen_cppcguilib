#include <cgui.h>
#include <string>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static vector<string> getImageByLines(const std::string& imageFile) {
    vector<string> lines;
    int width = 0, height = 0, channels = 0;
    auto pixels = stbi_load(imageFile.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    for (int y = 0; y < height; ++y) {
        string line = "";
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            line += pixels[i + 3] ? '#' : '.';
        }
        lines.push_back(line);
    }
    stbi_image_free(pixels);
    return lines;
}

int main() {
    auto image = createImage(1, 0, getImageByLines("apple.png"));
    auto text = createText(1, 1, "Hello World!");
    auto progressBar = createProgressBar(3, 0, 10);

    for (int i = 10; i <= 100; i += 10) {
        this_thread::sleep_for(200ms);
        changeProgress(progressBar, i);
    }
    changeImage(image, getImageByLines("diamond_sword.png"));
    changeText(text, "Hello CGUI!");
    return 0;
}