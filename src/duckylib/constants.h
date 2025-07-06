#ifndef CONSTANTS_H
#define CONSTANTS_H

float dl_square_2d[] = {
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

#endif