#include "Vector2D.h"

OctoGraphics::Vector2D::Vector2D(float x, float y) {
    set(x, y);
}

void OctoGraphics::Vector2D::set(float x, float y) {
    coords[0] = x;
    coords[1] = y;
}

void OctoGraphics::Vector2D::set_x(float x) {
    coords[0] = x;
}

void OctoGraphics::Vector2D::set_y(float y) {
    coords[1] = y;
}

float& OctoGraphics::Vector2D::operator[](int idx) {
    return coords[idx];
}

OctoGraphics::Vector2D& 
OctoGraphics::Vector2D::operator+=(const OctoGraphics::Vector2D& vector) {
    coords[0] += vector.coords[0];
    coords[1] += vector.coords[1];

    return (*this);
}

OctoGraphics::Vector2D& 
OctoGraphics::Vector2D::operator-=(const OctoGraphics::Vector2D& vector) {
    coords[0] -= vector.coords[0];
    coords[1] -= vector.coords[1];

    return (*this);
}

OctoGraphics::Vector2D& 
OctoGraphics::Vector2D::operator*=(float t) {
    coords[0] *= t;
    coords[1] *= t;

    return (*this);
}

OctoGraphics::Vector2D& 
OctoGraphics::Vector2D::operator/=(float t) {
    coords[0] /= t;
    coords[1] /= t;

    return (*this);
}

OctoGraphics::Vector2D
OctoGraphics::Vector2D::operator-() const {
    return Vector2D(-coords[0], -coords[1]);
}

OctoGraphics::Vector2D 
OctoGraphics::Vector2D::operator+(const OctoGraphics::Vector2D& vector) {
    return Vector2D(coords[0] + vector.coords[0],
        coords[1] + vector.coords[1]);
}

OctoGraphics::Vector2D 
OctoGraphics::Vector2D::operator-(const OctoGraphics::Vector2D& vector) {
    return Vector2D(coords[0] - vector.coords[0],
        coords[1] - vector.coords[1]);
}

float OctoGraphics::Vector2D::operator*(const OctoGraphics::Vector2D& vector) {
    return coords[0] * vector.coords[0] + coords[1] * vector.coords[1];
}

OctoGraphics::Vector2D
OctoGraphics::Vector2D::operator*(float t) {
    return Vector2D(coords[0] * t, coords[1] * t);
}

OctoGraphics::Vector2D
OctoGraphics::Vector2D::operator/(float t) {
    return Vector2D(coords[0] / t, coords[1] / t);
}

bool OctoGraphics::Vector2D::operator==(const OctoGraphics::Vector2D& vector) {
    return coords[0] == vector.coords[0] && coords[1] == vector.coords[1];
}

bool OctoGraphics::Vector2D::operator!=(const OctoGraphics::Vector2D& vector) {
    return !(coords[0] == vector.coords[0] && coords[1] == vector.coords[1]);
}

