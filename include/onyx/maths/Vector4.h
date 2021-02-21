#pragma once

#include <cassert>

namespace Onyx
{

template<typename T>
class Vector4
{
public:
    Vector4();
    Vector4(const T& x_, const T& y_, const T& z_, const T& w_);

    const T& operator[](int index) const;
    T& operator[](int index);

    T x, y, z, w;
};

template<typename T>
Vector4<T>::Vector4()
    : x(0), y(0), z(0), w(0)
{

}

template<typename T>
Vector4<T>::Vector4(const T& x_, const T& y_, const T& z_, const T& w_)
    : x(x_), y(y_), z(z_), w(w_)
{

}

template<typename T>
const T& Vector4<T>::operator[](int index) const
{
    assert(index < 4 && index >= 0);
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: return x; // Never reaches
    };
}

template<typename T>
T& Vector4<T>::operator[](int index)
{
    assert(index < 4 && index >= 0);
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: return x; // Never reaches
    };
}

typedef Vector4<float> Vector4f;

}