#ifndef OBJECT_BOUNDING_AREA_H
#define OBJECT_BOUNDING_AREA_H

#include "entity_fwd.h"

class object_bounding_area
{
public:
  object_bounding_area ();
private:
  vector<entity_id> m_bounding_objects;
};

#endif // OBJECT_BOUNDING_AREA_H
