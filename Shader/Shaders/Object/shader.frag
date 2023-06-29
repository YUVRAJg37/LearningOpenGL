#version 330 core

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
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
uniform float time;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main()
{
    vec3 ambient = light.ambient*lightColor*vec3(texture(material.diffuse, TexCoord));

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir, norm), 0.0f);
    vec3 diffuse = light.diffuse*diff*texture(material.diffuse, TexCoord).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular*spec*texture(material.specular, TexCoord).rgb;
    
    vec3 emission = vec3(0.0);
    if (texture(material.specular, TexCoord).r == 0.0)   /*rough check for blackbox inside spec texture */
    {
        /*apply emission texture */
        emission = texture(material.emission, TexCoord).rgb;
        
        /*some extra fun stuff with "time uniform" */
        //emission = texture(material.emission, TexCoord + vec2(0.0,time)).rgb;   /*moving */
        //emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;                     /*fading */
    }

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
}