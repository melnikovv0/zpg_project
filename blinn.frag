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
    // 1. Ambient (без изменений)
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // 2. Diffuse (без изменений)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // --- ИЗМЕНЕНО: 3. Specular (по модели Блинна-Фонга) ---
    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir); // <--- Промежуточный вектор
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32); // <--- Используем halfwayDir
    vec3 specular = specularStrength * spec * lightColor;
    
    // 4. Комбинируем (без изменений)
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}