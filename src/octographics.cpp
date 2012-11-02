#include <iostream>
#include "OctoGraphics.h"

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);
    OctoGraphics::Vector2D v, w, k;
    v.set(1, 0);
    w.set(0, 1);

    k = v + w;

    if (k != v) std::cout << "ok\n";
    if (k == (v + w) * 2.0) std::cout << "ok\n";

    std::cout << k[0] << ' ' << k[1] << "\n";
    k *= 7;
    std::cout << k[0] << ' ' << k[1] << "\n";
    std::cout << v * w << '\n';

    color.set_rgb(255, 255, 255);
    img.clear(color);

    img.save("imagem.ppm");
    
    return 0;
}
