#version 450 core

layout (location = 0) in vec3 a_pos;

uniform mat4 model;

uniform mat4 camera_matrix;

void main() 
{
    gl_Position = camera_matrix * model * vec4(a_pos, 1.0f);
}