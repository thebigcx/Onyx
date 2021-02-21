#pragma once

#include <onyx/maths/Vector3.h>
#include <onyx/maths/Vector4.h>

#include <cassert>
#include <cmath>

namespace Onyx
{

template<typename T>
class Matrix4
{
private:
    typedef Vector4<T> ColumnType;

public:
    Matrix4()
        : m_cells{ ColumnType(0), ColumnType(0), ColumnType(0), ColumnType(0) }
    {}

    Matrix4(const T& s)
        : m_cells{ ColumnType(s, 0, 0, 0), ColumnType(0, s, 0, 0), ColumnType(0, 0, s, 0), ColumnType(0, 0, 0, s) }
    {}

    Matrix4(const ColumnType& v0, const ColumnType& v1, const ColumnType& v2, const ColumnType& v3)
        : m_cells{ ColumnType(v0), ColumnType(v1), ColumnType(v2), ColumnType(v3) }
    {
        
    }

    Matrix4(
        const T& m00, const T& m10, const T& m20, const T& m30,
        const T& m01, const T& m11, const T& m21, const T& m31,
        const T& m02, const T& m12, const T& m22, const T& m32,
        const T& m03, const T& m13, const T& m23, const T& m33
    )
        : m_cells{ { m00, m10, m20, m30 }, 
                   { m01, m11, m12, m13 }, 
                   { m02, m12, m22, m32 }, 
                   { m30, m31, m32, m33 } } {}

    ColumnType& operator[](int i)
    {
        assert(i < 4);
        return this->m_cells[i];
    }

    const ColumnType& operator[](int i) const
    {
        assert(i < 4);
        return this->m_cells[i];
    }

    Matrix4<T>& operator=(const Matrix4<T>& matrix);

    static Matrix4<T> translate(const Matrix4<T>& matrix, const Vector3<T>& vector);
    static Matrix4<T> rotate(const Matrix4<T>& matrix, const T& angle, const Vector3<T>& axis);
    static Matrix4<T> scale(const Matrix4<T>& matrix, const Vector3<T>& scalar);
    static Matrix4<T> ortho(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far);
    static Matrix4<T> perspective(const T& fovy, const T& aspect, const T& zNear, const T& zFar);
    static Matrix4<T> lookAt(const Vector3<T>& pos, const Vector3<T>& object, const Vector3<T>& up);

private:
    ColumnType m_cells[4];
};

template<typename T>
Matrix4<T> operator*(const Matrix4<T>& matrix, const T& scalar)
{
    Matrix4<T> result = matrix;

    result[0] *= scalar;
    result[1] *= scalar;
    result[2] *= scalar;
    result[3] *= scalar;

    return result;
}

template<typename T>
Vector3<T> operator*(const Matrix4<T>& m, const Vector3<T>& v)
{
    return Vector3<T>(
        m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
        m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
        m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z
    );
}

template<typename T>
Matrix4<T> operator*(const Matrix4<T>& m1, const Matrix4<T>& m2)
{
    Matrix4<T> result;

    result[0] = m1[0] * m2[0][0] + m1[1] * m2[0][1] + m1[2] * m2[0][2] + m1[3] * m2[0][3];
    result[1] = m1[0] * m2[1][0] + m1[1] * m2[1][1] + m1[2] * m2[1][2] + m1[3] * m2[1][3];
    result[2] = m1[0] * m2[2][0] + m1[1] * m2[2][1] + m1[2] * m2[2][2] + m1[3] * m2[2][3];
    result[3] = m1[0] * m2[3][0] + m1[1] * m2[3][1] + m1[2] * m2[3][2] + m1[3] * m2[3][3];

    return result;
}

template<typename T>
Vector4<T> operator*(const Matrix4<T>& m, const Vector4<T>& v)
{
    Vector4<T> result;

    result.x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w;
    result.y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w;
    result.z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w;
    result.w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w;

    return result;
}

template<typename T>
Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& matrix)
{
    memcpy(&m_cells, &matrix.m_cells, 16 * sizeof(T));
    return *this;
}

