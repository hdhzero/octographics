#ifndef OCTOGRAPHICS_IMAGE_H
#define OCTOGRAPHICS_IMAGE_H

#include "OctoGraphics.h"
#include <stdint.h>
#include <X11/Xlib.h>

namespace OctoGraphics {

class Image {
    private:
        int width;
        int height;
        Color color;
        std::vector<std::vector<Color> > drawing;
        std::vector<std::vector<Fixed> > depth_buffer;

    private:
        void alloc(int w, int h);
        void setPixel(int x, int y);

    public:
        Image(int w, int h);

    public:
        void set_pixel(int i, int j, Color& c);
        void set_color(Color& c);
        void clear(Color& c);
        void save(std::string filename);
        void open(std::string filename);

    public:
        void draw_simple_line(const Vertex& v1, const Vertex& v2);
        void render_to_X(Display*& display, Window& drawable, int s);
        void render_to_SDL(uint32_t* framebuffer);
        void draw_point(int x, int y, Color& c);
        void draw_point(Vertex& v, Color& c);
};

}

#endif
