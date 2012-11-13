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
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = i == j ? 1 : 0;
        }
    }
}

} //End of namespace
