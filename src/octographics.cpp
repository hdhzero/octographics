#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <X11/Xlib.h>
#include "/usr/include/X11/keysymdef.h"
#include <unistd.h>
#include "OctoGraphics.h"

using namespace OctoGraphics;
using namespace std;

XEvent event;
bool k(char c) {
//    std::cout << "tecla: " <<  XLookupKeysym(&event.xkey, 0) << std::endl;

    return  (XLookupKeysym(&event.xkey, 0) == c);
}

std::vector<OctoGraphics::Vertex> cube() {
    std::vector<OctoGraphics::Vertex> tmp;
    tmp.push_back(OctoGraphics::Vertex(0.0, 0.0, 0.0, 1.0));
    tmp.push_back(OctoGraphics::Vertex(1.0, 0.0, 0.0, 1.0));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 1, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(1, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(1, 1, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 1, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(1, 1, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 0, 1, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 1, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 1, 1, 1));

    tmp.push_back(OctoGraphics::Vertex(1, 1, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(1, 1, 1, 1));

    tmp.push_back(OctoGraphics::Vertex(1, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(1, 0, 1, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 1, 1, 1));
    tmp.push_back(OctoGraphics::Vertex(1, 1, 1, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 1, 1));
    tmp.push_back(OctoGraphics::Vertex(1, 0, 1, 1));

    tmp.push_back(OctoGraphics::Vertex(1, 1, 1,1));
    tmp.push_back(OctoGraphics::Vertex(1, 0, 1,1));

    tmp.push_back(OctoGraphics::Vertex(0, 1, 1, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 0, 1, 1));

    return tmp;
}

void draw_cube(OctoGraphics::Matrix& mt, OctoGraphics::Image& img) {
    std::vector<OctoGraphics::Vertex> cb = cube();

    for (int q = 0; q < cb.size(); q += 2) {
        img.draw_simple_line(mt.apply(cb[q]), mt.apply(cb[q+1]));
    }
}

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(800, 600);

    OctoGraphics::Vertex X(100.0, 0, 0, 1);
    OctoGraphics::Vertex Y(0, 100.0, 0, 1);
    OctoGraphics::Vertex Z(0, 0, 100.0, 1);

    OctoGraphics::Vertex w(0, 0, 0, 1);
    OctoGraphics::Vertex eye(20.0, 20.0, 20.0, 1);
    OctoGraphics::Vertex gaze(0.0, 0.0, 0.0, 1);
    OctoGraphics::Vertex view_up(0.0, 1.0, 0.0, 0.0);
    OctoGraphics::Matrix m, mm;

    Display *display;
    Window window;
    int s;

    /* open connection with the server */

    display = XOpenDisplay(NULL);
    if (display == NULL) {
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
    OctoGraphics::Fixed um(0.001);
    OctoGraphics::Fixed major(1.0);
    OctoGraphics::Fixed minor(0.001);

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
            if (k('o')) { um = Fixed(1.0); }//major; }
            if (k('p')) { um = Fixed(0.001); } //minor; }
            if (k('q')) { break; }

            if (k('w')) {
                if (obj == 'e' && op == 't') {
                    eye[coord] = eye[coord] + um;
                }
                if (obj == 'g' && op == 't') {
                    gaze[coord] = gaze[coord] + um;
                }
                if (obj == 'u' && op == 't') {
                    view_up[coord] = view_up[coord] + um;
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
                    eye[coord] = eye[coord] - um;
                }
                if (obj == 'g' && op == 't') {
                    gaze[coord] = gaze[coord] - um;
                }
                if (obj == 'u' && op == 't') {
                    view_up[coord] = view_up[coord] - um;
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

            std::cout << "values: " << (char) obj << ' ' << (char) op << ' ' << coord << std::endl;
            // cat /usr/include/X11/keysymdef.h | less


            color.set_rgb(255, 255, 255);
            img.clear(color);
            XClearWindow(display,window);

            color.set_rgb(0, 0, 0);
            img.set_color(color);

            m.identity();
            //m.rotate(0.0, 0.0, 3.141592/4.0);
//            m.rotate(0.0, 0.0, eye[0].to_float());
            //m.translate(100.0, 100.0, 0.0);
//            m.translate(gaze[0].to_float(), gaze[1].to_float(), gaze[2].to_float());
            //m.print();
            m.camera(eye, gaze, view_up);
            //m.print();
            //m.orthographic(20.0, -20.0, 15.0, -15.0, -10, -100);
            //m.orthographic(-20.0, 20.0, -15.0, 15.0, -10, -100);
            m.perspective(Fixed(3.141592/1.1), (Fixed(800.0) / Fixed(600.0)), Fixed(-0.1), Fixed(-200.0));
           //m.print();
            m.viewport(800, 600);
            //m.print();

            color.set_rgb(255, 0, 0);
            img.set_color(color);
            img.draw_simple_line(X, w);
            img.draw_simple_line(m.apply(X), m.apply(w));

            color.set_rgb(0, 255, 0);
            img.set_color(color);
            img.draw_simple_line(Y, w);
            img.draw_simple_line(m.apply(Y), m.apply(w));

            color.set_rgb(0, 0, 255);
            img.set_color(color);
            img.draw_simple_line(Z, w);
            img.draw_simple_line(m.apply(Z), m.apply(w));

            color.set_rgb(0, 0, 0);
            img.set_color(color);
            draw_cube(m, img);

            img.render_to_X(display, window, s);
            std::cout << "herez\n";
            std::cout << "eye: " << eye[0].to_float() << ' ' << eye[1].to_float() << ' ' << eye[2].to_float() << endl;
            std::cout << "gaze: " << gaze[0].to_float() << ' ' << gaze[1].to_float() << ' ' << gaze[2].to_float() << endl;
            m.print();

    //        XFlush(display);
//            break;
        }

        usleep(50000);

    }
 
    /* close connection to server */

    XCloseDisplay(display);

    img.save("imagem.ppm");
    
    return 0;
}
