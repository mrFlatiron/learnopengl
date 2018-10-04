#ifndef GL_TEXTURES_CONTAINER_H
#define GL_TEXTURES_CONTAINER_H

#include "gl_textures_fwd.h"

class gl_textures_container
{
public:
  gl_textures_container ();
  ~gl_textures_container ();
private:
  std::map<gl_texture_id, unique_ptr<gl_texture>> m_textures;
};

#endif // GL_TEXTURES_CONTAINER_H
