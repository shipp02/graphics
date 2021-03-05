#version 330 core

in vec3 Pos;
in vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 Normal;
out vec3 FragPos;

void main() {
     Normal = fNormal;
     FragPos = vec3(model * vec4(Pos, 1.0));
     gl_Position = projection * view * model * vec4(Pos, 1.0);
}