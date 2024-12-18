#version 450 core
layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
void main()
{
    vec4 diffuseColor = texture(texture_diffuse1, v_TexCoord);
    vec4 specularColor = texture(texture_specular1, v_TexCoord);
    vec4 normalColor = texture(texture_normal1, v_TexCoord);
    vec4 heightColor = texture(texture_height1, v_TexCoord);
    vec4 combinedColor = diffuseColor;
    FragColor = combinedColor;
}