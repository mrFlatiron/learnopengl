#ifndef IMPACT_RESULT_H
#define IMPACT_RESULT_H

#include <glm/glm.hpp>

namespace phys
{

class sphere;
class box_3d;
class mass_center;
class vector_3d;
class rotation;

class impact_result
{
public:
  impact_result ();
};

impact_result calculate_impact (const glm::vec3 &point_of_impact,
                                const mass_center &mass_lhs, const vector_3d &velocity_lhs, const rotation &rot_lhs,
                                const mass_center &mass_rhs, const vector_3d &velocity_rhs, const rotation &rot_rhs);
} //namespace phys
#endif // IMPACT_RESULT_H
