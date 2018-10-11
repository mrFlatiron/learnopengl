#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "primitives_3d.h"

namespace phys
{
  inline bool is_overlap (const box_3d &box_lhs, const box_3d &box_rhs)
  {
    auto left_most = box_lhs.center ();
    auto right_most = box_rhs.center ();

    auto l_to_r = right_most - left_most;

    auto with_rhs = box_rhs.central_vector_intersection (-l_to_r);
    auto with_lhs = box_lhs.central_vector_intersection (l_to_r);

    if (!with_lhs || !with_rhs)
      return true;

    return glm::dot (*with_lhs - *with_rhs, l_to_r) >= 0;
  }

  inline bool is_overlap (const sphere &sph, const box_3d &box)
  {
    auto possible_intersectioin = box.central_vector_intersection (sph.center () - box.center ());

    if (!possible_intersectioin)
      return true;

    auto sph_center_to_intersect = *possible_intersectioin - sph.center ();

    return glm::dot (sph_center_to_intersect, sph_center_to_intersect) <= glm::dot (sph.radius (), sph.radius ());
  }

  inline bool is_overlap (const sphere &sph_lhs, const sphere &sph_rhs)
  {
    auto cent_vec = sph_lhs.center () - sph_rhs.center ();
    auto dist = math::length (cent_vec);

    return dist < sph_lhs.radius () + sph_rhs.radius ();
  }

  inline bool is_overlap (const bounding_area_t &lhs,
                          const bounding_area_t &rhs)
  {
    if (lhs.index () == 0u && rhs.index () == 0u)
      return is_overlap (std::get<box_3d> (lhs), std::get<box_3d> (rhs));

    if (lhs.index () == 0u && rhs.index () == 1u)
      return is_overlap (std::get<sphere> (rhs), std::get<box_3d> (lhs));

    if (lhs.index () == 1u && rhs.index () == 0u)
      return is_overlap (std::get<sphere> (lhs), std::get<box_3d> (rhs));

    return is_overlap (std::get<sphere> (lhs), std::get<sphere> (rhs));
  }
}

#endif // COLLISIONS_H
