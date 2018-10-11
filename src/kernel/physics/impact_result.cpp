#include "impact_result.h"
#include <glm/glm.hpp>

#include "gold/utils.h"

namespace phys
{
impact_result::impact_result ()
{

}

impact_result calculate_impact (const glm::vec3 &point_of_impact, const mass_center &mass_lhs, const vector_3d &velocity_lhs, const rotation &rot_lhs,
                               const mass_center &mass_rhs, const vector_3d &velocity_rhs, const rotation &rot_rhs)
{
  FIX_UNUSED (point_of_impact, mass_lhs, velocity_lhs, rot_lhs, mass_rhs, velocity_rhs, rot_rhs);
  return impact_result ();
}

}
