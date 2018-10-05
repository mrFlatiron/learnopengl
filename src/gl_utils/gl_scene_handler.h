#ifndef GL_SCENE_HANDLER_H
#define GL_SCENE_HANDLER_H

#include <glm/glm.hpp>

class gl_scene_handler
{
public:
  gl_scene_handler ();

  const glm::mat4 &projection_matrix () const;
  glm::mat4 &projection_matrix ();

  const glm::mat4 &view_matrix () const;
  glm::mat4 &view_matrix ();

  const glm::mat4 &model_matrix () const;
  glm::mat4 &model_matrix ();

  glm::mat4 result_matrix () const;
private:
  glm::mat4 m_projection_matrix {1};
  glm::mat4 m_view_matrix {1};
  glm::mat4 m_model_matrix {1};
};

#endif // GL_SCENE_HANDLER_H
