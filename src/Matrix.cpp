#include "OctoGraphics.h"

namespace OctoGraphics {

void Matrix::multiply(Fixed a[4][4]) {
    int i;
    int j;
    int k;
    Fixed t[4][4];

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            t[i][j] = 0.0;

            for (k = 0; k < 4; ++k) {
                t[i][j] = t[i][j] + a[i][k] * m[k][j];
            }
        }
    }

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            m[i][j] = t[i][j];
        }
    }
}

void Matrix::set_identity(Fixed a[4][4]) {
    Fixed aa(1.0);
    Fixed bb(0.0);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            a[i][j] = i == j ? aa : bb;
        }
    }
}

Vertex Matrix::apply(const Vertex& vertex) const {
    Vertex tmp;
    Fixed bb(0.0);

    for (int i = 0; i < 4; ++i) {
        tmp[i] = bb;

        for (int j = 0; j < 4; ++j) {
            tmp[i] = tmp[i] + vertex[j] * m[i][j];
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
            std::cout << m[i][j].to_float() << ' ';
        }
        std::cout << std::endl;
    }
}

void Matrix::translate(Fixed x, Fixed y, Fixed z) {
    Fixed tmp[4][4];

    set_identity(tmp);
    tmp[0][3] = x;
    tmp[1][3] = y;
    tmp[2][3] = z;

    multiply(tmp);
}

void Matrix::scale(Fixed x, Fixed y, Fixed z) {
    Fixed tmp[4][4];

    set_identity(tmp);
    tmp[0][0] = x;
    tmp[1][1] = y;
    tmp[2][2] = z;

    multiply(tmp);
}

void Matrix::rotate(Fixed x, Fixed y, Fixed z) {
    Fixed rz[4][4];
    Fixed rx[4][4];
    Fixed ry[4][4];

    set_identity(rz);
    set_identity(rx);
    set_identity(ry);

    rz[0][0] = Fixed(cos(z.to_float()));
    rz[0][1] = Fixed(-sin(z.to_float()));
    rz[1][0] = Fixed(sin(z.to_float()));
    rz[1][1] = Fixed(cos(z.to_float()));

    rx[1][1] = Fixed(cos(x.to_float()));
    rx[1][2] = Fixed(-sin(x.to_float()));
    rx[2][1] = Fixed(sin(x.to_float()));
    rx[2][2] = Fixed(cos(x.to_float()));

    ry[0][0] = Fixed(cos(y.to_float()));
    ry[0][2] = Fixed(sin(y.to_float()));
    ry[2][0] = Fixed(-sin(y.to_float()));
    ry[2][2] = Fixed(cos(y.to_float()));

    multiply(rz);
    multiply(rx);
    multiply(ry);
}

void Matrix::viewport(int width, int height) {
    Fixed tmp[4][4];

    set_identity(tmp);
    tmp[0][0] = Fixed((float) width) / Fixed(2.0);
    tmp[1][1] = Fixed((float) height) / Fixed(2.0);
    tmp[0][3] = Fixed(width - 1.0) / Fixed(2.0);
    tmp[1][3] = Fixed((height - 1.0)) / Fixed(2.0);

    multiply(tmp);
}

void Matrix::orthographic(Fixed l, Fixed r, Fixed b, Fixed t, Fixed n, Fixed f) {
    Fixed tmp[4][4];

    set_identity(tmp);

    tmp[0][0] = Fixed(2.0) / (r - l);
    tmp[1][1] = Fixed(2.0) / (t - b);
    tmp[2][2] = Fixed(2.0) / (n - f);
    tmp[0][3] = -(r + l) / (r - l);
    tmp[1][3] = -(t + b) / (t - b);
    tmp[2][3] = -(n + f) / (n - f);

    multiply(tmp);
}

void Matrix::frustum(Fixed l, Fixed r, Fixed b, Fixed t, Fixed n, Fixed f) {
	Fixed tmp[4][4];

	set_identity(tmp);

	tmp[0][0] = (Fixed(2.0) * n) / (r - l);
	tmp[0][2] = (l + r) / (l - r);
	tmp[1][1] = (Fixed(2.0) * n) / (t - b);
	tmp[1][2] = (b + t) / (b - t);
	tmp[2][2] = (f + n) / (n - f);
	tmp[2][3] = (Fixed(2.0) * f * n) / (f - n);
	tmp[3][2] = 1;
	tmp[3][3] = 0;

	multiply(tmp);
}

void Matrix::perspective(Fixed fov, Fixed aspect, Fixed n, Fixed f) {
    Fixed l;
    Fixed r;
    Fixed b;
    Fixed t;
    Fixed nn = n.to_float() < 0.0 ? -n : n;

    t = Fixed(tan(fov.to_float() / 2.0)) * nn;
    r = t * aspect;
    l = -r;
    b = -t;

    frustum(l, r, b, t, n, f);
}


void Matrix::camera(Vertex& eye, Vertex& gaze, Vertex& view_up) {
    Fixed tmp[4][4];
    Fixed tmp2[4][4];

    Vertex g = eye - gaze;
    Vertex w = g / g.length();
    w = -w;

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

void Matrix::camera2(Vertex& eye, Vertex& gaze, Vertex& view_up) {
    Fixed tmp[4][4];
    Fixed tmp2[4][4];

    Vertex f = eye - gaze;
    Vertex fn = f / f.length();
    Vertex un = view_up / view_up.length();
    Vertex s = fn.cross(un);
    Vertex sn = s / s.length();
    Vertex u = sn.cross(fn);

    set_identity(tmp);
    set_identity(tmp2);

    tmp[0][0] = s[0];
    tmp[0][1] = s[1];
    tmp[0][2] = s[2];

    tmp[1][0] = u[0];
    tmp[1][1] = u[1];
    tmp[1][2] = u[2];

    tmp[2][0] = -f[0];
    tmp[2][1] = -f[1];
    tmp[2][2] = -f[2];

    tmp2[0][3] = -eye[0];
    tmp2[1][3] = -eye[1];
    tmp2[2][3] = -eye[2];

    multiply(tmp2);
    multiply(tmp);
}


} //End of namespace
