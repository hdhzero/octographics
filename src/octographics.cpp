#include <iostream>
#include "OctoGraphics.h"

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);
    OctoGraphics::Vertex v(100, 400);
    OctoGraphics::Vertex w(0, 0);

    color.set_rgb(255, 255, 255);
    img.clear(color);
    color.set_rgb(0, 0, 0);
    img.set_color(color);
    img.draw_simple_line(v, w);

    img.save("imagem.ppm");
    
    return 0;
}
