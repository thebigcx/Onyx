#pragma once

#include <onyx/maths/Vector3.h>

namespace Onyx
{

template<typename T>
class Vector2
{
public:
    Vector2();
    Vector2(const T& x_, const T& y_);
    Vector2(const Vector3<T>& vec);

    template<typename U>
    Vector2(const U& x_, const U& y_);

    template<typename U>
    Vector2(const Vector2<U>& vec);

    T x, y;

    Vector2<T> operator+(const Vector2<T>& vec) const;
    Vector2<T> operator-(const Vector2<T>& vec) const;
    Vector2<T> operator*(const Vector2<T>& vec) const;
    Vector2<T> operator/(const Vector2<T>& vec) const;

    Vector2<T> operator+=(const Vector2<T>& vec);
    Vector2<T> operator-=(const Vector2<T>& vec);
    Vector2<T> operator*=(const Vector2<T>& vec);
    Vector2<T> operator/=(const Vector2<T>& vec);
};

template<typename T>
Vector2<T>::Vector2()
    : x(0), y(0)
{

}

template<typename T>
Vector2<T>::Vector2(const T& x_, const T& y_)
    : x(x_), y(y_)
{

}

template<typename T>
Vector2<T>::Vector2(const Vector3<T>& vec)
    : x(vec.x), y(vec.y)
{

}

template<typename T>
template<typename U>
Vector2<T>::Vector2(const U& x_, const U& y_)
    : x(static_cast<T>(x_)), y(static_cast<T>(y_))
{

}

template<typename T>
template<typename U>
Vector2<T>::Vector2(const Vector2<U>& vec)
    : x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y))
{

}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec) const
{
    return Vector2<T>(x + vec.x, y + vec.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vec) const
{
    return Vector2<T>(x - vec.x, y - vec.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& vec) const
{
    return Vector2<T>(x * vec.x, y * vec.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T>& vec) const
{
    return Vector2<T>(x / vec.x, y / vec.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2<T>& vec)
{
    x += vec.x; y += vec.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2<T>& vec)
{
    x -= vec.x; y -= vec.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*=(const Vector2<T>& vec)
{
    x *= vec.x; y *= vec.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator/=(const Vector2<T>& vec)
{
    x /= vec.x; y /= vec.y;
    return *this;
}


typedef Vector2<float> Vector2f;
typedef Vector2<unsigned int> Vector2u;

}