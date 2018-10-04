#include "gl_camera.h"
#include <cstdio>
#include <cmath>
#include <glm/gtx/transform.hpp>

gl_camera::gl_camera ()
{
  to_init_state ();
}

glm::mat4 gl_camera::matrix () const
{

//  return glm::lookAt ()

  return glm::translate (rotate_matrix (), -m_pos);

//  return m_matrix;

//  auto new_z = -m_direction;
//  auto new_x = -glm::cross (m_up, new_z);
//  auto new_y = -glm::cross (new_z, new_x);


//  auto retval = glm::mat4 (glm::vec4 (new_x, 0), glm::vec4 (new_y, 0) , glm::vec4 (new_z, 0),
//                           glm::vec4 (0, 0, 0, 1));


//  retval = glm::translate (retval, -m_pos);

//  auto glm_look = glm::lookAt (m_pos, m_pos + m_direction, m_up);

//  return retval;
}

void gl_camera::move_forward (float val)
{
//  auto translate = glm::translate (glm::mat4 (1), glm::vec3 (0, 0, val));
//  m_matrix = translate * m_matrix;
  m_pos -= val * direction ();
}

void gl_camera::move_backward (float val)
{
//  auto translate = glm::translate (glm::mat4 (1), glm::vec3 (0, 0, -val));
//  m_matrix = translate * m_matrix;
  m_pos += val * direction ();
}

//void gl_camera::rotate (float up, float side)
//{
//  m_matrix = glm::rotate (glm::mat4 (1.0f), angle, glm::normalize (axis)) * m_matrix;
//  m_alpha += alpha_angle;
//  m_beta += beta_angle;


//}

void gl_camera::to_init_state ()
{
  m_pos = glm::vec3 ();
  m_alpha = 0;
  m_beta = 0;
  m_gamma = 0;
//  m_up = glm::vec3 (0.0f, 0.0f, 1.0f);
//  m_direction = glm::vec3 (1.0f, .0f, 0.0f);

//  m_matrix = glm::mat4
//      (glm::vec4 (1, 0, 0, 0),
//       glm::vec4 (0, 1, 0, 0),
//       glm::vec4 (0, 0, -1, 0),
//       glm::vec4 (0, 0, 0, 1));
}

glm::vec3 gl_camera::direction () const
{
  return rotate_matrix ()[0];
}

glm::mat4 gl_camera::rotate_matrix () const
{
  auto alpha_mat = glm::rotate (glm::mat4 (1), m_alpha, glm::vec3 (0, 0, 1));
  glm::vec3 N_axis = alpha_mat[0];

  auto beta_mat = glm::rotate (glm::mat4 (1), m_beta, N_axis);
  glm::vec3 z_axis = beta_mat[2];

  auto gamma_mat = glm::rotate (glm::mat4 (1), m_gamma, z_axis);
  glm::vec3 x_axis = gamma_mat * glm::vec4 (N_axis, 1);
  glm::vec3 y_axis = glm::cross (z_axis, x_axis);

  return glm::mat4
      (
        glm::vec4 (x_axis, 0),
        glm::vec4 (y_axis, 0),
        glm::vec4 (z_axis, 0),
        glm::vec4 (0, 0, 0, 1)
        );
}
