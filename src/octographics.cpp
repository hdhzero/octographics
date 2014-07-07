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
#include <SDL/SDL.h>

using namespace OctoGraphics;
using namespace std;

int obj;
int op;
int coord;
float mfov = 4.0;
bool running = true;
int width  = 640;
int height = 480;

Fixed um(1.0);
SDL_Surface* screen = NULL;

Vertex eye(20.0, 20.0, -20.0, 1);
Vertex gaze(0.0, 0.0, 0.0, 1);
Vertex view_up(0.0, 1.0, 0.0, 0.0);

Color color;
Image img(640, 480);
Matrix m;

void draw_triangle(Vertex p1, Vertex p2, Vertex p3, Color color, Image& img);

uint32_t* get_framebuffer() {
    return (uint32_t*) screen->pixels;
}

void apply_transformations() {
    m.identity();
    m.camera(eye, gaze, view_up);
    //m.orthographic(16.0, -16.0, 12.0, -12.0, -10.0, -100.0);
    m.perspective(Fixed(3.141592/mfov), (Fixed(640.0) / Fixed(480.0)), Fixed(-0.1), Fixed(-200.0));
    m.viewport(640, 480);
}

void print_manipulation_info() {
    std::cout << "values: " << (char) obj 
        << ' ' << (char) op << ' ' << coord << std::endl;

    std::cout << "eye: " << eye[0].to_float() 
        << ' ' << eye[1].to_float() << ' ' << eye[2].to_float() << endl;

    std::cout << "gaze: " << gaze[0].to_float() 
        << ' ' << gaze[1].to_float() << ' ' << gaze[2].to_float() << endl;

    std::cout << "up: " << view_up[0].to_float() 
        << ' ' << view_up[1].to_float() << ' ' << view_up[2].to_float() << endl;
}

void render_to_sdl() {
    SDL_LockSurface(screen);
    img.render_to_SDL(get_framebuffer());
    SDL_UnlockSurface(screen);
    SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error at SDL\n";
        exit(0);
    }

    screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);

    if (!screen) {
        SDL_Quit();
        cout << "SDL_SetVideoMode failed\n";
        exit(0);
    }

    SDL_WM_SetCaption("Octographics", NULL);
}


void handle_inc() {
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

void handle_dec() {
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

void handle_keypress(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_q:
            running = false;
            break;

        case SDLK_r:
            op = 'r'; break;

        case SDLK_t:
            op = 't'; break;

        case SDLK_e:
            obj = 'e'; break;

        case SDLK_g:
            obj = 'g'; break;

        case SDLK_u:
            obj = 'u'; break;

        case SDLK_x:
            coord = 0; break;

        case SDLK_y:
            coord = 1; break;

        case SDLK_z:
            coord = 2; break;

        case SDLK_b:
            um = Fixed(10.0); break;

        case SDLK_n:
            um = Fixed(1.0); break;

        case SDLK_m:
            um = Fixed(0.1); break;

        case SDLK_i:
            mfov += 1.0; break;
            
        case SDLK_k:
            mfov -= 1.0; break;

        case SDLK_w:
            handle_inc(); break;

        case SDLK_s:
            handle_dec(); break;
    }
}

void handle_event(SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_KEYDOWN:
            handle_keypress(event);
            break;

        default:
            break;
    }
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

        void change_color(Color& c) {
            int r = c.get_red();
            int g = c.get_green();
            int b = c.get_blue();

            c.set_rgb(g, b, r);
        }

        void draw_objs2(OctoGraphics::Matrix& mt, OctoGraphics::Image& img) {
            Vertex v1, v2, v3;
            int sz;
            Color c;
            c.set_rgb(0, 255, 0);

            for (int i = 0; i < faces.size(); ++i) {
                v1 = mt.apply(faces[i][0]);
                v2 = mt.apply(faces[i][1]);
                v3 = mt.apply(faces[i][2]);

                draw_triangle(v1, v2, v3, c, img);
                change_color(c);
            }
        }
};


