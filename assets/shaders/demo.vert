#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 4) in mat4 aModelMatrix;

out vec2 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main() {
    TexCoords = aTexCoords;    
    gl_Position = projection * view * aModelMatrix * vec4(aPos.xyz, 1.0);
}