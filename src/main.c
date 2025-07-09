#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "ducky.h"

int main(int argc, char *argv[])
{
    DL_Window window;
    dl_startup(&window, true, true);

    Entity planet = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    planet.position = vec3(0.0f, 30.0f, 0.0f);
    planet.scale = vec3(6.0f, 6.0f, 6.0f);
    dl_material_new(&planet.material, "data/textures/Circle.png", GL_LINEAR, vec4(0.2f, 0.63f, 0.25f, 1.0f));
    dl_renderer_unbind_all(&planet.renderer);

    Entity moon = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    moon.position = vec3(0.0f, 10.0f, 0.0f);
    moon.scale = vec3(1.0f, 1.0f, 1.0f);
    dl_material_new(&moon.material, "data/textures/Circle.png", GL_LINEAR, vec4(0.31f, 0.32f, 0.34f, 1.0f));
    dl_renderer_unbind_all(&moon.renderer);

    Entity sun = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    sun.position = vec3(0.0f, 0.0f, 0.0f);
    sun.scale = vec3(10.0f, 10.0f, 10.0f);
    dl_material_new(&sun.material, "data/textures/Circle.png", GL_LINEAR, vec4(1.0f, 1.0f, 0.0f, 1.0f));
    dl_renderer_unbind_all(&moon.renderer);

    Entity black_hole = dl_entity_new(dl_square_2d, sizeof(dl_square_2d), NULL, NULL);
    black_hole.scale = vec3(10.0f, 10.0f, 10.0f);
    dl_material_new(&black_hole.material, "data/textures/Circle.png", GL_LINEAR, vec4(0.0f, 0.0f, 0.0f, 1.0f));
    dl_renderer_unbind_all(&black_hole.renderer);

    float move_speed = 100.0f;

    InputAxis vertical = {
        DL_W,
        DL_S
    };
    InputAxis horizontal = {
        DL_D,
        DL_A
    };
    InputAxis zoom = {
        DL_Q,
        DL_E
    };

    const float grav_const = 0.6674f;
    const float planet_mass = 0.5972f;
    const float init_dist = moon.position.y;
    const float init_angle = 0.0f;

    float current_angle = init_angle;
    float orbital_radius = init_dist;
    float orbital_speed = sqrt((grav_const * planet_mass) / orbital_radius);
    moon.position.x = orbital_radius * sin(current_angle);
    moon.position.y = orbital_radius * cos(current_angle);

    float current_angle2 = init_angle;
    float orbital_radius2 = 30.0f;
    float orbital_speed2 = sqrt((grav_const * 1.0) / orbital_radius2);
    planet.position.x = orbital_radius2 * sin(current_angle2);
    planet.position.y = orbital_radius2 * cos(current_angle2);

    float current_angle3 = init_angle;
    float orbital_radius3 = 50.0f;
    float orbital_speed3 = sqrt((grav_const * 1.0) / orbital_radius3);
    sun.position.x = orbital_radius3 * sin(current_angle3);
    sun.position.y = orbital_radius3 * cos(current_angle3);

    float max_zoom = 200.0f;
    camera.position.z = max_zoom;

    DL_Bind bind = {DL_F11};

    bool fullscreen;

    while (window.running)
    {
        dl_frame_begin();

        current_angle = current_angle + (orbital_speed * 2 * dl_time.delta_time);
        moon.position.x = orbital_radius * sin(current_angle) + planet.position.x;
        moon.position.y = orbital_radius * cos(current_angle) + planet.position.y;

        current_angle2 = current_angle2 + (orbital_speed2 / 2 * dl_time.delta_time);
        planet.position.x = orbital_radius2 * sin(current_angle2) + sun.position.x;
        planet.position.y = orbital_radius2 * cos(current_angle2) + sun.position.y;

        current_angle3 = current_angle3 + (orbital_speed3 / 4 * dl_time.delta_time);
        sun.position.x = orbital_radius3 * sin(current_angle3) + black_hole.position.x;
        sun.position.y = orbital_radius3 * cos(current_angle3) + black_hole.position.y;

        while (SDL_PollEvent(&window.sdl_event))
        {
            dl_poll_events(&window);
        }
        camera.position.x += dl_get_axis(&window, horizontal) * move_speed * dl_time.delta_time;
        camera.position.y += dl_get_axis(&window, vertical) * move_speed * dl_time.delta_time;
        camera.position.z += dl_get_axis(&window, zoom) * move_speed * dl_time.delta_time;

        if (gl_get_key_just_pressed(&window, &bind))
        {
            fullscreen = !fullscreen;
            SDL_SetWindowFullscreen(window.sdl_window, fullscreen);
        }

        if (camera.position.z < 1.0f)
            camera.position.z = 1.0f;
        if(camera.position.z > max_zoom)
            camera.position.z = max_zoom;

        dl_window_set_viewport(&window, DL_Aspect_1920x1080);
        dl_renderer_set_background((Vec4){0.1f, 0.1f, 0.1f, 1.0f});
        dl_renderer_clear();

        dl_camera_update();
        dl_entity_update(&planet);
        dl_entity_update(&moon);
        dl_entity_update(&sun);
        dl_entity_update(&black_hole);


        dl_window_swap_buffer(&window);
        dl_frame_end();
    }

    dl_entity_destroy(&planet);
    dl_entity_destroy(&moon);
    dl_entity_destroy(&sun);
    dl_entity_destroy(&black_hole);
    dl_window_destroy(&window);
    dl_camera_destroy();
    SDL_Quit();
    return 0;
}