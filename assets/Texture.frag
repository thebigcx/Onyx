#version 460

out vec4 color;

in Data
{
    vec2 texCoord;
    vec3 colorMask;
    float texIndex;
} fragmentIn;

uniform sampler2D uTextures[32];

void main()
{
    color = texture(uTextures[int(fragmentIn.texIndex)], fragmentIn.texCoord) * vec4(fragmentIn.colorMask, 1.0);

    if (color.a < 0.1)
    {
        discard;
    }
}