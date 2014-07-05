#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <X11/Xlib.h>
#include "/usr/include/X11/keysymdef.h"
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "OctoGraphics.h"

using namespace OctoGraphics;
using namespace std;

XEvent event;
bool k(char c) {
    return  (XLookupKeysym(&event.xkey, 0) == c);
}

class Objs {
    public:
        std::vector<std::vector<OctoGraphics::Vertex> > faces;

    public:
        void read_obj(std::string filename) {
            std::ifstream file;
            std::string tmp;
            std::vector<OctoGraphics::Vertex> vertices;
            float v1, v2, v3;
            int idx;

            file.open(filename.c_str());

            while (file.good()) {
                getline(file, tmp);

                if (tmp[0] != 'f' && tmp[0] != 'v') continue;
                if (tmp[0] == 'v' && tmp[1] == 't') continue;

                std::stringstream ss;
                if (tmp[0] == 'v') {
                    ss << tmp;
                    ss >> tmp >> v1 >> v2 >> v3;
                    vertices.push_back(Vertex(v1 / 1.0, v2 / 1.0, v3 / 1.0, 1.0));
                } else {
                    ss << tmp;
                    ss >> tmp;
                    faces.push_back(std::vector<OctoGraphics::Vertex>());

                    while (ss >> idx) {
                        faces[faces.size() - 1].push_back(vertices[idx - 1]);
                    }
                };
            }
        }

        void draw_objs(OctoGraphics::Matrix& mt, OctoGraphics::Image& img) {
            Vertex v1;
            Vertex v2;
            int sz;

            for (int i = 0; i < faces.size(); ++i) {
                sz = faces[i].size();

                for (int j = 0; j <= faces[i].size(); ++j) {
                    v1 = faces[i][j % sz];
                    v2 = faces[i][(j + 1) % sz];
                    img.draw_simple_line(mt.apply(v1), mt.apply(v2));
                }
            }
        }
};

