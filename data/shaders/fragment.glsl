#version 450 core

out vec4 FragColor;

in vec2 texture_coords;

uniform sampler2D texture_sample;

uniform vec4 color;

void main() 
{
    FragColor = color * texture(texture_sample, texture_coords);
}