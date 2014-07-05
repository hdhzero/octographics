#ifndef OCTOGRAPHICS_FIXED_H
#define OCTOGRAPHICS_FIXED_H

#include "OctoGraphics.h"

namespace OctoGraphics {

class Fixed {
    public:
        int num;
        int ip;
        int fp;

    public:
        Fixed(double n, int ip = 16, int fp = 16);
        Fixed(float n, int ip = 16, int fp = 16);
        Fixed(int num = 0, int ip = 16, int fp = 16);
        Fixed operator-() const;
        Fixed operator+(const Fixed& n) const;
        Fixed operator-(const Fixed& n) const;
        Fixed operator*(const Fixed& n) const;
        Fixed operator/(const Fixed& n) const;
        float to_float();
        const float to_float() const;

        
};

}

#endif
