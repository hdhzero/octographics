#ifndef OCTOGRAPHICS_MATRIX_H
#define OCTOGRAPHICS_MATRIX_H

#include "OctoGraphics.h"

namespace OctoGraphics {

class Matrix {
    private:
        float m[4][4];

    private:
        void multiply(float a[4][4]);

    public:
        Vertex apply(const Vertex& vertex) const;
        void identity();
        
};

} //End of namespace
#endif
