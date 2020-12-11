#version 330 core
in vec3 Pos;
// layout (location = 1) in vec3 aNormal;
in vec2 fTexCoords;
out vec2 TexCoords;

in vec3 fColor;
out vec3 Color;

// out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  Color = fColor;
  TexCoords = fTexCoords;
  gl_Position = projection * view * model * vec4(Pos, 1.0);
}
