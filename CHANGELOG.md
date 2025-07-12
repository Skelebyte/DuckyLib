# DuckyLib Changelog

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
