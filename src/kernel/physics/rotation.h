#ifndef ROTATION_H
#define ROTATION_H

#include <glm/glm.hpp>

namespace phys
{
class rotation
{
public:
  rotation ();
private:
  glm::vec3 m_axis {1, 0, 0};
  float m_angle_speed = 0;
};
} //namespace phys
#endif // ROTATION_H
