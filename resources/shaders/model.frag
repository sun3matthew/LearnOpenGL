#version 330 core


struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float shininess;
}; 
  
struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light; 
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords));
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    diffuse *= max(dot(norm, lightDir), 0.0);

    vec3 specular = light.specular * vec3(texture(material.specular, TexCoords));
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(viewPos - FragPos);
    specular *= pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 emissive = vec3(texture(material.emissive, TexCoords));
    if(vec3(texture(material.specular, TexCoords)) != vec3(0))
        emissive = vec3(0);

    vec3 result = ambient + diffuse + specular + emissive;
    FragColor = vec4(result, 1.0);
}  