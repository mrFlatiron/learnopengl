#include "gl_polar_camera.h"
#include <glm/gtx/transform.hpp>
#include <cstdio>

gl_polar_camera::gl_polar_camera ()
{

}

glm::mat4 gl_polar_camera::matrix () const
{
  return convention_matrix () * rotation_matrix () * glm::translate (-m_pos);
}

glm::vec3 gl_polar_camera::direction () const
{
  return compute_x_axis ();
}

void gl_polar_camera::to_init_state ()
{
  m_pos = glm::vec3 (0, 0, 0);
  m_phi = 0;
  m_psi = 0;
}

void gl_polar_camera::move_forward (float val)
{
  printf ("moving val: %.6f\n", val);
  fflush (stdout);
  m_pos += direction () * val;
}

void gl_polar_camera::move_backward (float val)
{
  m_pos -= direction () * val;
}

void gl_polar_camera::move_right (float val)
{
  m_pos -= glm::vec3 (axis_matrix ()[1]) * val;
}

void gl_polar_camera::move_left (float val)
{
  m_pos += glm::vec3 (axis_matrix ()[1]) * val;
}

void gl_polar_camera::rotate (float phi, float psi)
{
  m_phi = sum_angles (m_phi, phi);

  if (fabs (m_psi - M_PI / 2) < 0.1)
    {
      if (psi > 0)
        return;
    }

  if (fabs (m_psi + M_PI / 2) < 0.1)
    {
      if (psi < 0)
        return;
    }

  m_psi = sum_psi (m_psi, psi);
}

glm::mat4 gl_polar_camera::rotation_matrix () const
{
  auto axis_mat = axis_matrix ();

  auto x_axis = axis_mat[0];
  auto y_axis = axis_mat[1];
  auto z_axis = axis_mat[2];

  auto x_image = glm::vec3 (x_axis[0], y_axis[0], z_axis[0]);
  auto y_image = glm::vec3 (x_axis[1], y_axis[1], z_axis[1]);
  auto z_image = glm::vec3 (x_axis[2], y_axis[2], z_axis[2]);

  return glm::mat4
      (
        glm::vec4 (x_image, 0),
        glm::vec4 (y_image, 0),
        glm::vec4 (z_image, 0),
        glm::vec4 (0, 0, 0, 1)
        );
}

glm::mat4 gl_polar_camera::convention_matrix () const
{
  return glm::mat4
      (
        glm::vec4 (0, 0, -1, 0),
        glm::vec4 (-1, 0, 0, 0),
        glm::vec4 (0, 1, 0, 0),
        glm::vec4 (0, 0, 0, 1)
        );
}

glm::mat4 gl_polar_camera::axis_matrix () const
{
  auto x_axis = compute_x_axis ();
  auto up = glm::vec3 (0, 0, 1);

  glm::vec3 y_axis;
  glm::vec3 z_axis;

  if (fabs (x_axis[0]) < 1e-6 && fabs (x_axis[1]) < 1e-6 && fabs (x_axis[2] - 1) < 1e-6)
    {
      z_axis = glm::vec3 (-cos (m_phi), -sin (m_phi), 0);
      x_axis = glm::vec3 (0, 0, 1);
      y_axis = glm::cross (x_axis, z_axis);
    }
  else
    {
      if (fabs (x_axis[0]) < 1e-6 && fabs (x_axis[1]) < 1e-6 && fabs (x_axis[2] + 1) < 1e-6)
        {
          z_axis = glm::vec3 (cos (m_phi), sin (m_phi), 0);
          x_axis = glm::vec3 (0, 0, -1);
          y_axis = glm::cross (x_axis, z_axis);
        }
      else
      {
        y_axis = glm::cross (up, x_axis);
        z_axis = glm::cross (x_axis, y_axis);
      }
    }

  x_axis = glm::normalize (x_axis);
  y_axis = glm::normalize (y_axis);
  z_axis = glm::normalize (z_axis);

  return glm::mat4
      (
        glm::vec4 (x_axis, 0),
        glm::vec4 (y_axis, 0),
        glm::vec4 (z_axis, 0),
        glm::vec4 (0, 0, 0, 1)
        );
}

float gl_polar_camera::sum_angles (float a, float b)
{
  auto result = a + b;

  while (result < - M_PI)
    result += 2 * M_PI;

  while (result >= M_PI)
    result -= 2 * M_PI;

  return result;
}

float gl_polar_camera::sum_psi (float a, float b)
{
  auto sum = sum_angles (a, b);

  if (sum > - M_PI / 2 && sum < M_PI / 2)
    return sum;

  if (fabs (sum - M_PI /  2) >= fabs (sum + M_PI / 2))
    {
      return -M_PI / 2 + 0.0125;
    }

  return M_PI / 2 - 0.0125;
}

glm::vec3 gl_polar_camera::compute_x_axis () const
{
  return glm::normalize (glm::vec3 (cos (m_phi) * cos (m_psi), sin (m_phi) * cos (m_psi), sin (m_psi)));
}
