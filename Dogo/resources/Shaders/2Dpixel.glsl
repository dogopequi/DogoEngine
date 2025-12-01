#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) in vec4 v_Color;
layout(location = 2) in vec2 v_TexCoord;
layout(location = 3) in flat vec2 v_TexInfo;

uniform sampler2DArray u_TextureArrays[16];
void main()
{
	int arrayid = int(v_TexInfo.x);
	int layer = int(v_TexInfo.y);
    if(arrayid == 0) color = texture(u_TextureArrays[0], vec3(v_TexCoord, layer)) * v_Color;
    else if(arrayid == 1) color = texture(u_TextureArrays[1], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 2) color = texture(u_TextureArrays[2], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 3) color = texture(u_TextureArrays[3], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 4) color = texture(u_TextureArrays[4], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 5) color = texture(u_TextureArrays[5], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 6) color = texture(u_TextureArrays[6], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 7) color = texture(u_TextureArrays[7], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 8) color = texture(u_TextureArrays[8], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 9) color = texture(u_TextureArrays[9], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 10) color = texture(u_TextureArrays[10], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 11) color = texture(u_TextureArrays[11], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 12) color = texture(u_TextureArrays[12], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 13) color = texture(u_TextureArrays[13], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 14) color = texture(u_TextureArrays[14], vec3(v_TexCoord, layer)) * v_Color;
	else if(arrayid == 15) color = texture(u_TextureArrays[15], vec3(v_TexCoord, layer)) * v_Color;
	else
		color = texture(u_TextureArrays[0], vec3(v_TexCoord, 0)) * v_Color;
}