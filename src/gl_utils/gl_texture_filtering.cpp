#include "gl_texture_filtering.h"
#include "gl_headers.h"

unsigned int gl_texture_filtering::to_gl_const () const
{
  if (!use_mipmaps)
    {
      switch (pixel_method)
        {
        case gl_texture_filter_method::linear:
          return GL_LINEAR;
        case gl_texture_filter_method::nearest:
          return GL_NEAREST;
        }
    }

  switch (mipmap_method)
    {
    case gl_texture_filter_method::linear:
      switch (pixel_method)
        {
        case gl_texture_filter_method::linear:
          return GL_LINEAR_MIPMAP_LINEAR;
        case gl_texture_filter_method::nearest:
          return GL_LINEAR_MIPMAP_NEAREST;
        }
      break;
    case gl_texture_filter_method::nearest:
      switch (pixel_method)
        {
        case gl_texture_filter_method::linear:
          return GL_NEAREST_MIPMAP_LINEAR;
        case gl_texture_filter_method::nearest:
          return GL_NEAREST_MIPMAP_NEAREST;
        }
      break;
    }

  ASSERT_RETURN (false, 0);
}