void print_info() {
    Matrix m;

    OctoGraphics::Vertex eye(100.0, 100.0, 100.0, 1.0);
    OctoGraphics::Vertex gaze(0.0, 0.0, 0.0, 1.0);
    OctoGraphics::Vertex view_up(0.0, 1.0, 0.0, 0.0);

    cout << "Camera\n";
    m.identity();
    m.camera(eye, gaze, view_up);
    m.print();

    cout << "Perspective\n";
    m.identity();
    m.perspective(Fixed(3.141592/4.0), Fixed(640.0 / 480.0), Fixed(-0.1), Fixed(-20.0));
    m.print();

    cout << "Ortho\n";
    m.identity();
    m.orthographic(16.0, -16.0, 12.0, -12.0, -10.0, -100.0);
    m.print();

    cout << "Viewport\n";
    m.identity();
    m.viewport(640, 480);
    m.print();

    cout << "Transforms\n";
    m.identity();
    m.scale(Fixed(3.0), Fixed(-2.0), Fixed(9.0));
    m.translate(Fixed(100.0), Fixed(-50.0), Fixed(30.0));
    m.rotate(Fixed(3.141592), Fixed(0.0), Fixed(0.0));
    m.translate(Fixed(100.0), Fixed(-50.0), Fixed(30.0));
    m.print();

    cout << "All together\n";
    m.identity();
    m.scale(Fixed(3.0), Fixed(-2.0), Fixed(9.0));
    m.translate(Fixed(100.0), Fixed(-50.0), Fixed(30.0));
    m.rotate(Fixed(3.141592), Fixed(0.0), Fixed(0.0));
    m.translate(Fixed(100.0), Fixed(-50.0), Fixed(30.0));
    m.camera(eye, gaze, view_up);
    m.perspective(Fixed(3.141592/4.0), Fixed(640.0 / 480.0), Fixed(-0.1), Fixed(-20.0));
    Vertex objn2 = m.apply(Vertex(Fixed(0.0), Fixed(0.0), Fixed(100.0), Fixed(1.0)));
    m.print();
    cout << "\n-------\n";
    m.viewport(640, 480);
    m.print();

    Vertex objn = m.apply(Vertex(Fixed(0.0), Fixed(0.0), Fixed(100.0), Fixed(1.0)));

    objn.print();
    objn[0] = objn[0] / objn[3];
    objn[1] = objn[1] / objn[3];
    objn[2] = objn[2] / objn[3];
    objn[3] = objn[3] / objn[3];
    objn.print();

    objn2.print();
    objn2[0] = objn2[0] / objn2[3];
    objn2[1] = objn2[1] / objn2[3];
    objn2[2] = objn2[2] / objn2[3];
    objn2[3] = objn2[3] / objn2[3];
    objn2.print();

    m.identity();
    m.perspective(Fixed(3.141592/4.0), Fixed(640.0 / 480.0), Fixed(-0.1), Fixed(-20.0));
    m.viewport(640, 480);
    objn2 = m.apply(Vertex(Fixed(0.0), Fixed(0.0), Fixed(100.0), Fixed(1.0)));

    objn2[0] = objn2[0] / objn2[3];
    objn2[1] = objn2[1] / objn2[3];
    objn2[2] = objn2[2] / objn2[3];
    objn2[3] = objn2[3] / objn2[3];

    cout << "vertex at\n";
    objn2.print();

}

Fixed max(Fixed a, Fixed b) {
    if (a.to_float() > b.to_float()) {
        return a;
    } else {
        return b;
    }
}

Fixed min(Fixed a, Fixed b) {
    if (a.to_float() < b.to_float()) {
        return a;
    } else {
        return b;
    }
}

Fixed clamp(Fixed value, Fixed mn, Fixed mx) {
    return max(mn, min(value, mx));
}

Fixed clamp(Fixed value) {
    return max(Fixed(0.0), min(value, Fixed(1.0)));
}

Fixed interpolate(Fixed mn, Fixed mx, Fixed gradient) {
    return mn + (mx - mn) * clamp(gradient);
}

