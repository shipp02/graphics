#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//uniform vec3 Color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;

void main() {
//    float ambientStrength = 0.1;
//    float specularStrength = 0.3;
    
    vec3 ambient = material.ambient * lightColor;
//    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  lightColor * (material.diffuse * diff);
//    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = (specularStrength * spec) * lightColor;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (material.specular * spec);


    vec3 result = (ambient+diffuse+specular);
    FragColor = vec4(result, 1.0);
}
