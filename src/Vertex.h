#ifndef OCTOGRAPHICS_VERTEX_H
#define OCTOGRAPHICS_VERTEX_H

namespace OctoGraphics {

class Vertex {
    private:
        float c[4];

    public:
        Vertex(float x=0.0, float y=0.0, float z=0.0, float w=0.0);

    public:
        float& operator[](int idx);
        const float& operator[](int idx) const;

        Vertex& operator+=(const Vertex& vertex);
        Vertex& operator-=(const Vertex& vertex);

        Vertex& operator*=(float t);
        Vertex& operator/=(float t);

        Vertex operator-() const;
        Vertex operator+(const Vertex& vertex) const;
        Vertex operator-(const Vertex& vertex) const;
        float operator*(const Vertex& vertex) const;

        Vertex operator*(float t) const;
        Vertex operator/(float t) const;

        bool operator==(const Vertex& vertex) const;
        bool operator!=(const Vertex& vertex) const;
        
};

}

#endif
