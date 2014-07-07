#include "Color.h"

namespace OctoGraphics {

int Color::get_red() { 
    return red; 
}

int Color::get_green() { 
    return green; 
}

int Color::get_blue() { 
    return blue; 
}

int Color::get_alpha() { 
    return alpha; 
}

void Color::set_rgb(int r, int g, int b, int a) {
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

void Color::set_color(Color& c) {
    alpha = c.alpha;
    red = c.red;
    green = c.green;
    blue = c.blue;
}

}
