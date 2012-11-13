#include <iostream>
#include "OctoGraphics.h"

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);
    OctoGraphics::Vertex v(100, 400, 1, 1);
    OctoGraphics::Vertex w(0, 0, 1, 1);
    OctoGraphics::Matrix m;

    color.set_rgb(100, 100, 100);
    img.clear(color);

    color.set_rgb(0, 0, 0);
    img.set_color(color);
    m.identity();

    img.draw_simple_line(m.apply(v), w);
    m.rotate(0, 0, 0.1);
    img.draw_simple_line(m.apply(v), w);

    m.rotate(1.0, 0.7, 0.1);
    img.draw_simple_line(m.apply(v), w);
    img.save("imagem.ppm");
    
    return 0;
}
