#ifndef OCTOGRAPHICS_MATRIX_H
#define OCTOGRAPHICS_MATRIX_H

#include "OctoGraphics.h"

namespace OctoGraphics {

class Matrix {
    private:
        float m[4][4];

    private:
        void multiply(float a[4][4]);
        void set_identity(float a[4][4]);

    public:
        Vertex apply(const Vertex& vertex) const;
        void identity();
        void print();
        void translate(float x, float y, float z);
        void scale(float x, float y, float z);
        void rotate(float x, float y, float z);

        void viewport(int width, int height);
        void orthographic(float l, float r, float b, float t, float n, float f);
        void camera(Vertex& eye, Vertex& gaze, Vertex& view_up);
        
};

} //End of namespace
#endif
