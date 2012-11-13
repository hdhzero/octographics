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
        void translate(float x, float y, float z);
        void scale(float x, float y, float z);
        void rotate(float x, float y, float z);
        
};

} //End of namespace
#endif
