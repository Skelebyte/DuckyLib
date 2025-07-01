#version 450 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texture_coords;

out vec3 FragPosition;
out vec2 texture_coords;

uniform mat4 model;

uniform mat4 camera_matrix;

void main() 
{
    gl_Position = camera_matrix * model * vec4(a_pos, 1.0f);
    FragPosition = vec3(model * vec4(a_pos, 1.0f));
    texture_coords = a_texture_coords;
}