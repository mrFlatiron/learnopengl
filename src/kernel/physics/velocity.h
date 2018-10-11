#ifndef VELOCITY_H
#define VELOCITY_H

#include <glm/glm.hpp>

namespace phys
{
class vector_3d
{
public:
  vector_3d ();
private:
  glm::vec3 m_direction {1, 0, 0};
  float m_value = 0;
};
} //namespace phys
#endif // VELOCITY_H
