#pragma once

namespace Onyx
{

template<typename T>
class Vector2
{
public:
    Vector2();
    Vector2(const T& x_, const T& y_);

    T x, y;
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

typedef Vector2<float> Vector2f;
typedef Vector2<unsigned int> Vector2u;

}