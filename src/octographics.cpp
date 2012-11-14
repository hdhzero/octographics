#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <X11/Xlib.h>
#include "OctoGraphics.h"

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);
    OctoGraphics::Vertex v(10, 40, 1, 1);
    OctoGraphics::Vertex w(0, 0, 1, 1);
    OctoGraphics::Matrix m;

    /* Variables for X11 */
    Display* display;
    Window window;
    XEvent event;
    int s;
    
    display = XOpenDisplay(NULL);

    if (display == NULL) {
        std::cout << "Cannot open display\n";
        exit(1);
    }

    s = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 800, 600, 1,
                           BlackPixel(display, s), WhitePixel(display, s));

    XSelectInput(display, window, ExposureMask |  KeyPressMask);
    XMapWindow(display, window);

    while (true) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            for (int i = 0; i < 600; ++i) {
                for (int j = 0; j < 800; ++j) {
                    XDrawPoint(display, window, DefaultGC(display, s), i, j);
                }
            }
        }
    }

    XCloseDisplay(display);

    color.set_rgb(100, 100, 100);
    img.clear(color);

    color.set_rgb(0, 0, 0);
    img.set_color(color);
    m.identity();
    m.orthographic(-100, 100, -100, 100, 0, -100);
    m.viewport(800, 600);

    for (int k = 0; k < 4; ++k) {
        std::cout << m.apply(v)[k] << ' ';
    }

    std::cout << "\n";

    for (int k = 0; k < 4; ++k) {
        std::cout << m.apply(w)[k] << ' ';
    }

    std::cout << "\n";

    img.draw_simple_line(m.apply(v), m.apply(w));
    img.save("imagem.ppm");
    
    return 0;
}
