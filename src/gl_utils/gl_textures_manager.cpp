#include "gl_textures_manager.h"
#include "gl_headers.h"
#include "gl_texture.h"
#include "gl_texture_filtering.h"

#include "error_check.h"

gl_textures_manager::gl_textures_manager ()
{

}

gl_textures_manager::~gl_textures_manager ()
{

}

gl_texture_id gl_textures_manager::create_texture ()
{
  unsigned int gl_id;

  glGenTextures (1, &gl_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glGenTextures");
      return {};
    }

  gl_texture_id new_id = gl_texture_id::from_underlying (gl_id);

  m_textures.emplace (new_id, std::make_unique<gl_texture> (new_id));

  return new_id;
}

bool gl_textures_manager::set_tex_data (gl_texture_id id, unsigned int gl_texture_format, unsigned int gl_data_format, int width, int height, unsigned char *data)
{
  if (!bind (id))
    return false;

  glTexImage2D (GL_TEXTURE_2D, 0, gl_texture_format, width, height, 0, gl_data_format, GL_UNSIGNED_BYTE, data);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glTexImage2D");
      return false;
    }

  return true;
}

bool gl_textures_manager::set_wrap_method (gl_texture_id id, gl_texture_wrap_direction direction, gl_texture_wrap_method method)
{
  if (!bind (id))
    return false;

  glTexParameteri (GL_TEXTURE_2D, enum_to_gl_const (direction), enum_to_gl_const (method));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glTexParameteri");
      return false;
    }

  return true;
}

bool gl_textures_manager::set_filtering_method (gl_texture_id id, gl_texture_filter_type type, const gl_texture_filtering &filter)
{
  if (!bind (id))
    return false;

  glTexParameteri (GL_TEXTURE_2D, enum_to_gl_const (type), filter.to_gl_const ());

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glTexParameteri");
      return {};
    }

  return true;
}

bool gl_textures_manager::activate_texture (int gl_active_tex_num, gl_texture_id texture_to_bind)
{
  m_gl_active_tex_num = gl_active_tex_num;
  m_binded_texture.invalidate ();

  glActiveTexture (GL_TEXTURE0 + m_gl_active_tex_num);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glActiveTexture");
      return {};
    }

  return bind (texture_to_bind);
}

bool gl_textures_manager::generate_mipmap (gl_texture_id id)
{
  if (!bind (id))
    return false;

  glGenerateMipmap (GL_TEXTURE_2D);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glGenerateMipmap");
      return {};
    }

  return true;
}

bool gl_textures_manager::bind (gl_texture_id id)
{
  if (m_binded_texture == id)
    return true;

  glBindTexture (GL_TEXTURE_2D, static_cast<unsigned int> (id));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glBindTexture");
      return false;
    }

  return true;
}
