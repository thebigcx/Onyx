#version 460

out vec4 color;

in vec2 texCoord;
in vec3 colorMask;

layout (binding = 0) uniform sampler2D uTexture;

void main()
{
    color = texture(uTexture, texCoord) * vec4(colorMask, 1.0);

    if (color.a < 0.1)
    {
        discard;
    }
}