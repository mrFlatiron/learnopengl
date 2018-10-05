#include "gl_scene_handler.h"

gl_scene_handler::gl_scene_handler ()
{

}

const glm::mat4 &gl_scene_handler::projection_matrix () const
{
  return m_projection_matrix;
}

glm::mat4 &gl_scene_handler::projection_matrix ()
{
  return m_projection_matrix;
}

const glm::mat4 &gl_scene_handler::view_matrix () const
{
  return m_view_matrix;
}

glm::mat4 &gl_scene_handler::view_matrix ()
{
  return m_view_matrix;
}

const glm::mat4 &gl_scene_handler::model_matrix () const
{
  return m_model_matrix;
}

glm::mat4 &gl_scene_handler::model_matrix ()
{
  return m_model_matrix;
}

glm::mat4 gl_scene_handler::result_matrix () const
{
  return m_projection_matrix * m_view_matrix * m_model_matrix;
}
