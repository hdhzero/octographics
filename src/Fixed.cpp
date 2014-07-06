#include "OctoGraphics.h"

using namespace OctoGraphics;

Fixed::Fixed(double n, int ip, int fp) {
#ifndef OC_USEFLOAT
    num = (1 << fp) * n;
#else
    num = n;
#endif

    this->ip = ip;
    this->fp = fp;
}

Fixed::Fixed(float n, int ip, int fp) {
#ifndef OC_USEFLOAT
    num = (1 << fp) * n;
#else
    num = n;
#endif

    this->ip = ip;
    this->fp = fp;
}

Fixed::Fixed(int num, int ip, int fp) {
#ifndef OC_USEFLOAT
    this->num = (1 << fp) * ((float) num);
#else
    this->num = num;
#endif

    this->ip = ip;
    this->fp = fp;
}

Fixed Fixed::operator+(const Fixed& n) const {
#ifndef OC_USEFLOAT
    Fixed tmp;

    tmp.ip = ip;
    tmp.fp = fp;
    tmp.num = n.num + num;

    return tmp;
#else
    return num + n.num;
#endif
}

Fixed Fixed::operator-() const {
#ifndef OC_USEFLOAT
    Fixed tmp;

    tmp.ip = ip;
    tmp.fp = fp;
    tmp.num = -num;

    return tmp;
#else
    return -num;
#endif
}

Fixed Fixed::operator-(const Fixed& n) const {
#ifndef OC_USEFLOAT
    Fixed tmp;

    tmp.ip = ip;
    tmp.fp = fp;
    tmp.num = num - n.num;

    return tmp;
#else
    return num - n.num;
#endif
}

Fixed Fixed::operator*(const Fixed& n) const {
#ifndef OC_USEFLOAT
    Fixed tmp;
    long long int v;
    long long int r;

    tmp.ip = ip;
    tmp.fp = fp;
    v = (long long int) num * (long long int) n.num;
    r = v + ((v * 1 << (fp - 1)) << 1);
    tmp.num = v >> fp;

    return tmp;
#else
    return num * n.num;
#endif
}

Fixed Fixed::operator/(const Fixed& n) const {
#ifndef OC_USEFLOAT
    Fixed tmp;
    long long int v;
    long long int r;

    tmp.ip = ip;
    tmp.fp = fp;
    v = ((long long int) num) << fp;
    v = v / (long long int) n.num;
    r = v + ((v * 1 << (fp - 1)) << 1);
    tmp.num = v;

    return tmp;
#else
    return num / n.num;
#endif
}

float Fixed::to_float() {
#ifndef OC_USEFLOAT
    float t0 = (num >> fp);
    float t1 = 0.5;
    int i = fp - 1;

    while (i >= 0) {
        if (num & (1 << i)) {
            t0 += t1;
        }
        t1 /= 2.0;
        --i;
    }

    return t0;
#else
    return num;
#endif
}

const float Fixed::to_float() const {
#ifndef OC_USEFLOAT
    float t0 = (num >> fp);
    float t1 = 0.5;
    int i = fp - 1;

    while (i >= 0) {
        if (num & (1 << i)) {
            t0 += t1;
        }
        t1 /= 2.0;
        --i;
    }

    return t0;
#else
    return num;
#endif
}
