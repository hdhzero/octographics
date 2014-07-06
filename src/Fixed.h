#ifndef OCTOGRAPHICS_FIXED_H
#define OCTOGRAPHICS_FIXED_H

#include "OctoGraphics.h"
//#define OC_USEFLOAT 1

namespace OctoGraphics {

class Fixed {
    public:
        #ifdef OC_USEFLOAT
            float num;
        #else
            int num;
        #endif
        int ip;
        int fp;

    public:
        Fixed(double n, int ip = 20, int fp = 12);
        Fixed(float n, int ip = 20, int fp = 12);
        Fixed(int num = 0, int ip = 20, int fp = 12);
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
