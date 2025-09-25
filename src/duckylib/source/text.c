// #include "../text.h"

// DL_Text dl_text_new(const char *text, const char *font_path, int size, DL_Blendmode blendmode, DL_AspectRatios ratio, const char *vert_src_dir, const char *frag_src_dir)
// {
//     DL_Text t =
//     {
//         vec2(0.0f, 0.0f),
//         vec3(0.0f, 0.0f, 0.0f),
//         vec2(1.0f, 1.0f)
//     };

//     t.aspect_ratio = dl_get_virtual_aspect(ratio);

//     mat4_custom(t.model, fmath_v2_to_v3(t.position, 0.0f), t.rotation, fmath_v2_to_v3(t.scale, 1.0f), Mat4_TSR);

//     if (vert_src_dir == NULL)
//     {
//         vert_src_dir = dl_ui_vert_shader;
//     }
//     else
//     {
//         vert_src_dir = file_read(vert_src_dir);
//     }

//     if (frag_src_dir == NULL)
//     {
//         frag_src_dir = dl_ui_frag_shader;
//     }
//     else
//     {
//         frag_src_dir = file_read(frag_src_dir);
//     }

//     dl_renderer_compile_shaders(&t.renderer, vert_src_dir, frag_src_dir);
//     dl_renderer_opengl_error("DL_Text shader compilation failed!", __LINE__);

//     dl_renderer_gen_vao(&t.renderer);
//     dl_renderer_opengl_error("DL_Text VAO generation failed!", __LINE__);
//     dl_renderer_gen_vbo(&t.renderer, dl_square_2d, sizeof(dl_square_2d));
//     dl_renderer_opengl_error("DL_Text VBO generation failed!", __LINE__);

//     dl_renderer_link_attrib(&t.renderer, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0); // vertex position
//     dl_renderer_opengl_error("DL_Text vertex position link failed!", __LINE__);
//     dl_renderer_link_attrib(&t.renderer, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float))); // texture coordinate
//     dl_renderer_opengl_error("DL_Text texture coord link failed!", __LINE__);

//     SDL_Color color = {255, 255, 255, 255};
//     SDL_Surface *surface = TTF_RenderText_Blended(font_path, text, size, color);

//     unsigned char *data;
// }