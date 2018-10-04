#ifndef GL_TEXTURES_MANAGER_H
#define GL_TEXTURES_MANAGER_H

#include "gl_textures_fwd.h"

class gl_textures_manager
{
public:
  gl_textures_manager ();
  ~gl_textures_manager ();

  gl_textures_manager (const gl_textures_manager &) = delete;
  gl_textures_manager &operator= (const gl_textures_manager &) = delete;
  gl_textures_manager (gl_textures_manager &&) = delete;
  gl_textures_manager &operator= (gl_textures_manager &&) = delete;

  gl_texture_id create_texture ();

  bool set_tex_data (gl_texture_id id,
                     unsigned int gl_texture_format,
                     unsigned int gl_data_format,
                     int width, int height,
                     unsigned char *data);

  bool set_wrap_method (gl_texture_id id, gl_texture_wrap_direction direction, gl_texture_wrap_method method);
  bool set_filtering_method (gl_texture_id id, gl_texture_filter_type type, const gl_texture_filtering &filter);
  bool activate_texture (int gl_active_tex_num, gl_texture_id texture_to_bind);
  bool generate_mipmap (gl_texture_id id);

private:
  int m_gl_active_tex_num = 0;
  gl_texture_id m_binded_texture;

  std::map<gl_texture_id, unique_ptr<gl_texture>> m_textures;
private:
  bool bind (gl_texture_id id);

};

#endif // GL_TEXTURES_MANAGER_H
