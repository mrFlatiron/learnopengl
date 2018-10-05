#include "gl_texture.h"
#include "gl_headers.h"

gl_texture::gl_texture ()
{

}

gl_texture::~gl_texture ()
{
  auto gl_id = static_cast<unsigned int> (m_id);

  if (m_id.is_valid ())
    glDeleteTextures (1, &gl_id);
}

gl_texture::gl_texture (gl_texture_id id)
{
  m_id = id;
}

unsigned int enum_to_gl_const (gl_texture_wrap_direction dir)
{
  switch (dir)
    {
    case gl_texture_wrap_direction::left_right:
      return GL_TEXTURE_WRAP_S;
    case gl_texture_wrap_direction::top_bottom:
      return GL_TEXTURE_WRAP_T;
    }

  ASSERT_RETURN (false, 0);
}

unsigned int enum_to_gl_const (gl_texture_wrap_method method)
{
  switch (method)
    {
    case gl_texture_wrap_method::repeat:
      return GL_REPEAT;
    case gl_texture_wrap_method::mirrored_repeat:
      return GL_MIRRORED_REPEAT;
    case gl_texture_wrap_method::clamp_to_edge:
      return GL_CLAMP_TO_EDGE;
    case gl_texture_wrap_method::clamp_to_border:
      return GL_CLAMP_TO_BORDER;
    }

  ASSERT_RETURN (false, 0);
}

unsigned int enum_to_gl_const (gl_texture_filter_type type)
{
  switch (type)
    {
    case gl_texture_filter_type::magnification:
      return GL_TEXTURE_MAG_FILTER;
    case gl_texture_filter_type::minification:
      return GL_TEXTURE_MIN_FILTER;
    }

  ASSERT_RETURN (false, 0);
}
