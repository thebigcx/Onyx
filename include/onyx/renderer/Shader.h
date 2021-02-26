#pragma once

#include <onyx/maths/Matrix4.h>

#include <string>

namespace Onyx
{

class Shader
{
public:
    Shader(const std::string& vertPath, const std::string& fragPath);

    void setMatrix4f(const std::string& name, const Matrix4f& matrix);
    void setIntArray(const std::string& name, int32_t* array, uint32_t count);

    void bind() const;
    void unbind() const;

    int getUniformLocation(const std::string& name);

private:
    uint32_t m_id = 0;
};

}