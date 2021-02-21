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

    void bind() const;
    void unbind() const;

    int getUniformLocation(const std::string& name);

private:
    uint32_t m_id = 0;
};

}