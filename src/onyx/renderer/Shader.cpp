#include <onyx/renderer/Shader.h>

#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace Onyx
{

std::string openFile(const std::string& path)
{
    std::ostringstream stream;

    std::ifstream file(path);
    stream << file.rdbuf();
    return stream.str();
}

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
{
    auto vShader = openFile(vertPath);
    auto fShader = openFile(fragPath);
    const char* vShaderCode = vShader.c_str();
    const char* fShaderCode = fShader.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    // Check compile errors
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "Failed to compile vertex shader: " << infoLog << "\n";
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    // Check compile errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "Failed to compile fragment shader: " << infoLog << "\n";
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    // Check link errors
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "Failed to link shader program: " << infoLog << "\n";
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

int Shader::getUniformLocation(const std::string& name)
{
    int location = glGetUniformLocation(m_id, name.c_str());

    if (location == -1)
    {
        std::cout << "Shader does not contain uniform: " << name << "\n";
    }

    return location;
}

void Shader::setMatrix4f(const std::string& name, const Matrix4f& matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0].x);
}

void Shader::bind() const
{
    glUseProgram(m_id);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

}