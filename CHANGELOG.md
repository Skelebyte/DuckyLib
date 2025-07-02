### 2/2/25
- added a default texture to GLT
- fixed renderer to support more than 1 entity at a time

### 1/2/25
- created `Vec4` (`utils/vec4.h`)
- switched `Vec3` to a `union`
- added transparent texture support
- added new `color` uniform to `fragment.glsl`
- created `CHANGELOG.md` :)
- created `entity.h`
- moved camera logic to `camera.h`
- moved a bunch of OpenGL logic into `entity.h`
- sorta borked renderering (only when trying to render more that 1 model)