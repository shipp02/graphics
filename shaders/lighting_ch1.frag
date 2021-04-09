#version 330 core

struct Material {
    /* vec3 ambient; */
    sampler2D diffuse;
    sampler2D specular;
    float shiny;
};

struct Light {
    float constant;
    float linear;
    float quad;
    float cutOff;
    vec3 Pos;
    vec3 Dir;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;
uniform Material material;
uniform Light light;


out vec4 FragColor;


void main() {
    
    vec3 lightDir = normalize(light.Pos - FragPos);

    float theta = dot(lightDir, normalize(-light.Dir));
    if(theta>light.cutOff) {
        vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse =  light.diffuse* (vec3(texture(material.diffuse, TexCoords))  * diff);

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiny);
        vec3 specular = light.specular* (vec3(texture(material.specular, TexCoords)) * spec);

        float dist = length(light.Pos - FragPos);
        float attenuat = 1.0 / (light.constant + light.linear * dist + light.quad * (dist * dist));

        ambient *= attenuat;
        specular *= attenuat;
        diffuse *= attenuat;


        vec3 result = (ambient+diffuse+specular);
        FragColor = vec4(result, 1.0);
    } else {
        FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
    }
}
