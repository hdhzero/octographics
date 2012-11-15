#include "OctoGraphics.h"

namespace OctoGraphics {

void Matrix::multiply(float a[4][4]) {
    int i;
    int j;
    int k;
    float t[4][4];

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            t[i][j] = 0.0;

            for (k = 0; k < 4; ++k) {
                t[i][j] += a[i][k] * m[k][j];
            }
        }
    }

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            m[i][j] = t[i][j];
        }
    }
}

void Matrix::set_identity(float a[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            a[i][j] = i == j ? 1 : 0;
        }
    }
}

Vertex Matrix::apply(const Vertex& vertex) const {
    Vertex tmp;

    for (int i = 0; i < 4; ++i) {
        tmp[i] = 0.0;

        for (int j = 0; j < 4; ++j) {
            tmp[i] += vertex[j] * m[i][j];
        }
    }

    return tmp;
}


void Matrix::identity() {
    set_identity(m);
}

void Matrix::print() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << m[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Matrix::translate(float x, float y, float z) {
    float tmp[4][4];

    set_identity(tmp);
    tmp[0][3] = x;
    tmp[1][3] = y;
    tmp[2][3] = z;

    multiply(tmp);
}

void Matrix::scale(float x, float y, float z) {
    float tmp[4][4];

    set_identity(tmp);
    tmp[0][0] = x;
    tmp[1][1] = y;
    tmp[2][2] = z;

    multiply(tmp);
}

void Matrix::rotate(float x, float y, float z) {
    float rz[4][4];
    float rx[4][4];
    float ry[4][4];

    set_identity(rz);
    set_identity(rx);
    set_identity(ry);

    rz[0][0] = cos(z);
    rz[0][1] = -sin(z);
    rz[1][0] = sin(z);
    rz[1][1] = cos(z);

    rx[1][1] = cos(x);
    rx[1][2] = -sin(x);
    rx[2][1] = sin(x);
    rx[2][2] = cos(x);

    ry[0][0] = cos(y);
    ry[0][2] = sin(y);
    ry[2][0] = -sin(y);
    ry[2][2] = cos(y);

    multiply(rz);
    multiply(rx);
    multiply(ry);
}

void Matrix::viewport(int width, int height) {
    float tmp[4][4];

    set_identity(tmp);
    tmp[0][0] = width / 2;
    tmp[1][1] = height / 2;
    tmp[0][3] = (width - 1) / 2;
    tmp[1][3] = (height - 1) / 2;

    multiply(tmp);
}

void Matrix::orthographic(float l, float r, float b, float t, float n, float f) {
    float tmp[4][4];

    set_identity(tmp);

    tmp[0][0] = 2.0 / (r - l);
    tmp[1][1] = 2.0 / (t - b);
    tmp[2][2] = 2.0 / (n - f);
    tmp[0][3] = -(r + l) / (r - l);
    tmp[1][3] = -(t + b) / (t - b);
    tmp[2][3] = -(n + f) / (n - f);

    multiply(tmp);
}

void Matrix::camera(Vertex& eye, Vertex& gaze, Vertex& view_up) {
    float tmp[4][4];
    float tmp2[4][4];
    Vertex w = gaze / gaze.length();
    Vertex a = view_up.cross(w);
    Vertex u = a / a.length();
    Vertex v = w.cross(u);

    set_identity(tmp);
    set_identity(tmp2);

    tmp[0][0] = u[0];
    tmp[0][1] = u[1];
    tmp[0][2] = u[2];

    tmp[1][0] = v[0];
    tmp[1][1] = v[1];
    tmp[1][2] = v[2];

    tmp[2][0] = w[0];
    tmp[2][1] = w[1];
    tmp[2][2] = w[2];

    tmp2[0][3] = -eye[0];
    tmp2[1][3] = -eye[1];
    tmp2[2][3] = -eye[2];

    multiply(tmp2);
    multiply(tmp);

}

} //End of namespace
