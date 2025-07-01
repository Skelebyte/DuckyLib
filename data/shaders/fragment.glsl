#version 450 core

out vec4 FragColor;

in vec2 texture_coords;
// in vec4 color;

uniform sampler2D texture_sample;

uniform vec4 color;

void main() 
{
    //FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
    FragColor = color * texture(texture_sample, texture_coords);
}