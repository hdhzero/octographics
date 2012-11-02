#ifndef OCTOGRAPHICS_VECTOR_H
#define OCTOGRAPHICS_VECTOR_H

#include <vector>

namespace OctoGraphics {

class Vector {
    private:
        std::vector<float> coords;

    public:
        Vector();
        Vector(float x, float y);
        Vector(float x, float y, float z);
        Vector(int n);
        Vector(std::vector<float>& c);
        
    public:
        void set(float x, float y);
        void set(float x, float y, float z);
        void set(std::vector<float>& c);
        void set_x(float x);
        void set_y(float y);
        void set_z(float z);

        float& operator[](int idx);
        Vector& operator+=(const Vector& vector);
        Vector& operator-=(const Vector& vector);
        Vector& operator*=(float t);
        Vector& operator/=(float t);

        Vector operator-() const;
        Vector operator+(const Vector& vector);
        Vector operator-(const Vector& vector);
        float operator*(const Vector& vector);
        
        Vector operator*(float t);
        Vector operator/(float t);
    
        bool operator==(const Vector& vector);
        bool operator!=(const Vector& vector);     
};

}

#endif
