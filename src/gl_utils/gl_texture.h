#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "gl_textures_fwd.h"

class gl_texture
{
public:
  gl_texture ();
  ~gl_texture ();

  gl_texture (gl_texture_id id);
private:
  gl_texture_id m_id;
};

#endif // GL_TEXTURE_H
