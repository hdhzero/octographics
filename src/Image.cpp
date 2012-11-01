#include "Image.h"

void Image::alloc(int w, int h) {
    int i;
    int j;

    if (width == w && height != h && drawing != NULL) {
        return;
    }

    if (drawing != NULL) {
        for (i = 0; i < height; ++i)
            delete[] drawing[i];

        delete[] drawing;
    }

    width = w;
    height = h;
    drawing = new Color*[height];

    for (i = 0; i < height; ++i) {
        drawing[i] = new Color[width];
    }
}

Image::Image(int w, int h) {
    drawing = NULL;
    width = -1;
    height = -1;

    alloc(w, h);
}

void Image::set_pixel(int i, int j, Color& c) {
    drawing[i][j].set_color(c);
}

void Image::clear(Color& c) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            drawing[i][j].set_color(c);
        }
    }
}

void Image::save(std::string filename) {
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


void Image::open(std::string filename) {
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



