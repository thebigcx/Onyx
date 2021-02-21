#version 460

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;

out vec2 texCoord;
out flat vec3 colorMask;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uTransform;

void main()
{
    texCoord = aTexCoord;
    colorMask = aColor;
    gl_Position = uProjection * uView * uTransform * vec4(aPos, 0.0, 1.0);
}