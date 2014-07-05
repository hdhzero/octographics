#include "OctoGraphics.h"

namespace OctoGraphics {

Vertex::Vertex() {
    Fixed a(0.0);

    c[0] = a;
    c[1] = a;
    c[2] = a;
    c[3] = a;
}

Vertex::Vertex(Fixed x, Fixed y, Fixed z, Fixed w) {
    c[0] = x;
    c[1] = y;
    c[2] = z;
    c[3] = w;
}

Vertex::Vertex(double x, double y, double z, double w) {
    c[0] = Fixed(x);
    c[1] = Fixed(y);
    c[2] = Fixed(z);
    c[3] = Fixed(w);
}

Fixed& Vertex::operator[](int idx) {
    return c[idx];
}

const Fixed& Vertex::operator[](int idx) const {
    return c[idx];
}

Vertex& Vertex::operator+=(const Vertex& vertex) {
    c[0] = c[0] + vertex.c[0];
    c[1] = c[1] + vertex.c[1];
    c[2] = c[2] + vertex.c[2];

    return (*this);
}

Vertex& Vertex::operator-=(const Vertex& vertex) {
    c[0] = c[0] - vertex.c[0];
    c[1] = c[1] - vertex.c[1];
    c[2] = c[2] - vertex.c[2];

    return (*this);
}

Vertex& Vertex::operator*=(Fixed t) {
    c[0] = c[0] * t;
    c[1] = c[1] * t;
    c[2] = c[2] * t;

    return (*this);
}

Vertex& Vertex::operator/=(Fixed t) {
    c[0] = c[0] / t;
    c[1] = c[1] / t;
    c[2] = c[2] / t;

    return (*this);
}

Vertex Vertex::operator-() const {
    Fixed a(-c[0].num);
    Fixed b(-c[1].num);
    Fixed cc(-c[2].num);
    Fixed d(c[3].num);

    return Vertex(a, b, cc, d);
}

Vertex Vertex::operator+(const Vertex& vertex) const {
    Vertex tmp;
    Fixed f = c[3] + vertex[3];

    tmp[0] = c[0] + vertex[0];
    tmp[1] = c[1] + vertex[1];
    tmp[2] = c[2] + vertex[2];

    if (f.to_float() >= 1) {
        tmp[3] = Fixed(1.0);
    } else {
        tmp[3] = Fixed(0.0);
    }

    return tmp;
}

Vertex Vertex::operator-(const Vertex& vertex) const {
    Vertex tmp;

    tmp[0] = c[0] - vertex[0];
    tmp[1] = c[1] - vertex[1];
    tmp[2] = c[2] - vertex[2];
    tmp[3] = Fixed(0.0);

    return tmp;
}

Fixed Vertex::operator*(const Vertex& vertex) const {
    Fixed tmp = c[0] * vertex[0];

    tmp = tmp + c[1] * vertex[1];
    tmp = tmp + c[2] * vertex[2];

    return tmp;
}

/* It is important to remember that cross product is performed
 * between vectors (whose coordinate w = 0.0), not between points, that
 * have coordinate w = 1.0. Thus, only vectors can be passed as argument
 * to cross method
 */
Vertex Vertex::cross(const Vertex& vertex) const {
    Vertex tmp;

    tmp[0] = c[1] * vertex[2] - c[2] * vertex[1];
    tmp[1] = c[2] * vertex[0] - c[0] * vertex[2];
    tmp[2] = c[0] * vertex[1] - c[1] * vertex[0];
    tmp[3] = 0.0; //zero because it is a vector, not a point

    return tmp;
}

Fixed Vertex::length() {
    Fixed tmp(0.0);

    for (int i = 0; i < 3; ++i) {
        tmp = tmp + c[i] * c[i];
    }

    return Fixed(sqrt(tmp.to_float()));
}

Vertex Vertex::operator*(Fixed t) const {
    Vertex tmp;

    tmp[0] = c[0] * t;
    tmp[1] = c[1] * t;
    tmp[2] = c[2] * t;

    return tmp;
}

Vertex Vertex::operator/(Fixed t) const {
    Vertex tmp;

    tmp[0] = c[0] / t;
    tmp[1] = c[1] / t;
    tmp[2] = c[2] / t;

    return tmp;
}

bool Vertex::operator==(const Vertex& vertex) const {
    return c[0].num == vertex[0].num && c[1].num == vertex[1].num
        && c[2].num == vertex[2].num && c[3].num == vertex[3].num;
}

bool Vertex::operator!=(const Vertex& vertex) const {
    return !(c[0].num == vertex[0].num && c[1].num == vertex[1].num
        && c[2].num == vertex[2].num && c[3].num == vertex[3].num);
}

void Vertex::print() {
    std::cout << "{ ";
    for (int i = 0; i < 3; ++i) {
        std::cout << c[i].to_float() << ", ";
    }

    std::cout << c[3].to_float() << " }\n";
}

}
