#version 330 core

#define MAX_LIGHTS 8 

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec3 viewPos;
uniform vec3 objectColor; 

vec3 CalculateLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 finalColor = vec3(0.0);
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    for(int i = 0; i < numberOfLights; i++)
        finalColor += CalculateLight(lights[i], norm, FragPos, viewDir);
    
    FragColor = vec4(finalColor * objectColor, 1.0);
}


vec3 CalculateLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
   
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
    
    return (ambient + diffuse + specular) * attenuation;
}