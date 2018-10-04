#ifndef GL_TEXTURES_FWD_H
#define GL_TEXTURES_FWD_H

#include "gold/typesafe_id.h"

struct gl_texture_id_tag {};
using gl_texture_id = typesafe_id_generic<gl_texture_id_tag, 0>;

class gl_textures_container;
class gl_texture;

enum class gl_texture_wrap_direction
{
  left_right,
  top_bottom,
};

enum class gl_texture_wrap_method
{
  repeat,
  mirrored_repeat,
  clamp_to_edge,
  clamp_to_border,
};

enum class gl_texture_filter_type
{
  magnification,
  minification,
};

enum class gl_texture_filter_method
{
  nearest,
  linear,
};

struct gl_texture_filtering;

unsigned int enum_to_gl_const (gl_texture_wrap_direction dir);
unsigned int enum_to_gl_const (gl_texture_wrap_method method);
unsigned int enum_to_gl_const (gl_texture_filter_type type);

#endif // GL_TEXTURES_FWD_H
