#version 460

out vec4 color;

in vec2 texCoord;

layout (binding = 0) uniform sampler2D uTexture;

void main()
{
    color = texture(uTexture, texCoord);

    if (color.a < 0.1)
    {
        discard;
    }
}