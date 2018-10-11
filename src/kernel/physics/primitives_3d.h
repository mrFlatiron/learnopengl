#ifndef PRIMITIVES_3D_H
#define PRIMITIVES_3D_H

#include <glm/glm.hpp>
#include "gold/enum/enum_range.h"
#include "kernel/math/math.h"

namespace phys
{

class flat_surface
{
public:
  flat_surface () = default;
  flat_surface (const glm::vec3 &surface_point_arg, const glm::vec3 &normal_arg)
    : m_surface_point (surface_point_arg),
      m_normal (glm::normalize (normal_arg))
  {
  }

  inline const glm::vec3 &surface_point () const {return m_surface_point;}
  inline const glm::vec3 &normal () const {return m_normal;}

  inline std::optional<glm::vec3> vector_intersection (const glm::vec3 &vector_base,
                                                     const glm::vec3 &vector_direction) const
  {
    auto to_surface = m_surface_point - vector_base;
    auto to_surface_perp_len_signed = glm::dot (to_surface, m_normal);
    auto orth_base_point = vector_base + to_surface_perp_len_signed * m_normal;
    auto orth = orth_base_point - vector_base;
    auto projection_on_orth = glm::dot (vector_direction, orth);

    if (projection_on_orth < 1)
      return std::nullopt;

    return vector_base + vector_direction / projection_on_orth;
  }
private:
  glm::vec3 m_surface_point = {0, 0, 0};
  glm::vec3 m_normal = {0, 0, 1};
};

class sphere
{
public:
  sphere () = default;
  sphere (const glm::vec3 &center,
          float radius)
    : m_center (center),
      m_radius (radius)
  {}

  inline const glm::vec3 &center () const {return m_center;}
  inline float radius () const {return m_radius;}
private:
  glm::vec3 m_center;
  float m_radius = 0;
};

class box_3d
{
public:
  enum class face
  {
    x_near,
    x_far,
    y_near,
    y_far,
    z_near,
    z_far,
  };
public:
  box_3d () = default;
  box_3d (const glm::vec3 &base_arg,
          const glm::vec3 &x_edge_arg,
          const glm::vec3 &y_edge_arg,
          const glm::vec3 &z_edge_arg)
    : m_base_vertex (base_arg),
      m_x_edge (x_edge_arg),
      m_y_edge (y_edge_arg),
      m_z_edge (z_edge_arg)
  {}

  inline glm::vec3 center () const
  {
    return m_base_vertex + 0.5f * (m_x_edge + m_y_edge + m_z_edge);
  }

  inline glm::vec3 face_vector (face f) const
  {
    switch (f)
      {
      case face::x_near:
        return -m_x_edge * 0.5f;
      case face::x_far:
        return m_x_edge * 0.5f;
      case face::y_near:
        return -m_y_edge * 0.5f;
      case face::y_far:
        return m_y_edge * 0.5f;
      case face::z_near:
        return -m_z_edge * 0.5f;
      case face::z_far:
        return m_z_edge * 0.5f;
      }
  }

  inline glm::vec3 face_normal (face f) const
  {
    return glm::normalize (face_vector (f));
  }



  inline glm::vec3 face_center (face f) const
  {
    return center () + face_vector (f);
  }

  inline float center_to_face_dist (face f) const
  {
    return math::length (face_vector (f));
  }

  inline std::optional<glm::vec3> central_vector_intersection (const glm::vec3 &vector) const
  {
    float min_val_sqr = -1;
    std::optional<glm::vec3> point_of_intersection;

    for (face f : enum_range<face> ())
      {
        auto point = flat_surface (face_center (f), face_normal (f)).vector_intersection (center (), vector);

        if (!point)
          continue;

        auto clamped_vec = *point - center ();

        auto val_sqr = glm::dot (clamped_vec, clamped_vec);

        if (min_val_sqr < 0 || min_val_sqr > val_sqr)
          {
            min_val_sqr = val_sqr;
            point_of_intersection = point;
          }
      }

    if (min_val_sqr < 0)
      return std::nullopt;

    if (min_val_sqr > glm::dot (vector, vector))
      return std::nullopt;

    return point_of_intersection;
  }

private:
  glm::vec3 m_base_vertex {-1, -1, -1};
  glm::vec3 m_x_edge {1, 0, 0};
  glm::vec3 m_y_edge {0, 1, 0};
  glm::vec3 m_z_edge {0, 0, 1};
};

constexpr int enum_end (box_3d::face) {return 6;}

using bounding_area_t = std::variant<box_3d, sphere>;

} //namespace phys

#endif // PRIMITIVES_3D_H
