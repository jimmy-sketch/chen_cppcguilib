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

// Create
static auto testCreateImage() {
    return createImage(0, 0, getImageByLines("apple.png"));
}

static auto testCreateProgressBar() {
    return createProgressBar(0, 0, 10);
}

static auto testCreateText() {
    string text = "Hello World!";
    return createText(0, 0, text);
}

// Change
static void testChangeImage(basicImage* image) {
    changeImage(image, getImageByLines("diamond_sword.png"));
}

static void testChangeProgress(basicProgressBar* progressBar) {
    for (int i = 10; i <= 100; i += 10) {
        this_thread::sleep_for(200ms);
        changeProgress(progressBar, i);
    }
}

static void testChangeText(basicText* text) {
    changeText(text, "Hello CGUI!");
}

// Main
int main() {
    auto image = testCreateImage();
    auto text = testCreateText();
    auto progressBar = testCreateProgressBar();
    testChangeProgress(progressBar);
    testChangeImage(image);
    testChangeText(text);
}