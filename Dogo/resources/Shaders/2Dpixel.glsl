#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) in vec4 v_Color;
layout(location = 2) in vec2 v_TexCoord;
layout(location = 3) in flat float v_TexIndex;
layout(location = 4) in flat float v_TilingFactor;

uniform sampler2D u_TextureArray[16];
void main()
{
	int index = int(v_TexIndex);
	vec4 texColor = vec4(1.0f);
	switch(index)
	{
		case  0: texColor = texture(u_TextureArray[ 0], v_TexCoord * v_TilingFactor); break;
		case  1: texColor = texture(u_TextureArray[ 1], v_TexCoord * v_TilingFactor); break;
		case  2: texColor = texture(u_TextureArray[ 2], v_TexCoord * v_TilingFactor); break;
		case  3: texColor = texture(u_TextureArray[ 3], v_TexCoord * v_TilingFactor); break;
		case  4: texColor = texture(u_TextureArray[ 4], v_TexCoord * v_TilingFactor); break;
		case  5: texColor = texture(u_TextureArray[ 5], v_TexCoord * v_TilingFactor); break;
		case  6: texColor = texture(u_TextureArray[ 6], v_TexCoord * v_TilingFactor); break;
		case  7: texColor = texture(u_TextureArray[ 7], v_TexCoord * v_TilingFactor); break;
		case  8: texColor = texture(u_TextureArray[ 8], v_TexCoord * v_TilingFactor); break;
		case  9: texColor = texture(u_TextureArray[ 9], v_TexCoord * v_TilingFactor); break;
		case 10: texColor = texture(u_TextureArray[10], v_TexCoord * v_TilingFactor); break;
		case 11: texColor = texture(u_TextureArray[11], v_TexCoord * v_TilingFactor); break;
		case 12: texColor = texture(u_TextureArray[12], v_TexCoord * v_TilingFactor); break;
		case 13: texColor = texture(u_TextureArray[13], v_TexCoord * v_TilingFactor); break;
		case 14: texColor = texture(u_TextureArray[14], v_TexCoord * v_TilingFactor); break;
		case 15: texColor = texture(u_TextureArray[15], v_TexCoord * v_TilingFactor); break;
	}
	color = texColor * v_Color;
}