#include "gl_matrix_stacker.h"

gl_matrix_stacker::gl_matrix_stacker (glm::mat4 &stack_base)
  : m_stacked_matrix (stack_base),
    m_original_matrix (stack_base)
{

}

gl_matrix_stacker::~gl_matrix_stacker ()
{
  m_stacked_matrix = m_original_matrix;
}

gl_matrix_stacker::self &gl_matrix_stacker::mult_left (const glm::mat4 &matrix)
{
  m_stacked_matrix = matrix * m_stacked_matrix;
  return *this;
}

const glm::mat4 &gl_matrix_stacker::matrix () const
{
  return m_stacked_matrix;
}
