#version 450 core

layout(location = 0) out vec4 color;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
    sampler2D emission;
	float shininess;
};
struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPosition;

uniform vec3 objcolor;
uniform vec3 viewPos;

uniform Material material;

void main()
{
    //ambient light
    vec3 ambient  = light.ambient * texture(material.diffuse, v_TexCoord).rgb;

    // diffuse light
    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(light.position - v_FragPosition);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, v_TexCoord).rgb; 

    //specular
    vec3 viewDirection = normalize(viewPos - v_FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, v_TexCoord).rgb;   

    vec3 emissiveLight = texture(material.emission, v_TexCoord).rgb;

    vec3 result = (ambient + diffuse + specular + emissiveLight);

    color = vec4(result, 1.0);
}