std::vector<OctoGraphics::Vertex> cube(float sz) {
    std::vector<OctoGraphics::Vertex> tmp;
    tmp.push_back(OctoGraphics::Vertex(0.0, 0.0, 0.0, 1.0));
    tmp.push_back(OctoGraphics::Vertex(sz, 0.0, 0.0, 1.0));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 0, 1.0));
    tmp.push_back(OctoGraphics::Vertex(0, sz, 0, 1.0));

    tmp.push_back(OctoGraphics::Vertex(sz, 0, 0, 1.0));
    tmp.push_back(OctoGraphics::Vertex(sz, sz, 0, 1.0));

    tmp.push_back(OctoGraphics::Vertex(0, sz, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(sz, sz, 0, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 0, sz, 1));

    tmp.push_back(OctoGraphics::Vertex(0, sz, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(0, sz, sz, 1));

    tmp.push_back(OctoGraphics::Vertex(sz, sz, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(sz, sz, sz, 1));

    tmp.push_back(OctoGraphics::Vertex(sz, 0, 0, 1));
    tmp.push_back(OctoGraphics::Vertex(sz, 0, sz, 1));

    tmp.push_back(OctoGraphics::Vertex(0, sz, sz, 1));
    tmp.push_back(OctoGraphics::Vertex(sz, sz, sz, 1));

    tmp.push_back(OctoGraphics::Vertex(0, 0, sz, 1));
    tmp.push_back(OctoGraphics::Vertex(sz, 0, sz, 1));

    tmp.push_back(OctoGraphics::Vertex(sz, sz, sz,1));
    tmp.push_back(OctoGraphics::Vertex(sz, 0, sz, 1));

    tmp.push_back(OctoGraphics::Vertex(0, sz, sz, 1));
    tmp.push_back(OctoGraphics::Vertex(0, 0, sz, 1));

    return tmp;
}

void draw_cube(OctoGraphics::Matrix& mt, OctoGraphics::Image& img, float sz) {
    std::vector<OctoGraphics::Vertex> cb = cube(sz);

    for (int q = 0; q < cb.size(); q += 2) {
        img.draw_simple_line(mt.apply(cb[q]), mt.apply(cb[q+1]));
    }
}

void draw_spin_cube(Image& img, float sz) {
    Matrix m;
    static float angle = 1.0f;
    OctoGraphics::Vertex eye(0.0, 10.0, 10.0, 1.0);
    OctoGraphics::Vertex gaze(0.0, 0.0, -100.0, 1.0);
    OctoGraphics::Vertex view_up(0.0, 1.0, 0.0, 0.0);


    m.identity();
    m.rotate(Fixed(angle), Fixed(0.0), Fixed(0.0));
    m.translate(Fixed(0.5f), Fixed(0.0f), Fixed(1.0f));
    m.camera(eye, gaze, view_up);
    m.perspective(Fixed(3.141592/4.0), (Fixed(640.0) / Fixed(480.0)), Fixed(-0.1), Fixed(-100.0));
    m.viewport(640, 480);
    
    draw_cube(m, img, sz);
    angle += 0.5f;
}

int main(int argc, char** argv) {
    OctoGraphics::Color color;
    OctoGraphics::Image img(640, 480);

    OctoGraphics::Vertex X(10.0, 0, 0, 1);
    OctoGraphics::Vertex Y(0, 10.0, 0, 1);
    OctoGraphics::Vertex Z(0, 0, 10.0, 1);

    OctoGraphics::Vertex w(0, 0, 0, 1);
    OctoGraphics::Vertex eye(10.0, 10.0, 10.0, 1);
    OctoGraphics::Vertex gaze(0.0, 0.0, 0.0, 1);
    OctoGraphics::Vertex view_up(0.0, 1.0, 0.0, 0.0);
    OctoGraphics::Matrix m, mm;
    Objs objs;
    std::string filename(argv[1]);
    objs.read_obj(filename);
    //objs.read_obj("/home/hdhzero/untitled2.obj");
    //objs.read_obj("/home/hdhzero/untitled.obj");

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

    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 640, 480, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */

    XSelectInput(display, window, ExposureMask | KeyPressMask);
 
    /* map (show) the window */

    XMapWindow(display, window);

    int obj;
    int op;
    int coord;
    float mfov = 4.0;
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
            if (k('p')) { um = Fixed(0.1); } //minor; }
            if (k('i')) { mfov += 1.0; }
            if (k('k')) { mfov -= 1.0; }
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
            m.camera(eye, gaze, view_up);
            //m.perp(Fixed(-10.0), Fixed(-100.0));
//            m.orthographic(20.0, -20.0, 15.0, -15.0, -10, -100);
            m.orthographic(16.0, -16.0, 12.0, -12.0, -10, -100);
            //m.orthographic(-20.0, 20.0, -15.0, 15.0, -10, -100);
//            m.perspective(Fixed(3.141592/mfov), (Fixed(640.0) / Fixed(480.0)), Fixed(-10.1), Fixed(-20.0));

            color.set_rgb(0, 255, 255);
            img.set_color(color);
            std::cout << "1vec\n";
            img.draw_simple_line(X, w);
            std::cout << "2vec\n";
            m.print();
            std::cout << "---\n";
            m.viewport(640, 480);
            m.print();
            X.print();
            m.apply(X).print();
            m.apply(Y).print();
            m.apply(Z).print();
            img.draw_simple_line(m.apply(X), m.apply(w));
            std::cout << "3vec\n";

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
            draw_cube(m, img, 1.1);
            draw_spin_cube(img, 1.1);
            objs.draw_objs(m, img);

            img.render_to_X(display, window, s);
            std::cout << "herez\n";
            std::cout << "eye: " << eye[0].to_float() << ' ' << eye[1].to_float() << ' ' << eye[2].to_float() << endl;
            std::cout << "gaze: " << gaze[0].to_float() << ' ' << gaze[1].to_float() << ' ' << gaze[2].to_float() << endl;
            std::cout << "up: " << view_up[0].to_float() << ' ' << view_up[1].to_float() << ' ' << view_up[2].to_float() << endl;

            XFlush(display);
//            break;
        }

        usleep(50000);

    }
 
    /* close connection to server */

    XCloseDisplay(display);

    img.save("imagem.ppm");
    
    return 0;
}
