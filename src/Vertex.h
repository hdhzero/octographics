#ifndef OCTOGRAPHICS_VERTEX_FIXED_H
#define OCTOGRAPHICS_VERTEX_FIXED_H

namespace OctoGraphics {

class Vertex {
    private:
        Fixed c[4];

    public:
        Vertex();
        Vertex(Fixed x, Fixed y, Fixed z, Fixed w);
        Vertex(double x, double y = 0.0, double z = 0.0, double w = 0.0);

    public:
        Fixed& operator[](int idx);
        const Fixed& operator[](int idx) const;

        Vertex& operator+=(const Vertex& vertex);
        Vertex& operator-=(const Vertex& vertex);

        Vertex& operator*=(Fixed t);
        Vertex& operator/=(Fixed t);

        Vertex operator-() const;
        Vertex operator+(const Vertex& vertex) const;
        Vertex operator-(const Vertex& vertex) const;
        Fixed operator*(const Vertex& vertex) const;
        Fixed length();

        Vertex cross(const Vertex& vertex) const;

        Vertex operator*(Fixed t) const;
        Vertex operator/(Fixed t) const;

        bool operator==(const Vertex& vertex) const;
        bool operator!=(const Vertex& vertex) const;
        
};

}

#endif
