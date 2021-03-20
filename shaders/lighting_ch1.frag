#version 330 core

struct Material {
    /* vec3 ambient; */
    sampler2D diffuse;
    sampler2D specular;
    float shiny;
};

struct Light {
    vec3 Pos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

//uniform vec3 Color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {
//    float ambientStrength = 0.1;
//    float specularStrength = 0.3;
    
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
//    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  light.diffuse* (vec3(texture(material.diffuse, TexCoords))  * diff);
//    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = (specularStrength * spec) * lightColor;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiny);
    vec3 specular = light.specular* (vec3(texture(material.specular, TexCoords)) * spec);


    vec3 result = (ambient+diffuse+specular);
    FragColor = vec4(result, 1.0);
}
