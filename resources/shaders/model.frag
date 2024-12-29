#version 330 core

uniform vec3 modelColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main()
{
    float distance = length(lightPos - FragPos);

    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor / (distance * distance);


    float diffuseStrength = 0.9;
    vec3 diffuse = diffuseStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    diffuse *= max(dot(norm, lightDir), 0.0) / (distance * distance);


    float specularStrength = 0.5;
    vec3 specular = specularStrength * lightColor;
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(viewPos - FragPos);
    specular *= pow(max(dot(viewDir, reflectDir), 0.0), 64);
    specular /= (distance * distance);


    vec3 result = ambient * modelColor + diffuse * modelColor + specular;
    FragColor = vec4(result, 1.0);
}  