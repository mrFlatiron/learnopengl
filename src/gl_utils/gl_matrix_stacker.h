#ifndef GL_MATRIX_STACKER_H
#define GL_MATRIX_STACKER_H

#include <glm/glm.hpp>
#include "gold/utils.h"

class gl_matrix_stacker : uncopiable, unmovable
{
  using self = gl_matrix_stacker;
public:
  gl_matrix_stacker (glm::mat4 &stack_base);
  ~gl_matrix_stacker ();

  self &mult_left (const glm::mat4 &matrix);

  const glm::mat4 &matrix () const;
private:
  glm::mat4 &m_stacked_matrix;
  const glm::mat4 m_original_matrix;
};

#endif // GL_MATRIX_STACKER_H
