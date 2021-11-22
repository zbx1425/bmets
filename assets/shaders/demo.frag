#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;
uniform vec4 color_diffuse;

void main() {    
    vec4 texColor = color_diffuse * texture(texture_diffuse, TexCoords);
    if(texColor.a < 0.05) discard;
    FragColor = texColor;
}