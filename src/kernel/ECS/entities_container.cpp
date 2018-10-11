#include "entities_container.h"
#include "kernel/ECS/physical_props.h"

entities_container::entities_container ()
{

}

entity_id entities_container::allocate_entity ()
{
  m_max_id++;
  return m_max_id;
}

void entities_container::set_physycal_props (entity_id id, const physical_props &props)
{
  m_phys_props[id] = props;
}

const physical_props *entities_container::phys_props (entity_id id) const
{
  auto it = m_phys_props.find (id);
  if (it == m_phys_props.end ())
    return nullptr;

  return &it->second;
}

physical_props *entities_container::phys_props (entity_id id)
{
  auto it = m_phys_props.find (id);
  if (it == m_phys_props.end ())
    return nullptr;

  return &it->second;
}
