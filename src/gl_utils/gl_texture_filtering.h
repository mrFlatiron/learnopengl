#ifndef GL_TEXTURE_FILTERING_H
#define GL_TEXTURE_FILTERING_H

#include "gl_textures_fwd.h"
#include "gold/enum/containers/enum_vector.h"

struct gl_texture_filtering
{
  bool use_mipmaps = false;
  gl_texture_filter_method mipmap_method = gl_texture_filter_method::nearest;
  gl_texture_filter_method pixel_method = gl_texture_filter_method::nearest;

  unsigned int to_gl_const () const;
};

#endif // GL_TEXTURE_FILTERING_H
