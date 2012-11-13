#ifndef OCTOGRAPHICS_IMAGE_H
#define OCTOGRAPHICS_IMAGE_H

#include "OctoGraphics.h"

namespace OctoGraphics {

class Image {
    private:
        int width;
        int height;
        std::vector<std::vector<Color> > drawing;

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

}

#endif
