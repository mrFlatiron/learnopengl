#ifndef MASS_CENTER_H
#define MASS_CENTER_H

#include <glm/glm.hpp>

namespace phys
{
class mass_center
{
public:
  mass_center ();
  mass_center (const glm::vec3 &pos, int mass_arg)
    : m_position (pos),
      m_mass (mass_arg)
  {}

  inline const glm::vec3 &position () const {return m_position;}
  inline int mass () const {return m_mass;}
private:
  glm::vec3 m_position {0, 0 ,0};
  int m_mass = 0;
};

} //namespace phys
#endif // MASS_CENTER_H
