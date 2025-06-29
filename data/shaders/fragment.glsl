#version 450 core

out vec4 FragColor;

in vec2 texture_coords;

uniform sampler2D texture_sample;

void main() 
{
    //FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
    FragColor = texture(texture_sample, texture_coords);
}