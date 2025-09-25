#include "../input.h"

int dl_input_get_axis(DL_InputAxis axis)
{

    SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

    if (axis.positive < 0 && axis.negative < 0)
    {
        if (flags & SDL_BUTTON_MASK(-axis.positive) && flags & SDL_BUTTON_MASK(-axis.negative))
        {
            return 0;
        }
    }

    if (axis.positive < 0)
    {
        if (flags == SDL_BUTTON_MASK(-axis.positive))
        {
            return 1;
        }
    }

    if (axis.negative < 0)
    {
        if (flags == SDL_BUTTON_MASK(-axis.negative))
        {
            return -1;
        }
    }

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
    SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

    if(bind->keycode < 0)
    {
        if(get_just_once == true)
        {
            if (flags & SDL_BUTTON_MASK(-bind->keycode) && bind->pressed == false)
            {
                bind->pressed = true;
                return 1;
            }

            if((flags & SDL_BUTTON_MASK(-bind->keycode)) == 0 && bind->pressed == true)
            {
                bind->pressed = false;
                return 0;
            }
        }
        else
        {
            if (flags == SDL_BUTTON_MASK(-bind->keycode))
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

Vec2 dl_input_get_raw_mouse_position()
{
    Vec2 pos = {0};
    SDL_GetMouseState(&pos.x, &pos.y);

    return pos;
}

Vec2 dl_input_get_mouse_position(DL_Window *window)
{
    Vec2 pos = {0};
    SDL_GetMouseState(&pos.x, &pos.y);

    pos.x -= window->viewport_x;
    pos.x -= window->viewport_w / 2;
    pos.x /= window->viewport_w / 2;
    pos.y -= window->viewport_y;
    pos.y -= window->viewport_h / 2;
    pos.y /= window->viewport_h / 2;

    pos.y = -pos.y;

    if (pos.x > 1.0f)
        pos.x = 1.0f;
    if (pos.x < -1.0f)
        pos.x = -1.0f;
    if (pos.y > 1.0f)
        pos.y = 1.0f;
    if (pos.y < -1.0f)
        pos.y = -1.0f;

    return pos;
}