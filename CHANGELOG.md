# DuckyLib Changelog

## 24/9/25

- created `log.h` in utils
- added `dl_input_get_raw_mouse_position`, which returns the mouse position with the top left of the window being 0, 0.
- added `dl_input_get_mouse_position`, which returns the mouse position with the center of the viewport as 0, 0.
- added `fmath_v2_to_v3`, which converts a Vec2 to Vec3, with the z axis specified.
- added `fmath_v3_to_v2`, which converts a Vec3 to Vec2, dropping the z axis.
- broke built-in texture generating, except for the missing pink and black texture.

## 22/9/25

- renamed `cmath.h` and `cmath.c` to `fmath.h` and `fmath.c`

## 21/9/25

- created `.c` files for all headers (excluding `constants.h`)

## 8/9/25

- removed the comment from `dl_camera_destroy`

## 15/4/25

- added `viewport_x`, `viewport_x` floats to DL_Window
- added `pillarboxed`, `letterboxed` bools to DL_Window

## 14/7/25

- removed `DL_MouseBind`
- removed `DL_MouseButton`
- moved all values from `DL_MouseButton` to `DL_Keycode`, and made them negative so they don't conflict with real SDL scancodes
- `dl_input_get_key_down` now supports the new mouse codes in `DL_Keycode`
- `dl_input_get_axis` now supports the new mouse codes in `DL_Keycode`
- `dl_ui_entity_update` now prevents the ui from moving out of bounds (off the screen), which can be toggled with `DL_UIEntity::allow_out_of_bounds`

## 13/7/25

- added `sound.h`, which uses `miniaudio.h`
- added `miniaudio.h`, new dependency from [mackron/miniaudio](https://github.com/mackron/miniaudio)

## 12/7/25

- added a Windows build option to the `Makefile`
- added a Linux build option to the `Makefile`
- removed `dl_get_key_just_pressed`, moved it to be an option in `dl_get_key_pressed`
- renamed `dl_get_key_pressed` to `dl_input_get_key_down`
- renamed `dl_get_axis` to `dl_input_get_axis`
- pressing both the positive and negative axis in `dl_input_get_axis` now cancel each other out, and return 0
- removed the `DL_Window*` parameters from all input functions
- added `dl_input_get_mouse_button_down` to `input.h`
- added `vec2.h`
- added `dl_input_get_mouse_position` to `input.h`

## 11/7/25

- added `ui_entity.h` for ui objects, rendering and creation complete
- `dl_material_activate` now binds the texture
- `dl_entity_update` no longer binds texture, which is now done by `dl_material_activate`
- added an order to how `mat4_custom` multiplies position, rotation, and scale with `Mat4_MultiplicationOrder`

## 10/7/25

- changed `dl_renderer_set_background` parameter from `Vec4` to `Vec3`

## 9/7/25

- cleaned up all memory leaks
- replaced `#define float* Mat4` with `typedef float Mat4[16];`
- updated all `mat4.h` functions to match the new `Mat4`
- added `DL_Bind` to `input.h`, which holds a single `DL_Keycode` and a `bool` that tells if its pressed
- added `dl_get_key_pressed` to `input.h`, that returns `1` while a bind is pressed
- added `dl_get_key_just_pressed` to `input.h`, that only returns `1` once while a bind is pressed
- added `dl_window_set_name` to `window.h`

## 8/7/25

- added default vertex and fragment shaders to `constants.h`, if `NULL` is passed in creating a new entity it swaps it for those instead
- removed `DL_FRAG_SHADER_DEFAULT` and `DL_VERT_SHADER_DEFAULT` from `renderer.h`
- discovered shit tonne of memory leaks in `mat4.h`

## 7/7/25

- external documentation work

## 6/7/25

- fixed the dates in `CHANGELOG.md`
- renamed all structs, enums, macros, and functions to begin with `dl_` or `DL_`
- created `constants.h`
- moved the vertices for the square shape to `constants.h` (`dl_square_2d`)
- name for this project: `DuckyLib`
- created `ducky.h`
- moved all source files to into new folder `duckylib`
- moved `file.h` to `duckylib/utils`
- added a default start-up function do `ducky.h` (`dl_startup`) that optionall y creates the window, camera, and default OpenGL settings
- updated `Makefile` to correctly point to `glad.c`
- `dl_entity_new` now allows passing `NULL` for the shader directories, which will swap to the default directory macros (`DL_FRAG_SHADER_DEFAULT`, `DL_VERT_SHADER_DEFAULT`)

## 5/7/25

- added frame counting and FPS

## 4/7/25

- used keyboard state for input
- added `delta_time`

## 3/7/25

- added `glc_destroy_camera` to `camera.h`
- added inline docs to `camera.h`
- started working on frames

## 2/7/25

- added a default texture to GLT (accessible by passing `GLR_DEFAULT_TEXTURE` instead of a proper path, generates a 4x4 white and grey checker)
- added a default solid texture to GLT (accessible by passing `GLR_DEFAULT_TEXTURE_SOLID` instead of a proper path, generates a 1x1 white texture)
- renderer now supports multiple entities through multiple `glDrawArrays` calls
- fixed depth test (changed `GL_DEPTH_CLAMP` to `GL_DEPTH_TEST`)
- fixed camera bug (appeared to turn off at z -0.3, caused by broken `vec3_normalize` function)
- fixed `vec3_normalize` (related to above)
- moved all entity rendering code to `gle_update`
- created `material.h`
- removed random `printf`s
- created simple texture generator to `texture.h` (`glt_gen_texture`), allows checkered or solid color textures

## 1/7/25

- created `Vec4` (`utils/vec4.h`)
- switched `Vec3` to a `union`
- added transparent texture support
- added new `color` uniform to `fragment.glsl`
- created `CHANGELOG.md` :)
- created `entity.h`
- moved camera logic to `camera.h`
- moved a bunch of OpenGL logic into `entity.h`
- sorta borked renderering (only when trying to render more that 1 model)
