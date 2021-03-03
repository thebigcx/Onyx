#pragma once

#include <onyx/maths/Vector3.h>
#include <onyx/maths/Vector4.h>

namespace Onyx
{

template<typename T>
class Vector2
{
public:
    Vector2();
    Vector2(const T& x_, const T& y_);
    Vector2(const T& s);
    Vector2(const Vector3<T>& vec);
    Vector2(const Vector4<T>& vec);

    template<typename U>
    Vector2(const U& x_, const U& y_);

    template<typename U>
    Vector2(const Vector2<U>& vec);

    template<typename U>
    Vector2(const U& s);

    T x, y;

    Vector2<T> operator+(const Vector2<T>& vec) const;
    Vector2<T> operator-(const Vector2<T>& vec) const;
    Vector2<T> operator*(const Vector2<T>& vec) const;
    Vector2<T> operator/(const Vector2<T>& vec) const;

    Vector2<T> operator+=(const Vector2<T>& vec);
    Vector2<T> operator-=(const Vector2<T>& vec);
    Vector2<T> operator*=(const Vector2<T>& vec);
    Vector2<T> operator/=(const Vector2<T>& vec);

    static float magnitude(const Vector2<T>& v);
    static Vector2<T> normalize(const Vector2<T>& v);
    static float dot(const Vector2<T>& v1, const Vector2<T>& v2);
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
Vector2<T>::Vector2(const T& s)
    : x(x), y(s)
{

}

template<typename T>
Vector2<T>::Vector2(const Vector3<T>& vec)
    : x(vec.x), y(vec.y)
{

}

template<typename T>
Vector2<T>::Vector2(const Vector4<T>& vec)
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
template<typename U>
Vector2<T>::Vector2(const U& s)
    : x(static_cast<T>(s)), y(static_cast<T>(s))
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

template<typename T>
float Vector2<T>::magnitude(const Vector2<T>& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

template<typename T>
Vector2<T> Vector2<T>::normalize(const Vector2<T>& v)
{
    float magnitude = 1.f / Vector2<T>::magnitude(v); // Divide once (save CPU cycles)
    return Vector2<T>(v.x * magnitude, v.y * magnitude);
}

template<typename T>
float Vector2<T>::dot(const Vector2<T>& v1, const Vector2<T>& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

typedef Vector2<float> Vector2f;
typedef Vector2<unsigned int> Vector2u;

}