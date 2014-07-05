#include "OctoGraphics.h"

using namespace OctoGraphics;

Fixed::Fixed(double n, int ip, int fp) {
    num = (1 << fp) * n;
    this->ip = ip;
    this->fp = fp;
}

Fixed::Fixed(float n, int ip, int fp) {
    num = (1 << fp) * n;
    this->ip = ip;
    this->fp = fp;
}

Fixed::Fixed(int num, int ip, int fp) {
    this->num = num;
    this->ip = ip;
    this->fp = fp;
}

Fixed Fixed::operator+(const Fixed& n) const {
    Fixed tmp;

    tmp.ip = ip;
    tmp.fp = fp;
    tmp.num = n.num + num;

    return tmp;
}

Fixed Fixed::operator-() const {
    Fixed tmp;

    tmp.ip = ip;
    tmp.fp = fp;
    tmp.num = -num;

    return tmp;
}

Fixed Fixed::operator-(const Fixed& n) const {
    Fixed tmp;

    tmp.ip = ip;
    tmp.fp = fp;
    tmp.num = num - n.num;

    return tmp;
}

Fixed Fixed::operator*(const Fixed& n) const {
    Fixed tmp;
    long long int v;
    long long int r;

    tmp.ip = ip;
    tmp.fp = fp;
    v = (long long int) num * (long long int) n.num;
    r = v + ((v * 1 << (fp - 1)) << 1);
    tmp.num = v >> fp;

    return tmp;

}

Fixed Fixed::operator/(const Fixed& n) const {
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

}

float Fixed::to_float() {
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
}

const float Fixed::to_float() const {
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
}
