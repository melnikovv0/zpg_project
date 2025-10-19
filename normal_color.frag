#version 330 core
in vec3 fragNormal;
out vec4 fragColor;

void main()
{
    vec3 norm = normalize(fragNormal);
    vec3 color = (norm + 1.0) / 2.0;
    fragColor = vec4(color, 1.0);
}