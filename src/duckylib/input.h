#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <SDL3/SDL.h>
#include "utils/vec2.h"
#include "window.h"

typedef enum DL_Keycode
{
    DL_KEY = 0,
    DL_A = 4,
    DL_B = 5,
    DL_C = 6,
    DL_D = 7,
    DL_E = 8,
    DL_F = 9,
    DL_G = 10,
    DL_H = 11,
    DL_I = 12,
    DL_J = 13,
    DL_K = 14,
    DL_L = 15,
    DL_M = 16,
    DL_N = 17,
    DL_O = 18,
    DL_P = 19,
    DL_Q = 20,
    DL_R = 21,
    DL_S = 22,
    DL_T = 23,
    DL_U = 24,
    DL_V = 25,
    DL_W = 26,
    DL_X = 27,
    DL_Y = 28,
    DL_Z = 29,
    DL_NUM_1 = 30,
    DL_NUM_2 = 31,
    DL_NUM_3 = 32,
    DL_NUM_4 = 33,
    DL_NUM_5 = 34,
    DL_NUM_6 = 35,
    DL_NUM_7 = 36,
    DL_NUM_8 = 37,
    DL_NUM_9 = 38,
    DL_NUM_0 = 39,
    DL_RETURN = 40,
    DL_ESC = 41,
    DL_BACKSPACE = 42,
    DL_TAB = 43,
    DL_SPACE = 44,
    DL_TILDE_GRAVE = 53,
    DL_F1 = 58,
    DL_F2 = 59,
    DL_F3 = 60,
    DL_F4 = 61,
    DL_F5 = 62,
    DL_F6 = 63,
    DL_F7 = 64,
    DL_F8 = 65,
    DL_F9 = 66,
    DL_F10 = 67,
    DL_F11 = 68,
    DL_F12 = 69,
    DL_R_ARROW = 79,
    DL_L_ARROW = 80,
    DL_D_ARROW = 81,
    DL_U_ARROW = 82,
    DL_L_CTRL = 224,
    DL_L_SHIFT = 225,
    DL_L_ALT = 226,
    DL_R_CTRL = 228,
    DL_R_SHIFT = 229,
    DL_R_ALT = 230

} DL_Keycode, Keycode;

typedef enum DL_MouseButton
{
    DL_LMB = 1,
    DL_MMB = 2,
    DL_RMB = 3,
    DL_XMB1 = 4,
    DL_XMB2 = 5,
} DL_MouseButton, MouseButton;

typedef struct DL_InputAxis
{
    DL_Keycode positive;
    DL_Keycode negative;
} DL_InputAxis, InputAxis;

typedef struct DL_Bind
{
    DL_Keycode keycode;
    bool pressed;
} DL_Bind, Bind;

typedef struct DL_MouseBind
{
    DL_MouseButton mouse_button;
    bool pressed;
} DL_MouseBind, MouseBind;

int dl_input_get_axis(DL_InputAxis axis)
{
    const bool *input = SDL_GetKeyboardState(NULL);

    if(input[axis.positive] == true && input[axis.negative] == true)
    {
        return 0;
    }

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

int dl_input_get_key_down(DL_Bind *bind, bool get_just_once)
{
    const bool *input = SDL_GetKeyboardState(NULL);

    if (get_just_once == true) // get key after its been pressed once
    {
        if (input[bind->keycode] == true && bind->pressed == false)
        {
            bind->pressed = true;
            return 1;
        }

        if (input[bind->keycode] == false && bind->pressed == true)
        {
            bind->pressed = false;
            return 0;
        }
    }
    else // get key while its down
    {
        if(input[bind->keycode] == true)
        {
            bind->pressed = true;
            return 1;
        } 
        else
        {
            bind->pressed = false;
            return 0;
        }
    }

    return 0;
}

int dl_input_get_mouse_button_down(DL_MouseBind *mouse_bind)
{
    SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);
    if(flags == SDL_BUTTON_MASK(mouse_bind->mouse_button))
    {
        mouse_bind->pressed = true;
        return 1;
    }
    else
    {
        mouse_bind->pressed = false;
        return 0;
    }

    

    return 0;
}

Vec2 dl_input_get_mouse_position()
{
    Vec2 pos;
    SDL_GetMouseState(&pos.x, &pos.y);

    return pos;
}

#endif