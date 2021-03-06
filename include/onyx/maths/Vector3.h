#pragma once


#include <cmath>
#include <cassert>

namespace Onyx
{

template<typename T>
class Vector3
{
public:
    Vector3();
    Vector3(const T& x_, const T& y_, const T& z_);

    static Vector3<T> normalize(const Vector3<T>& vector);
    static Vector3<T> cross(const Vector3<T>& a, const Vector3<T>& b);
    static float dot(const Vector3<T>& a, const Vector3<T>& b);
    static float mag(const Vector3<T>& vector);

    Vector3<T> operator+(const Vector3<T>& val) const;
    Vector3<T> operator+(const T& num) const;

    Vector3<T> operator-(const Vector3<T>& val) const;
    Vector3<T> operator-(const T& num) const;
    Vector3<T> operator-();

    Vector3<T> operator*(const Vector3<T>& val) const;
    Vector3<T> operator*(const T& scl) const;

    Vector3<T> operator/(const Vector3<T>& val) const;
    Vector3<T> operator/(const T& scl) const;

    const T& operator[](int index) const;
    T& operator[](int index);

    T x, y, z;
};

template<typename T>
Vector3<T>::Vector3()
    : x(0), y(0), z(0)
{

}

template<typename T>
Vector3<T>::Vector3(const T& x_, const T& y_, const T& z_)
    : x(x_), y(y_), z(z_)
{

}

template<typename T>
Vector3<T> Vector3<T>::normalize(const Vector3<T>& vector)
{
    float magnitude = 1.f / Vector3<T>::mag(vector);
    return Vector3<T>(vector.x * magnitude, vector.y * magnitude, vector.z * magnitude);
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& a, const Vector3<T>& b)
{
    return Vector3<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template<typename T>
float Vector3<T>::dot(const Vector3<T>& a, const Vector3<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
float Vector3<T>::mag(const Vector3<T>& vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const
{
    return Vector3<T>(x + vector.x, y + vector.y, z + vector.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const T& num) const
{
    return Vector3<T>(x + num, y + num, z + num);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector) const
{
    return Vector3<T>(x - vector.x, y - vector.y, z - vector.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const T& num) const
{
    return Vector3<T>(x - num, y - num, z - num);
}

template<typename T>
Vector3<T> Vector3<T>::operator-()
{
    return Vector3<T>(-x, -y, -z);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& vector) const
{
    return Vector3<T>(x * vector.x, y * vector.y, z * vector.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const T& scl) const
{
    return Vector3<T>(x * scl, y * scl, z * scl);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(const Vector3<T>& vector) const
{
    return Vector3<T>(x / vector.x, y / vector.y, z / vector.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(const T& scl) const
{
    return Vector3<T>(x / scl, y / scl, z / scl);
}

template<typename T>
const T& Vector3<T>::operator[](int index) const
{
    assert(index < 3 && index >= 0);
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    };
}

template<typename T>
T& Vector3<T>::operator[](int index)
{
    assert(index < 3 && index >= 0);
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    };
}

typedef Vector3<float> Vector3f;

}