void process_scanline(int y, Vertex pa, Vertex pb, Vertex pc, Vertex pd, Color color, Image& img) {
    Fixed gradient1(1.0);
    Fixed gradient2(1.0);
    Fixed yy((float) y);

    if (pa[1].to_float() != pb[1].to_float()) {
        gradient1 = (yy - pa[1]) / (pb[1] - pa[1]);
    }

    if (pc[1].to_float() != pd[1].to_float()) {
        gradient2 = (yy - pc[1]) / (pd[1] - pc[1]);
    }

    yy = interpolate(pa[0] / pa[3], pb[0] / pb[3], gradient1);
    int sx = yy.to_float();
    yy = interpolate(pc[0] / pc[3], pd[0] / pd[3], gradient2);
    int ex = yy.to_float();

    Fixed z1 = interpolate(pa[2], pb[2], gradient1);
    Fixed z2 = interpolate(pc[2], pd[2], gradient2);

    for (int x = sx; x < ex; ++x) {
        Fixed gradient = Fixed((x - sx) / (float)(ex - sx));
        Fixed z = interpolate(z1, z2, gradient);

        Fixed ax((float) x);
        Fixed ay((float) y);
        Vertex av(ax, ay, z, Fixed(1.0));
/*

cout << "grads: " << gradient1.to_float() << ' ' << gradient2.to_float() 
<< ' ' << gradient.to_float() << ' ' << z.to_float() 
<< ' ' << z1.to_float() << ' ' << z2.to_float() 
<< ": " << pa[2].to_float() << ' ' << pb[2].to_float() << endl;*/
        img.draw_point(av, color);
//        img.draw_point(x, y, color);
        //cin >> x;
    }
}

void draw_triangle(Vertex p1, Vertex p2, Vertex p3, Color color, Image& img) {
    Vertex tmp;

    if (p1[1].to_float() > p2[1].to_float()) {
        tmp = p2;
        p2 = p1;
        p1 = tmp;
    }

    if (p2[1].to_float() > p3[1].to_float()) {
        tmp = p2;
        p2 = p3;
        p3 = tmp;
    }

    if (p1[1].to_float() > p2[1].to_float()) {
        tmp = p2;
        p2 = p1;
        p1 = tmp;
    }

    Fixed dP1P2, dP1P3;

    if ((p2[1].to_float() - p1[1].to_float()) > 0.0) {
        dP1P2 = (p2[0] - p1[0]) / (p2[1] - p1[1]);
    } else {
        dP1P2 = Fixed(0.0);
    }

    if ((p3[1].to_float() - p1[1].to_float()) > 0.0) {
        dP1P3 = (p3[0] - p1[0]) / (p3[1] - p1[1]);
    } else {
        dP1P3 = Fixed(0.0);
    }

    if (dP1P2.to_float() > dP1P3.to_float()) {
        for (int y = p1[1].to_float() / p1[3].to_float(); 
y <= p3[1].to_float() / p3[3].to_float(); ++y) {
            if (y < p2[1].to_float() / p2[3].to_float()) {
                process_scanline(y, p1, p3, p1, p2, color, img);
            } else {
                process_scanline(y, p1, p3, p2, p3, color, img);
            }
        }
    } else {
        for (int y = p1[1].to_float() / p1[3].to_float(); 
y <= p3[1].to_float() / p3[3].to_float(); ++y) {
            if (y < p2[1].to_float() / p2[3].to_float()) {
                process_scanline(y, p1, p2, p1, p3, color, img);
            } else {
                process_scanline(y, p2, p3, p1, p3, color, img);
            }
        }
    }
}

void draw_axis() {
    OctoGraphics::Vertex X(10.0, 0, 0, 1);
    OctoGraphics::Vertex Y(0, 10.0, 0, 1);
    OctoGraphics::Vertex Z(0, 0, 10.0, 1);
    OctoGraphics::Vertex w(0, 0, 0, 1);

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
}

int main(int argc, char** argv) {
    Objs objs;
    std::string filename(argv[1]);
    objs.read_obj(filename);

    init_sdl();
    print_info();

    /* event loop */
    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            handle_event(event);
        }

        color.set_rgb(255, 255, 255);
        img.clear(color);
        apply_transformations();
        draw_axis();
        objs.draw_objs2(m, img);
        render_to_sdl();

        usleep(1000 * 50);
    }
 
    /* close connection to server */
    SDL_Quit();
    img.save("imagem.ppm");
    
    return 0;
}
