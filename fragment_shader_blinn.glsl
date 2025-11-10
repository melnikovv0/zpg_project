#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light lights[1];
uniform int numberOfLights;

uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
    vec3 result = vec3(0.0);

    if (numberOfLights > 0) {
        vec3 ambient = lights[0].ambient;

        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lights[0].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lights[0].diffuse * diff;
        
        float specularStrength = 1.0;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir); 
        float spec = pow(max(dot(norm, halfwayDir), 0.0), 32); 
        vec3 specular = lights[0].specular * spec * specularStrength;



        
        result = (ambient + diffuse + specular);
    }

    FragColor = vec4(result * objectColor, 1.0);
}