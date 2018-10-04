#ifndef GL_CAMERA_H
#define GL_CAMERA_H

#include <glm/glm.hpp>

class gl_camera
{
public:
  gl_camera ();
  glm::mat4 matrix () const;
  void move_forward (float val);
  void move_backward (float val);
  void rotate (float angle, glm::vec3 axis);
  void to_init_state ();

  glm::vec3 direction () const;
private:
//  glm::vec3 m_up; //normalized
//  glm::vec3 m_direction;
  glm::vec3 m_pos;
//  glm::mat4 m_matrix;

  float m_alpha = 0;
  float m_beta = 0;
  float m_gamma = 0;

//  int m_zoom_val = 1;
private:
  glm::mat4 rotate_matrix () const;
};

#endif // GL_CAMERA_H
