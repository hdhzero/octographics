#include "Image.h"

namespace OctoGraphics {

Image::Image(int w, int h) {
    alloc(w, h);
}

void Image::alloc(int w, int h) {
    width = w;
    height = h;

    drawing.resize(height);

    for (int i = 0; i < height; ++i) {
        drawing[i].resize(width);
    }
}

void Image::setPixel(int x, int y) {
    drawing[x][y] = color;

}

void Image::set_pixel(int i, int j, Color& c) {
    drawing[i][j].set_color(c);
}

void Image::set_color(Color& c) {
    color = c;
}

void Image::clear(Color& c) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            drawing[i][j].set_color(c);
        }
    }
}

void Image::save(std::string filename) {
    std::ofstream file;
    file.open(filename.c_str());

    file << "P3\n" << width << ' ' << height
        << "\n255\n";

    std::stringstream ss;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ss << drawing[i][j].get_red() << ' '
                << drawing[i][j].get_green() << ' '
                << drawing[i][j].get_blue() << '\n';
        }
    }

    file << ss.str();
    file.close();
}


void Image::open(std::string filename) {
    std::ifstream file;
    std::string tmp;
    int w, h, t;
    
    file >> tmp;
    file >> w >> h;
    alloc(w, h);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> w >> h >> t;
            drawing[i][j].set_rgb(w, h, t);
        }
    }
}

void Image::draw_simple_line(const Vertex& v1, const Vertex& v2) {
    int p1x = v1[0];
    int p1y = v1[1];
    int p2x = v2[0];
    int p2y = v2[1];

    int F, x, y;

    if (p1x > p2x)  // Swap points if p1 is on the right of p2
    {
        std::swap(p1x, p2x);
        std::swap(p1y, p2y);
    }

    // Handle trivial cases separately for algorithm speed up.
    // Trivial case 1: m = +/-INF (Vertical line)
    if (p1x == p2x)
    {
        if (p1y > p2y)  // Swap y-coordinates if p1 is above p2
        {
            std::swap(p1y, p2y);
        }

        x = p1x;
        y = p1y;
        while (y <= p2y)
        {
            setPixel(x, y);
            y++;
        }
        return;
    }
    // Trivial case 2: m = 0 (Horizontal line)
    else if (p1y == p2y)
    {
        x = p1x;
        y = p1y;

        while (x <= p2x)
        {
            setPixel(x, y);
            x++;
        }
        return;
    }


    int dy            = p2y - p1y;  // y-increment from p1 to p2
    int dx            = p2x - p1x;  // x-increment from p1 to p2
    int dy2           = (dy << 1);  // dy << 1 == 2*dy
    int dx2           = (dx << 1);
    int dy2_minus_dx2 = dy2 - dx2;  // precompute constant for speed up
    int dy2_plus_dx2  = dy2 + dx2;


    if (dy >= 0)    // m >= 0
    {
        // Case 1: 0 <= m <= 1 (Original case)
        if (dy <= dx)   
        {
            F = dy2 - dx;    // initial F

            x = p1x;
            y = p1y;
            while (x <= p2x)
            {
                setPixel(x, y);
                if (F <= 0)
                {
                    F += dy2;
                }
                else
                {
                    y++;
                    F += dy2_minus_dx2;
                }
                x++;
            }
        }
        // Case 2: 1 < m < INF (Mirror about y=x line
        // replace all dy by dx and dx by dy)
        else
        {
            F = dx2 - dy;    // initial F

            y = p1y;
            x = p1x;
            while (y <= p2y)
            {
                setPixel(x, y);
                if (F <= 0)
                {
                    F += dx2;
                }
                else
                {
                    x++;
                    F -= dy2_minus_dx2;
                }
                y++;
            }
        }
    }
    else    // m < 0
    {
        // Case 3: -1 <= m < 0 (Mirror about x-axis, replace all dy by -dy)
        if (dx >= -dy)
        {
            F = -dy2 - dx;    // initial F

            x = p1x;
            y = p1y;
            while (x <= p2x)
            {
                setPixel(x, y);
                if (F <= 0)
                {
                    F -= dy2;
                }
                else
                {
                    y--;
                    F -= dy2_plus_dx2;
                }
                x++;
            }
        }
        // Case 4: -INF < m < -1 (Mirror about x-axis and mirror 
        // about y=x line, replace all dx by -dy and dy by dx)
        else    
        {
            F = dx2 + dy;    // initial F

            y = p1y;
            x = p1x;
            while (y >= p2y)
            {
                setPixel(x, y);
                if (F <= 0)
                {
                    F += dx2;
                }
                else
                {
                    x++;
                    F += dy2_plus_dx2;
                }
                y--;
            }
        }
    }
}

void Image::render_to_X(Display*& display, Window& drawable, int s) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (drawing[i][j].get_red() == 0) {
                XDrawPoint(display, drawable, DefaultGC(display, s), i, j);
            }
        }
    }
}

} //End of namespace

