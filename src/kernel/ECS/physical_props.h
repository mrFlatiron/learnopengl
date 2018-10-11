#ifndef PHYSICAL_PROPS_H
#define PHYSICAL_PROPS_H

#include <glm/glm.hpp>
#include "kernel/physics/primitives_3d.h"
#include "kernel/physics/mass_center.h"

class physical_props
{
public:
  physical_props ();

  inline void set_bounding_area (const phys::bounding_area_t &area) {m_bounding_area = area;}
  inline void set_bounding_area (const phys::box_3d &box) {m_bounding_area = box;}
  inline void set_bounding_area (const phys::sphere &sph) {m_bounding_area = sph;}

  inline void set_is_ghost (bool val = true) {m_is_ghost = val;}
  inline void set_mass (int val) {m_mass = val;}
  inline void set_velocity (const glm::vec3 &vel) {m_velocity = vel;}
  inline void set_acceleration (const glm::vec3 &acc) {m_acceleration = acc;}
  inline void set_eye_direction (const glm::vec3 &dir) {m_eye_direction = dir;}
  inline void set_max_velocity (float val) {m_max_velocity = val;}
  inline void set_moving_force (float val) {m_moving_force = val;}

  inline const phys::bounding_area_t bounding_area () const {return m_bounding_area;}
  inline bool is_ghost () const {return m_is_ghost;}
  inline int mass () const {return m_mass;}
  inline const glm::vec3 &velocity () const {return m_velocity;}
  inline const glm::vec3 &acceleration () const {return m_acceleration;}
  inline const glm::vec3 &eye_direction () const {return m_eye_direction;}
  inline float max_velocity () const {return m_max_velocity;}
  inline float moving_force () const {return m_moving_force;}

private:
  bool m_is_ghost = false;
  phys::bounding_area_t m_bounding_area;
  int m_mass = 1;
  glm::vec3 m_velocity;
  glm::vec3 m_acceleration;
  glm::vec3 m_eye_direction {1, 0, 0}; //normalized
  float m_max_velocity = 0;
  float m_moving_force = -1;

};

#endif // PHYSICAL_PROPS_H
