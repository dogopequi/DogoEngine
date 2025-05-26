#version 450 core

layout(location = 0) out vec4 color;
in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in float v_TexIndex;

uniform sampler2D textures[16];
uniform int mode;
void main()
{
    if(mode == 0)
    {
        int index = int(v_TexIndex);
        if (index != 0)
            color = texture(textures[index], v_TexCoord);
        else
            color = v_Color;
    }
    else
    {
        vec2 flippedTexCoord = vec2(v_TexCoord.x, 1.0 - v_TexCoord.y);
        color = texture(textures[0], flippedTexCoord);
    }

}