#ifndef COLOR_H
#define COLOR_H

namespace OctoGraphics {

class Color {
    private:
        int alpha;
        int red;
        int green;
        int blue;

    public:
        int get_red();
        int get_green();
        int get_blue();
        int get_alpha();
        void set_rgb(int r, int g, int b);
        void set_color(OctoGraphics::Color& c);
};

}

#endif
