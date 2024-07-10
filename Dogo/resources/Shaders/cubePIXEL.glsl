#version 450 core

layout(location = 0) out vec4 color;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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
in vec3 v_FragPosition;

uniform vec3 objcolor;
uniform vec3 viewPos;

uniform Material material;

void main()
{
    //ambient light
    vec3 ambient  = light.ambient * material.ambient;

    // diffuse light
    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(light.position - v_FragPosition);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse); 

    //specular
    vec3 viewDirection = normalize(viewPos - v_FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);   

    vec3 result = (ambient + diffuse + specular);

    color = vec4(result, 1.0);
}