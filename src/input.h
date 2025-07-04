#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <SDL3/SDL.h>
#include "window.h"

typedef enum GLR_KeyCode
{
    GLR_KEY = 0,

    GLR_A = 4,
    GLR_B = 5,
    GLR_C = 6,
    GLR_D = 7,
    GLR_E = 8,
    GLR_F = 9,
    GLR_G = 10,
    GLR_H = 11,
    GLR_I = 12,
    GLR_J = 13,
    GLR_K = 14,
    GLR_L = 15,
    GLR_M = 16,
    GLR_N = 17,
    GLR_O = 18,
    GLR_P = 19,
    GLR_Q = 20,
    GLR_R = 21,
    GLR_S = 22,
    GLR_T = 23,
    GLR_U = 24,
    GLR_V = 25,
    GLR_W = 26,
    GLR_X = 27,
    GLR_Y = 28,
    GLR_Z = 29,

    GLR_NUM_1 = 30,
    GLR_NUM_2 = 31,
    GLR_NUM_3 = 32,
    GLR_NUM_4 = 33,
    GLR_NUM_5 = 34,
    GLR_NUM_6 = 35,
    GLR_NUM_7 = 36,
    GLR_NUM_8 = 37,
    GLR_NUM_9 = 38,
    GLR_NUM_0 = 39,

    GLR_RETURN = 40,
    GLR_ESC = 41,
    GLR_BACKSPACE = 42,
    GLR_TAB = 43,
    GLR_SPACE = 44,

    GLR_TILDE_GRAVE = 53,

    GLR_F1 = 58,
    GLR_F2 = 59,
    GLR_F3 = 60,
    GLR_F4 = 61,
    GLR_F5 = 62,
    GLR_F6 = 63,
    GLR_F7 = 64,
    GLR_F8 = 65,
    GLR_F9 = 66,
    GLR_F10 = 67,
    GLR_F11 = 68,
    GLR_F12 = 69,

    GLR_R_ARROW = 79,
    GLR_L_ARROW = 80,
    GLR_D_ARROW = 81,
    GLR_U_ARROW = 82,

    GLR_L_CTRL = 224,
    GLR_L_SHIFT = 225,
    GLR_L_ALT = 226,

    GLR_R_CTRL = 228,
    GLR_R_SHIFT = 229,
    GLR_R_ALT = 230

} GLR_KeyCode, KeyCode;

typedef struct GLR_InputAxis
{
    GLR_KeyCode positive;
    GLR_KeyCode negative;
} GLR_InputAxis, InputAxis;

int gli_get_axis(GLR_Window *window, GLR_InputAxis axis) 
{

    const bool *input = SDL_GetKeyboardState(NULL);

    if(input[axis.positive] == true)
    {
        return 1;
    }

    if(input[axis.negative] == true)
    {
        return -1;
    }


    return 0;
}

#endif