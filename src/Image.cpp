#include "Image.h"

OctoGraphics::Image::Image(int w, int h) {
    alloc(w, h);
}

void OctoGraphics::Image::alloc(int w, int h) {
    width = w;
    height = h;

    drawing.resize(height);

    for (int i = 0; i < height; ++i) {
        drawing[i].resize(width);
    }
}

void OctoGraphics::Image::set_pixel(int i, int j, Color& c) {
    drawing[i][j].set_color(c);
}

void OctoGraphics::Image::clear(Color& c) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            drawing[i][j].set_color(c);
        }
    }
}

void OctoGraphics::Image::save(std::string filename) {
    std::ofstream file;
    file.open(filename.c_str());

    file << "P3\n" << width << ' ' << height
        << "\n255\n";

    std::stringstream ss;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ss << drawing[i][j].get_red() << ' '
                << drawing[i][j].get_green() << ' '
                << drawing[i][j].get_blue() << '\n';
        }
    }

    file << ss.str();
    file.close();
}


void OctoGraphics::Image::open(std::string filename) {
    std::ifstream file;
    std::string tmp;
    int w, h, t;
    
    file >> tmp;
    file >> w >> h;
    alloc(w, h);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> w >> h >> t;
            drawing[i][j].set_rgb(w, h, t);
        }
    }
}



