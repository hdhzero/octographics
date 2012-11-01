#include "Color.h"

int OctoGraphics::Color::get_red() { 
    return red; 
}

int OctoGraphics::Color::get_green() { 
    return green; 
}

int OctoGraphics::Color::get_blue() { 
    return blue; 
}

int OctoGraphics::Color::get_alpha() { 
    return alpha; 
}

void OctoGraphics::Color::set_rgb(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
}

void OctoGraphics::Color::set_color(Color& c) {
    alpha = c.alpha;
    red = c.red;
    green = c.green;
    blue = c.blue;
}

