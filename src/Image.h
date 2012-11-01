#ifndef IMAGE_H
#define IMAGE_H

#include <sstream>
#include <fstream>
#include "Color.h"

class Image {
    private:
        int width;
        int height;
        Color** drawing;

    private:
        void alloc(int w, int h);

    public:
        Image(int w, int h);

    public:
        void set_pixel(int i, int j, Color& c);
        void clear(Color& c);
        void save(std::string filename);
        void open(std::string filename);
};

#endif
