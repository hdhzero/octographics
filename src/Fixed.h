#ifndef OCTOGRAPHICS_FIXED_H
#define OCTOGRAPHICS_FIXED_H

#include "OctoGraphics.h"
//#define OC_USEFLOAT 1

namespace OctoGraphics {

#define OC_IP 20
#define OC_FP 14

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
        Fixed(double n, int ip = OC_IP, int fp = OC_FP);
        Fixed(float n, int ip = OC_IP, int fp = OC_FP);
        Fixed(int num = 0, int ip = OC_IP, int fp = OC_FP);
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
