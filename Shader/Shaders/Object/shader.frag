#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

uniform Material material;  
uniform Light light;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    vec3 ambient = light.ambient*material.ambient*lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir, norm), 0.0f);

    vec3 diffuse = light.diffuse*diff*material.diffuse*lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular*spec*material.specular*lightColor;
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result * objectColor, 1.0);
}