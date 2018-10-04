#ifndef GL_POLAR_CAMERA_H
#define GL_POLAR_CAMERA_H

#include <glm/glm.hpp>

class gl_polar_camera
{
public:
  gl_polar_camera ();
  glm::mat4 matrix () const;
  glm::vec3 direction () const;

  void to_init_state ();
  void move_forward (float val);
  void move_backward (float val);
  void move_right (float val);
  void move_left (float val);
  void rotate (float phi, float psi);
private:
  float m_phi = 0;
  float m_psi = 0;

  glm::vec3 m_pos;
private:
  glm::mat4 rotation_matrix () const;
  glm::mat4 convention_matrix () const;
  glm::mat4 axis_matrix () const;
  static float sum_angles (float a, float b);
  static float sum_psi (float a, float b);
  glm::vec3 compute_x_axis () const;
};

#endif // GL_POLAR_CAMERA_H