template<typename T>
Matrix4<T> Matrix4<T>::translate(const Matrix4<T>& matrix, const Vector3<T>& vector)
{
    Matrix4<T> result = matrix;

    result[3][0] += vector.x * matrix[0][0];
    result[3][1] += vector.y * matrix[1][1];
    result[3][2] += vector.z * matrix[2][2];

    return result;
}

template<typename T>
Matrix4<T> Matrix4<T>::rotate(const Matrix4<T>& matrix, const T& angle, const Vector3<T>& axis)
{
    Matrix4<T> rotation = matrix;

    T c = std::cos(angle);
    T s = std::sin(angle);
    T omc = static_cast<T>(1) - c;

    Vector3<T> normAxis(normalize(axis));

    T x = normAxis.x;
    T y = normAxis.y;
    T z = normAxis.z;

    rotation[0][0] = x * x * omc + c;
    rotation[0][1] = y * x * omc + z * s;
    rotation[0][2] = x * z * omc - y * s;

    rotation[1][0] = x * y * omc - z * s;
    rotation[1][1] = y * y * omc + c;
    rotation[1][2] = y * z * omc + x * s;

    rotation[2][0] = x * z * omc + y * s;
    rotation[2][1] = y * z * omc - x * s;
    rotation[2][2] = z * z * omc + c;

    Matrix4<T> result;
    result[0] = matrix[0] * rotation[0][0] + matrix[1] * rotation[0][1] + matrix[2] * rotation[0][2];
    result[1] = matrix[0] * rotation[1][0] + matrix[1] * rotation[1][1] + matrix[2] * rotation[1][2];
    result[2] = matrix[0] * rotation[2][0] + matrix[1] * rotation[2][1] + matrix[2] * rotation[2][2];
    result[3] = matrix[3];

    return result;
}

template<typename T>
Matrix4<T> Matrix4<T>::scale(const Matrix4<T>& matrix, const Vector3<T>& scalar)
{
    Matrix4<T> result = matrix;

    result[0] *= Vector4<T>(scalar, static_cast<T>(1));
    result[1] *= Vector4<T>(scalar, static_cast<T>(1));
    result[2] *= Vector4<T>(scalar, static_cast<T>(1));

    return result;
}

template<typename T>
Matrix4<T> Matrix4<T>::ortho(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far)
{
    Matrix4<T> result(static_cast<T>(1));

    result[0][0] = static_cast<T>(2) / (right - left);
    result[1][1] = static_cast<T>(2) / (top - bottom);
    result[2][2] = static_cast<T>(-2) / (far - near);

    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(far + near) / (far - near);

    return result;
}

template<typename T>
Matrix4<T> Matrix4<T>::perspective(const T& fovy, const T& aspect, const T& zNear, const T& zFar)
{
    Matrix4<T> result;

    result[0][0] = static_cast<T>(1) / (aspect * std::tan(fovy / static_cast<T>(2)));
    result[1][1] = static_cast<T>(1) / std::tan(fovy / static_cast<T>(2));
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -static_cast<T>(1);
    result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);

    return result;
}

template<typename T>
Matrix4<T> Matrix4<T>::lookAt(const Vector3<T>& pos, const Vector3<T>& object, const Vector3<T>& up)
{
    Matrix4<T> result(static_cast<T>(1));

    Vector3<T> f = Vector3<T>::normalize(object - pos);
    Vector3<T> s = Vector3<T>::normalize(Vector3<T>::cross(f, up));
    Vector3<T> u = Vector3<T>::cross(s, f);

    result[0][0] = s.x;
    result[1][0] = s.y;
    result[2][0] = s.z;

    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;

    result[0][2] = -f.x;
    result[1][2] = -f.y;
    result[2][2] = -f.z;

    result[3][0] = -Vector3<T>::dot(s, pos);
    result[3][1] = -Vector3<T>::dot(u, pos);
    result[3][2] =  Vector3<T>::dot(f, pos);

    return result;
}

typedef Matrix4<float> Matrix4f;

}