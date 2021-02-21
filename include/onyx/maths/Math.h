#pragma once

namespace Onyx
{

template<typename T>
static T toRadians(const T& degrees)
{
    return degrees * static_cast<T>(0.01745329251994329576923690768489);
}

template<typename T>
static T toDegrees(const T& radians)
{
    return radians * static_cast<T>(57.295779513082320876798154814105);
}

}