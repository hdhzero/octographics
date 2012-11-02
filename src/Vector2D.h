#ifndef OCTOGRAPHICS_VECTOR2D_H
#define OCTOGRAPHICS_VECTOR2D_H

namespace OctoGraphics {

class Vector2D {
    private:
        float coords[2];

    public:
        Vector2D(float x = 0.0, float y = 0.0);
        
    public:
        void set(float x, float y);
        void set_x(float x);
        void set_y(float y);

        float& operator[](int idx);
        Vector2D& operator+=(const Vector2D& vector);
        Vector2D& operator-=(const Vector2D& vector);
        Vector2D& operator*=(float t);
        Vector2D& operator/=(float t);

        Vector2D operator-() const;
        Vector2D operator+(const Vector2D& vector);
        Vector2D operator-(const Vector2D& vector);
        float operator*(const Vector2D& vector);
        
        Vector2D operator*(float t);
        Vector2D operator/(float t);
    
        bool operator==(const Vector2D& vector);
        bool operator!=(const Vector2D& vector);     
};

}

#endif
