#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos; // Позиция камеры

void main()
{
    // 1. Ambient (фоновое освещение)
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // 2. Diffuse (диффузное освещение - как в Ламберте)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // --- НОВОЕ: 3. Specular (зеркальные блики) ---
    float specularStrength = 1.0; // Интенсивность блика
    vec3 viewDir = normalize(viewPos - FragPos); // Направление от фрагмента к камере
    vec3 reflectDir = reflect(-lightDir, norm); // Отраженный луч света
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 - это "блеск" (shininess)
    vec3 specular = specularStrength * spec * lightColor;
    
    // 4. Комбинируем все три компонента
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}