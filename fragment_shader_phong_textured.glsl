#version 330 core

#define MAX_LIGHTS 8 

in vec3 FragPos;
in vec3 Normal;
in vec2 uv;

out vec4 FragColor;

struct Light {
    int type;
    
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights; 

uniform vec3 viewPos; 
uniform sampler2D textureUnit;

vec3 CalculateLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 finalColor = vec3(0.0); 
    vec3 norm = normalize(Normal); 
    vec3 viewDir = normalize(viewPos - FragPos); 

    for(int i = 0; i < numberOfLights; i++)
        finalColor += CalculateLight(lights[i], norm, FragPos, viewDir);
    
    FragColor = vec4(finalColor, 1.0) * texture(textureUnit, uv);
}

vec3 CalculateLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir; 
    
    if (light.type == 0) { 
        lightDir = normalize(-light.direction);
    } else { 
        lightDir = normalize(light.position - fragPos);
    }



    float diff = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); 

    float attenuation = 1.0; 
    if (light.type != 0) {  
        float distance = length(light.position - fragPos);
        attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    }

    float spotlightEffect = 1.0;
    if (light.type == 2) { 

        float theta = dot(lightDir, normalize(-light.direction)); 

        float epsilon = light.cutOff - light.outerCutOff; 

        spotlightEffect = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    }

    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
    
    return (ambient + (diffuse + specular) * spotlightEffect) * attenuation;
}