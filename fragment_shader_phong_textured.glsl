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
uniform int numberOfLights; // Říká shaderu, kolik zdrojů z pole lights je třeba zpracovat.

uniform vec3 viewPos; // Poloha kamery potřebná pro výpočet odlesků.
uniform sampler2D textureUnit;

vec3 CalculateLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 finalColor = vec3(0.0); // cerny
    vec3 norm = normalize(Normal); // Normalizujeme normálu (vektor „od“ povrchu)
    vec3 viewDir = normalize(viewPos - FragPos); // // Směr od pixelu ke kameře

    for(int i = 0; i < numberOfLights; i++)
        finalColor += CalculateLight(lights[i], norm, FragPos, viewDir);
    
    FragColor = vec4(finalColor, 1.0) * texture(textureUnit, uv);
}

vec3 CalculateLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir; // Určujeme směr světla

    //Zde se provádí kontrola typu, o které jsme hovořili. Pokud je type == 0 (směrový), vezme směr. V opačném případě (bodový nebo svítilna) vypočítá vektor od pixelu ke zdroji světla.
    
    if (light.type == 0) { // Directional
        lightDir = normalize(-light.direction);
    } else { // Point or Spotlight
        lightDir = normalize(light.position - fragPos);
    }



    //diff — jas světla v závislosti na úhlu dopadu, spec — jas odlesku v závislosti na úhlu pohledu.
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm); // // Vektor odrazu
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); //  Odlesk

    //utlum Čím větší je vzdálenost, tím menší je útlum (blíže k 0).
    float attenuation = 1.0; // 1,0 = žádné útlumy
    if (light.type != 0) {  //Útlum se NEVZTAHUJE na směrové (typ 0)
        float distance = length(light.position - fragPos);
        attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    }

   // Výpočet kužele svítidla 
    float spotlightEffect = 1.0;
    if (light.type == 2) { // Spotlight - Reflektor

        float theta = dot(lightDir, normalize(-light.direction)); // Vypočítáme kosinus úhlu mezi směrem světla   a směrem k pixelu

        float epsilon = light.cutOff - light.outerCutOff; //  Vypočítáme „velikost“ měkkého okraje



        //Tato formule dává hodnotu 0,0, pokud jsme na okraji, a 1,0, pokud jsme u vnitřního kužele. clamp(...) nedovolí, aby hodnota překročila mez [0,0, 1,0].
        spotlightEffect = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    }

    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
    
    return (ambient + (diffuse + specular) * spotlightEffect) * attenuation;
}