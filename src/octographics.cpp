#include <iostream>
#include "OctoGraphics.h"

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);

    color.set_rgb(255, 255, 255);
    img.clear(color);

    img.save("imagem.ppm");
    
    return 0;
}
