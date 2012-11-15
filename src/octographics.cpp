#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <X11/Xlib.h>
#include "/usr/include/X11/keysymdef.h"
#include <unistd.h>
#include "OctoGraphics.h"

XEvent event;
bool k(char c) {
    std::cout << "tecla: " <<  XLookupKeysym(&event.xkey, 0) << std::endl;

    return  (XLookupKeysym(&event.xkey, 0) == c);
}

std::vector<OctoGraphics::Vertex> cube() {
    std::vector<OctoGraphics::Vertex> tmp;
    tmp.push_back(OctoGraphics::Vertex(0, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(10, 0, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 10, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(10, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(10, 10, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 10, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(10, 10, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 0, 10, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 10, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 10, 10, 1));

    tmp.push_back(OctoGraphics::Vertex(10, 10, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(10, 10, 10, 1));

    tmp.push_back(OctoGraphics::Vertex(10, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(10, 0, 10, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 10, 10, 1));
    tmp.push_back(OctoGraphics::Vertex(10, 10, 10, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 10,1));
    tmp.push_back(OctoGraphics::Vertex(10, 0, 10,1));

    tmp.push_back(OctoGraphics::Vertex(10, 10, 10,1));
    tmp.push_back(OctoGraphics::Vertex(10, 0, 10,1));

    tmp.push_back(OctoGraphics::Vertex(0, 10, 10,1));
    tmp.push_back(OctoGraphics::Vertex(0, 0, 10,1));

    return tmp;
}

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);

    OctoGraphics::Vertex X(10, 0, 0, 1);
    OctoGraphics::Vertex Y(0, 10, 0, 1);
    OctoGraphics::Vertex Z(0, 0, 10, 1);

    OctoGraphics::Vertex w(0, 0, 0, 1);
    OctoGraphics::Vertex eye(0, 0, 2, 1);
    OctoGraphics::Vertex gaze(0, 0, -1, 0);
    OctoGraphics::Vertex view_up(0, 1, 0, 0);
    OctoGraphics::Matrix m;

    color.set_rgb(100, 100, 100);
    img.clear(color);

    color.set_rgb(0, 0, 0);
    img.set_color(color);
    m.identity();
    m.print();
    m.camera(eye, gaze, view_up);
    m.print();
    m.orthographic(-100, 100, -100, 100, 0, -100);
    m.print();
    m.viewport(800, 600);
    m.print();

    m.print();

    Display *display;
    Window window;

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

    int obj;
    int op;
    int coord;
    /* event loop */
    while (1) {
//        XNextEvent(display, &event);
        int f = XCheckWindowEvent(display, window, KeyPressMask, &event);
 
        /* exit on key press */
        if (event.type == KeyPress && f == 1) {
            if (k('r')) { op = 'r'; }
            if (k('t')) { op = 't'; }
            if (k('e')) { obj = 'e'; }
            if (k('g')) { obj = 'g'; }
            if (k('u')) { obj = 'u'; }
            if (k('x')) { coord = 0; }
            if (k('y')) { coord = 1; }
            if (k('z')) { coord = 2; }

            if (k('w')) {
                if (obj == 'e' && op == 't') {
                    eye[coord]++;
                }
                if (obj == 'g' && op == 't') {
                    gaze[coord]++;
                }
                if (obj == 'u' && op == 't') {
                    view_up[coord]++;
                }
                if (obj == 'e' && op == 'r') {
                    OctoGraphics::Matrix tmp;
                    tmp.identity();
                    if (coord == 0) { tmp.rotate(0.1, 0, 0); }
                    if (coord == 1) { tmp.rotate(0, 0.1, 0); }
                    if (coord == 2) { tmp.rotate(0, 0, 0.1); }
                    eye = tmp.apply(eye);
                }
                if (obj == 'g' && op == 'r') {
                    OctoGraphics::Matrix tmp;
                    tmp.identity();
                    if (coord == 0) { tmp.rotate(0.1, 0, 0); }
                    if (coord == 1) { tmp.rotate(0, 0.1, 0); }
                    if (coord == 2) { tmp.rotate(0, 0, 0.1); }
                    gaze = tmp.apply(gaze);
                }
                if (obj == 'u' && op == 'r') {
                    OctoGraphics::Matrix tmp;
                    tmp.identity();
                    if (coord == 0) { tmp.rotate(0.1, 0, 0); }
                    if (coord == 1) { tmp.rotate(0, 0.1, 0); }
                    if (coord == 2) { tmp.rotate(0, 0, 0.1); }
                    view_up = tmp.apply(view_up);
                }


            }

            if (k('s')) {
                if (obj == 'e' && op == 't') {
                    eye[coord]--;
                }
                if (obj == 'g' && op == 't') {
                    gaze[coord]--;
                }
                if (obj == 'u' && op == 't') {
                    view_up[coord]--;
                }
                if (obj == 'e' && op == 'r') {
                    OctoGraphics::Matrix tmp;
                    tmp.identity();
                    if (coord == 0) { tmp.rotate(-0.1, 0, 0); }
                    if (coord == 1) { tmp.rotate(0, -0.1, 0); }
                    if (coord == 2) { tmp.rotate(0, 0, -0.1); }
                    eye = tmp.apply(eye);
                }
                if (obj == 'g' && op == 'r') {
                    OctoGraphics::Matrix tmp;
                    tmp.identity();
                    if (coord == 0) { tmp.rotate(-0.1, 0, 0); }
                    if (coord == 1) { tmp.rotate(0, -0.1, 0); }
                    if (coord == 2) { tmp.rotate(0, 0, -0.1); }
                    gaze = tmp.apply(gaze);
                }
                if (obj == 'u' && op == 'r') {
                    OctoGraphics::Matrix tmp;
                    tmp.identity();
                    if (coord == 0) { tmp.rotate(-0.1, 0, 0); }
                    if (coord == 1) { tmp.rotate(0, -0.1, 0); }
                    if (coord == 2) { tmp.rotate(0, 0, -0.1); }
                    view_up = tmp.apply(view_up);
                }

            }

            std::cout << "values: " << obj << ' ' << op << ' ' << coord << std::endl;
            // cat /usr/include/X11/keysymdef.h | less


            color.set_rgb(100, 100, 100);
            img.clear(color);
            XClearWindow(display,window);

            color.set_rgb(0, 0, 0);
            img.set_color(color);

            m.identity();
            m.print();
            m.camera(eye, gaze, view_up);
            m.print();
            m.orthographic(-100, 100, -100, 100, 0, -100);
            m.print();
            m.viewport(800, 600);
            m.print();


            img.draw_simple_line(m.apply(X), m.apply(w));
            img.draw_simple_line(m.apply(Y), m.apply(w));
            img.draw_simple_line(m.apply(Z), m.apply(w));

            std::vector<OctoGraphics::Vertex> cb = cube();

            for (int q = 0; q < cb.size(); q += 2) {
                img.draw_simple_line(m.apply(cb[q]), m.apply(cb[q+1]));
            }

            img.render_to_X(display, window, s);
            std::cout << "herez\n";

    //        XFlush(display);
//            break;
        }

        usleep(50000);

    }
 
    /* close connection to server */
    XCloseDisplay(display);

//    img.save("imagem.ppm");
    
    return 0;
}
