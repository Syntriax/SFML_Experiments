#include "SynGame.hpp"

#pragma region Vector1
    class Vector1
    {
        public:
            float x;
            Vector1(float = 0);
            Vector1 operator+(Vector1);
            Vector1 operator-(Vector1);
            Vector1 operator/(Vector1);
            Vector1 operator*(Vector1);
            Vector1 operator+=(Vector1);
            Vector1 operator-=(Vector1);
            Vector1 operator/=(Vector1);
            Vector1 operator*=(Vector1);
            Vector1 operator/(float);
            Vector1 operator*(float);
            Vector1 operator/=(float);
            Vector1 operator*=(float);
            float Magnitude();
            float Distance(Vector1);
            Vector1 Normalized();
    };

    Vector1::Vector1(float x) { this -> x = x; }

    Vector1 Vector1::operator+ (Vector1 parameter) { Vector1 vector = Vector1(x); vector.x += parameter.x; return vector; }
    Vector1 Vector1::operator- (Vector1 parameter) { Vector1 vector = Vector1(x); vector.x -= parameter.x; return vector; }
    Vector1 Vector1::operator/ (Vector1 parameter) { Vector1 vector = Vector1(x); vector.x /= parameter.x; return vector; }
    Vector1 Vector1::operator* (Vector1 parameter) { Vector1 vector = Vector1(x); vector.x *= parameter.x; return vector; }
    Vector1 Vector1::operator+=(Vector1 parameter) { x += parameter.x; return *this; }
    Vector1 Vector1::operator-=(Vector1 parameter) { x -= parameter.x; return *this; }
    Vector1 Vector1::operator/=(Vector1 parameter) { x /= parameter.x; return *this; }
    Vector1 Vector1::operator*=(Vector1 parameter) { x *= parameter.x; return *this; }
    
    Vector1 Vector1::operator/ (float parameter) { Vector1 vector = Vector1(x); vector.x /= parameter; return vector; }
    Vector1 Vector1::operator* (float parameter) { Vector1 vector = Vector1(x); vector.x *= parameter; return vector; }
    Vector1 Vector1::operator/=(float parameter) { x /= parameter; return *this; }
    Vector1 Vector1::operator*=(float parameter) { x *= parameter; return *this; }

    float Vector1::Magnitude() { return x; }
    float Vector1::Distance(Vector1 parameter) 
    { 
        Vector1 distanceVector = (*this) - parameter;
        return distanceVector.Magnitude(); 
    }
    Vector1 Vector1::Normalized() { return Vector1(x < 0.0 ? -1.0 : 1.0); }
#pragma endregion
#pragma region Vector2
    class Vector2
    {
        public:
            float x;
            float y;
            Vector2(float = 0, float = 0);
            Vector2 operator+(Vector2);
            Vector2 operator-(Vector2);
            Vector2 operator/(Vector2);
            Vector2 operator*(Vector2);
            Vector2 operator+=(Vector2);
            Vector2 operator-=(Vector2);
            Vector2 operator/=(Vector2);
            Vector2 operator*=(Vector2);
            Vector2 operator/(float);
            Vector2 operator*(float);
            Vector2 operator/=(float);
            Vector2 operator*=(float);
            float Magnitude();
            float Distance(Vector2);
            Vector2 Normalized();
    };

    Vector2::Vector2(float x, float y) { this -> x = x; this -> y = y; }

    Vector2 Vector2::operator+ (Vector2 parameter) { Vector2 vector = Vector2(x, y); vector.x += parameter.x; vector.y += parameter.y; return vector; }
    Vector2 Vector2::operator- (Vector2 parameter) { Vector2 vector = Vector2(x, y); vector.x -= parameter.x; vector.y -= parameter.y; return vector; }
    Vector2 Vector2::operator/ (Vector2 parameter) { Vector2 vector = Vector2(x, y); vector.x /= parameter.x; vector.y /= parameter.y; return vector; }
    Vector2 Vector2::operator* (Vector2 parameter) { Vector2 vector = Vector2(x, y); vector.x *= parameter.x; vector.y *= parameter.y; return vector; }
    Vector2 Vector2::operator+=(Vector2 parameter) { x += parameter.x; y += parameter.y; return *this; }
    Vector2 Vector2::operator-=(Vector2 parameter) { x -= parameter.x; y -= parameter.y; return *this; }
    Vector2 Vector2::operator/=(Vector2 parameter) { x /= parameter.x; y /= parameter.y; return *this; }
    Vector2 Vector2::operator*=(Vector2 parameter) { x *= parameter.x; y *= parameter.y; return *this; }

    Vector2 Vector2::operator/ (float parameter) { Vector2 vector = Vector2(x, y); vector.x /= parameter; vector.y /= parameter; return vector; }
    Vector2 Vector2::operator* (float parameter) { Vector2 vector = Vector2(x, y); vector.x *= parameter; vector.y *= parameter; return vector; }
    Vector2 Vector2::operator/=(float parameter) { x *= parameter; y *= parameter; return *this; }
    Vector2 Vector2::operator*=(float parameter) { x /= parameter; y /= parameter; return *this; }

    float Vector2::Magnitude() { return sqrt(x*x+y*y); }
    float Vector2::Distance(Vector2 parameter) 
    { 
        Vector2 distanceVector = (*this) - parameter;
        return distanceVector.Magnitude(); 
    }
    Vector2 Vector2::Normalized() 
    { 
        Vector2 vector = Vector2(x, y);
        return vector / Magnitude();
    }
