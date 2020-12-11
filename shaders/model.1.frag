#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Color;

uniform sampler2D _texture;

void main()
{    
    FragColor = texture(_texture, TexCoords);
}
