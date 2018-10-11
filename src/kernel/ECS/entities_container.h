#ifndef ENTITIES_CONTAINER_H
#define ENTITIES_CONTAINER_H

#include "entity_fwd.h"

class physical_props;

class entities_container
{
public:
  entities_container ();

  entity_id allocate_entity ();

  void set_physycal_props (entity_id id, const physical_props &props);

  const physical_props *phys_props (entity_id id) const;
  physical_props *phys_props (entity_id id);
private:
  entity_id m_max_id;

  std::map<entity_id, physical_props> m_phys_props;
};

#endif // ENTITIES_CONTAINER_H
