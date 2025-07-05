# Changelog

## 5/7/25

- added frame counting and FPS

## 4/2/25

- used keyboard state for input
- added `delta_time`

## 3/2/25

- added `glc_destroy_camera` to `camera.h`
- added inline docs to `camera.h`
- started working on frames

## 2/2/25

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

## 1/2/25

- created `Vec4` (`utils/vec4.h`)
- switched `Vec3` to a `union`
- added transparent texture support
- added new `color` uniform to `fragment.glsl`
- created `CHANGELOG.md` :)
- created `entity.h`
- moved camera logic to `camera.h`
- moved a bunch of OpenGL logic into `entity.h`
- sorta borked renderering (only when trying to render more that 1 model)