#version 330 core
in vec3 Pos;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexCoords;

in vec3 fColor;
out vec3 Color;

// out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  // gl_Position = view * vec4(Pos, 1.0);
  Color = fColor;
    //  gl_Position = vec4(aPos, 1.0);
  gl_Position = projection * view * model * vec4(Pos, 1.0);
}
