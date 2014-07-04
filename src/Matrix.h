#ifndef OCTOGRAPHICS_MATRIXFIXED_H
#define OCTOGRAPHICS_MATRIXFIXED_H

#include "OctoGraphics.h"

namespace OctoGraphics {

class Matrix {
    private:
        Fixed m[4][4];

    private:
        void multiply(Fixed a[4][4]);
        void set_identity(Fixed a[4][4]);

    public:
        Vertex apply(const Vertex& vertex) const;
        void identity();
        void print();
        void translate(Fixed x, Fixed y, Fixed z);
        void scale(Fixed x, Fixed y, Fixed z);
        void rotate(Fixed x, Fixed y, Fixed z);

        void viewport(int width, int height);
        void orthographic(Fixed l, Fixed r, Fixed b, Fixed t, Fixed n, Fixed f);
        void frustum(Fixed l, Fixed r, Fixed b, Fixed t, Fixed n, Fixed f);
        void camera(Vertex& eye, Vertex& gaze, Vertex& view_up);
        void camera2(Vertex& eye, Vertex& gaze, Vertex& view_up);
        
};

} // End of namespace
#endif
