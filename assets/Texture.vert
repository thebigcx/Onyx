#version 460

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uTransform;

void main()
{
    texCoord = aTexCoord;
    gl_Position = uProjection * uView * uTransform * vec4(aPos, 0.0, 1.0);
}