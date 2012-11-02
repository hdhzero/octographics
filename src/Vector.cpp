#include "Vector.h"

OctoGraphics::Vector::Vector() {
    coords.resize(2);
    set(0.0, 0.0);
}

OctoGraphics::Vector::Vector(float x, float y) {
    coords.resize(2);
    set(x, y);
}

OctoGraphics::Vector::Vector(float x, float y, float z) {
    coords.resize(3);
    set(x, y, z);
}

OctoGraphics::Vector::Vector(int n) {
    coords.resize(n);

    for (int i = 0; i < n; ++i) {
        coords[i] = 0.0;
    }
}

OctoGraphics::Vector::Vector(std::vector<float>& c) {
    set(c);
}

void OctoGraphics::Vector::set(float x, float y) {
    coords[0] = x;
    coords[1] = y;
}

void OctoGraphics::Vector::set(float x, float y, float z) {
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
}

void OctoGraphics::Vector::set(std::vector<float>& c) {
    coords = c;
}


void OctoGraphics::Vector::set_x(float x) {
    coords[0] = x;
}

void OctoGraphics::Vector::set_y(float y) {
    coords[1] = y;
}

void OctoGraphics::Vector::set_z(float z) {
    coords[2] = z;
}

float& OctoGraphics::Vector::operator[](int idx) {
    return coords[idx];
}

OctoGraphics::Vector& 
OctoGraphics::Vector::operator+=(const OctoGraphics::Vector& vector) {
    for (int i = 0; i < coords.size(); ++i) {
        coords[i] += vector.coords[i];
    }

    return (*this);
}

OctoGraphics::Vector& 
OctoGraphics::Vector::operator-=(const OctoGraphics::Vector& vector) {
    for (int i = 0; i < coords.size(); ++i) {
        coords[i] -= vector.coords[i];
    }

    return (*this);
}

OctoGraphics::Vector& 
OctoGraphics::Vector::operator*=(float t) {
    for (int i = 0; i < coords.size(); ++i) {
        coords[i] *= t;
    }

    return (*this);
}

OctoGraphics::Vector& 
OctoGraphics::Vector::operator/=(float t) {
    for (int i = 0; i < coords.size(); ++i) {
        coords[i] /= t;
    }

    return (*this);
}

OctoGraphics::Vector
OctoGraphics::Vector::operator-() const {
    std::vector<float> tmp(coords.size());

    for (int i = 0; i < coords.size(); ++i) {
        tmp[i] = -coords[i];
    }

    return Vector(tmp);
}

OctoGraphics::Vector 
OctoGraphics::Vector::operator+(const OctoGraphics::Vector& vector) {
    std::vector<float> tmp(coords.size());

    for (int i = 0; i < coords.size(); ++i) {
        tmp[i] = coords[i] + vector.coords[i];
    }

    return Vector(tmp);
}

OctoGraphics::Vector 
OctoGraphics::Vector::operator-(const OctoGraphics::Vector& vector) {
    std::vector<float> tmp(coords.size());

    for (int i = 0; i < coords.size(); ++i) {
        tmp[i] = coords[i] - vector.coords[i];
    }

    return Vector(tmp);
}

float OctoGraphics::Vector::operator*(const OctoGraphics::Vector& vector) {
    float tmp = 0.0;

    for (int i = 0; i < coords.size(); ++i) {
        tmp += coords[i] * vector.coords[i];
    }

    return tmp;
}

OctoGraphics::Vector
OctoGraphics::Vector::operator*(float t) {
    std::vector<float> tmp(coords.size());

    for (int i = 0; i < coords.size(); ++i) {
        tmp[i] = coords[i] * t;
    }

    return Vector(tmp);
}

OctoGraphics::Vector
OctoGraphics::Vector::operator/(float t) {
    std::vector<float> tmp(coords.size());

    for (int i = 0; i < coords.size(); ++i) {
        tmp[i] = coords[i] / t;
    }

    return Vector(tmp);
}

bool OctoGraphics::Vector::operator==(const OctoGraphics::Vector& vector) {
    for (int i = 0; i < coords.size(); ++i) {
        if (coords[i] != vector.coords[i]) {
            return false;
        }
    }

    return true;
}

bool OctoGraphics::Vector::operator!=(const OctoGraphics::Vector& vector) {
    for (int i = 0; i < coords.size(); ++i) {
        if (coords[i] != vector.coords[i]) {
            return true;
        }
    }

    return false;

}

