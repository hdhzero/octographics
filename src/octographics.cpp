#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <X11/Xlib.h>
#include <unistd.h>
#include "OctoGraphics.h"

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);
    OctoGraphics::Vertex v(10, 40, 1, 1);
    OctoGraphics::Vertex w(0, 0, 1, 1);
    OctoGraphics::Matrix m;

    color.set_rgb(100, 100, 100);
    img.clear(color);

    color.set_rgb(0, 0, 0);
    img.set_color(color);
    m.identity();
    m.orthographic(-100, 100, -100, 100, 0, -100);
    m.viewport(800, 600);


    img.draw_simple_line(m.apply(v), m.apply(w));

    Display *display;
    Window window;
    XEvent event;
    int s;
 
    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
 
    s = DefaultScreen(display);
 
    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 800, 600, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */
    XSelectInput(display, window, ExposureMask | KeyPressMask);
 
    /* map (show) the window */
    XMapWindow(display, window);
 
    /* event loop */
    while (1) {
//        XNextEvent(display, &event);
        int f = XCheckWindowEvent(display, window, KeyPressMask, &event);
 
        /* exit on key press */
        if (event.type == KeyPress && f == 1) {
            // cat /usr/include/X11/keysymdef.h | less

            if (XLookupKeysym(&event.xkey, 0) == 0xff52)
                v[0]++;
            else
                v[0]--;
            std::cout << "ak: " << v[0] << std::endl;

            color.set_rgb(100, 100, 100);
            img.clear(color);
            XClearWindow(display,window);

            color.set_rgb(0, 0, 0);
            img.set_color(color);

            img.draw_simple_line(m.apply(v), m.apply(w));
            img.render_to_X(display, window, s);

    //        XFlush(display);
//            break;
        }

        usleep(50000);
        std::cout << "sleeping\n";
    }
 
    /* close connection to server */
    XCloseDisplay(display);

//    img.save("imagem.ppm");
    
    return 0;
}
