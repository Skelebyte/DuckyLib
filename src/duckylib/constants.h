#ifndef CONSTANTS_H
#define CONSTANTS_H

static float dl_square_2d[] = {
    // First triangle
    // positions        // texture coords
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // top left
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
    // Second triangle
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // top right
};

static const char *dl_vert_shader = 
"#version 450 core\n"
"layout(location = 0) in vec3 a_pos;\n"
"layout(location = 1) in vec2 a_texture_coords;\n"
"out vec3 FragPosition;\n"
"out vec2 texture_coords;\n"
"uniform mat4 model;\n"
"uniform mat4 camera_matrix;\n"
"void main()\n"
"{\n"
    "gl_Position = camera_matrix * model * vec4(a_pos, 1.0f);\n"
    "FragPosition = vec3(model * vec4(a_pos, 1.0f));\n"
    "texture_coords = a_texture_coords;\n"
"}\0";

static const char *dl_frag_shader = 
"#version 450 core\n"
"out vec4 FragColor;\n"
"in vec2 texture_coords;\n"
"uniform sampler2D texture_sample;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
    "FragColor = color * texture(texture_sample, texture_coords);\n"
"}\0";

static const char *dl_ui_vert_shader = 
"#version 450 core\n"
"layout(location = 0) in vec3 a_pos;\n"
"layout(location = 1) in vec2 a_texture_coords;\n"
"out vec3 FragPosition;\n"
"out vec2 texture_coords;\n"
"uniform mat4 model;\n"
"uniform mat4 camera_matrix;\n"
"void main()\n"
"{\n"
    "gl_Position = model * vec4(a_pos, 1.0f);\n"
    "FragPosition = vec3(model * vec4(a_pos, 1.0f));\n"
    "texture_coords = a_texture_coords;\n"
"}\0";

static const char *dl_ui_frag_shader = 
"#version 450 core\n"
"out vec4 FragColor;\n"
"in vec2 texture_coords;\n"
"uniform sampler2D texture_sample;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
    "FragColor = color * texture(texture_sample, texture_coords);\n"
"}\0";

#endif