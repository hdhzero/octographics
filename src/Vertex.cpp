#include "OctoGraphics.h"

namespace OctoGraphics {

Vertex::Vertex(float x, float y, float z, float w) {
    c[0] = x;
    c[1] = y;
    c[2] = z;
    c[3] = w;
}

float& Vertex::operator[](int idx) {
    return c[idx];
}

const float& Vertex::operator[](int idx) const {
    return c[idx];
}

Vertex& Vertex::operator+=(const Vertex& vertex) {
    c[0] += vertex.c[0];
    c[1] += vertex.c[1];
    c[2] += vertex.c[2];
    c[3] += vertex.c[3];

    return (*this);
}

Vertex& Vertex::operator-=(const Vertex& vertex) {
    c[0] -= vertex.c[0];
    c[1] -= vertex.c[1];
    c[2] -= vertex.c[2];
    c[3] -= vertex.c[3];

    return (*this);
}

Vertex& Vertex::operator*=(float t) {
    c[0] *= t;
    c[1] *= t;
    c[2] *= t;
    c[3] *= t;

    return (*this);
}

Vertex& Vertex::operator/=(float t) {
    c[0] /= t;
    c[1] /= t;
    c[2] /= t;
    c[3] /= t;

    return (*this);
}

Vertex Vertex::operator-() const {
    return Vertex(-c[0], -c[1], -c[2], -c[3]);
}

Vertex Vertex::operator+(const Vertex& vertex) const {
    Vertex tmp;

    tmp[0] = c[0] + vertex[0];
    tmp[1] = c[1] + vertex[1];
    tmp[2] = c[2] + vertex[2];
    tmp[3] = c[3] + vertex[3];

    return tmp;
}

Vertex Vertex::operator-(const Vertex& vertex) const {
    Vertex tmp;

    tmp[0] = c[0] - vertex[0];
    tmp[1] = c[1] - vertex[1];
    tmp[2] = c[2] - vertex[2];
    tmp[3] = c[3] - vertex[3];

    return tmp;
}

float Vertex::operator*(const Vertex& vertex) const {
    float tmp = c[0] * vertex[0];

    tmp += c[1] * vertex[1];
    tmp += c[2] * vertex[2];
    tmp += c[3] * vertex[3];

    return tmp;
}

Vertex Vertex::operator*(float t) const {
    Vertex tmp;

    tmp[0] = c[0] * t;
    tmp[1] = c[1] * t;
    tmp[2] = c[2] * t;
    tmp[3] = c[3] * t;

    return tmp;
}

Vertex Vertex::operator/(float t) const {
    Vertex tmp;

    tmp[0] = c[0] / t;
    tmp[1] = c[1] / t;
    tmp[2] = c[2] / t;
    tmp[3] = c[3] / t;

    return tmp;
}

bool Vertex::operator==(const Vertex& vertex) const {
    return c[0] == vertex[0] && c[1] == vertex[1]
        && c[2] == vertex[2] && c[3] == vertex[3];
}

bool Vertex::operator!=(const Vertex& vertex) const {
    return !(c[0] == vertex[0] && c[1] == vertex[1]
        && c[2] == vertex[2] && c[3] == vertex[3]);
}

}
