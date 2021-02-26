#version 460

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;
layout (location = 3) in float aTexIndex;

out Data
{
    vec2 texCoord;
    vec3 colorMask;
    float texIndex;
} vertexOut;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uTransform;

void main()
{
    vertexOut.texCoord = aTexCoord;
    vertexOut.colorMask = aColor;
    vertexOut.texIndex = aTexIndex;

    gl_Position = uProjection * uView * uTransform * vec4(aPos, 0.0, 1.0);
}