#pragma endregion
#pragma region Vector3
    class Vector3
    {
        public:
            float x;
            float y;
            float z;
            Vector3(float = 0, float = 0, float = 0);
            Vector3 operator+(Vector3);
            Vector3 operator-(Vector3);
            Vector3 operator/(Vector3);
            Vector3 operator*(Vector3);
            Vector3 operator+=(Vector3);
            Vector3 operator-=(Vector3);
            Vector3 operator/=(Vector3);
            Vector3 operator*=(Vector3);
            Vector3 operator/(float);
            Vector3 operator*(float);
            Vector3 operator/=(float);
            Vector3 operator*=(float);
            float Magnitude();
            float Distance(Vector3);
            Vector3 Normalized();
    };

    Vector3::Vector3(float x, float y, float z) { this -> x = x; this -> y = y; this -> z = z; }

    Vector3 Vector3::operator+ (Vector3 parameter) { Vector3 vector = Vector3(x, y, z); vector.x += parameter.x; vector.y += parameter.y; vector.z += parameter.z; return vector; }
    Vector3 Vector3::operator- (Vector3 parameter) { Vector3 vector = Vector3(x, y, z); vector.x -= parameter.x; vector.y -= parameter.y; vector.z -= parameter.z; return vector; }
    Vector3 Vector3::operator/ (Vector3 parameter) { Vector3 vector = Vector3(x, y, z); vector.x /= parameter.x; vector.y /= parameter.y; vector.z /= parameter.z; return vector; }
    Vector3 Vector3::operator* (Vector3 parameter) { Vector3 vector = Vector3(x, y, z); vector.x *= parameter.x; vector.y *= parameter.y; vector.z *= parameter.z; return vector; }
    Vector3 Vector3::operator+=(Vector3 parameter) { x += parameter.x; y += parameter.y; z += parameter.z; return *this; }
    Vector3 Vector3::operator-=(Vector3 parameter) { x -= parameter.x; y -= parameter.y; z -= parameter.z; return *this; }
    Vector3 Vector3::operator/=(Vector3 parameter) { x /= parameter.x; y /= parameter.y; z /= parameter.z; return *this; }
    Vector3 Vector3::operator*=(Vector3 parameter) { x *= parameter.x; y *= parameter.y; z *= parameter.z; return *this; }

    Vector3 Vector3::operator/=(float parameter) { x *= parameter; y *= parameter; z *= parameter; return *this; }
    Vector3 Vector3::operator*=(float parameter) { x /= parameter; y /= parameter; z /= parameter; return *this; }
    Vector3 Vector3::operator/ (float parameter) { Vector3 vector = Vector3(x, y, z); vector.x /= parameter; vector.y /= parameter; vector.z /= parameter; return vector; }
    Vector3 Vector3::operator* (float parameter) { Vector3 vector = Vector3(x, y, z); vector.x *= parameter; vector.y *= parameter; vector.z *= parameter; return vector; }

    float Vector3::Magnitude() { return sqrt(x*x+y*y+z*z); }
    float Vector3::Distance(Vector3 parameter) 
    { 
        Vector3 distanceVector;
        distanceVector.x = x - parameter.x;
        distanceVector.y = y - parameter.y;
        distanceVector.z = z - parameter.z;
        return distanceVector.Magnitude(); 
    }
    Vector3 Vector3::Normalized() 
    { 
        Vector3 vector = Vector3(x, y, z);
        return vector / Magnitude();
    }
#pragma endregion