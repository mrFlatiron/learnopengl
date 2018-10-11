#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>

namespace math
{

namespace constants
{
constexpr float cmp_eps =  2 * std::numeric_limits<float>::epsilon ();
} //namespace math::constants

inline bool fuzzy_eq (float a, float b, float eps = math::constants::cmp_eps)
{
  return fabs (a - b) < eps;
}

inline bool fuzzy_eq (const glm::vec3 &a, const glm::vec3 &b, float eps = math::constants::cmp_eps)
{
  for (int i = 0; i < 3; i++)
    if (!fuzzy_eq (a[i], b[i], eps))
      return false;

  return true;
}

inline float length (const glm::vec3 &vec)
{
  return sqrt (glm::dot (vec, vec));
}

} //namespace math

#endif // MATH_H
