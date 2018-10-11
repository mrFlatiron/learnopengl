#ifndef TYPESAFE_ID_H
#define TYPESAFE_ID_H

#include "precompiled/precompiled_header.h"

template<typename IdName, int64_t invalid_start_index = -1>
class typesafe_id_generic
{
private:
  using self = typesafe_id_generic<IdName, invalid_start_index>;
  int64_t m_id = invalid_start_index;
public:
  typesafe_id_generic () {}

private:
  explicit typesafe_id_generic (int64_t id) : m_id (id) {}
public:

  self operator++ (int) {self temp = *this; m_id++; return temp;}
  self operator++ ()    {++m_id; return *this;}

  template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, int64_t>, void>>
  explicit operator T () const {return static_cast<T> (m_id);}
  int64_t get_underlying () const {return m_id;}


  bool operator == (self rhs) const {return m_id == rhs.m_id;}
  bool operator != (self rhs) const {return m_id != rhs.m_id;}
  bool operator <  (self rhs) const {return m_id < rhs.m_id;}
  bool operator >  (self rhs) const {return m_id > rhs.m_id;}
  bool operator <= (self rhs) const {return m_id <= rhs.m_id;}
  bool operator >= (self rhs) const {return m_id >= rhs.m_id;}

  bool is_valid () const {return m_id > invalid_start_index;}
  void invalidate () {m_id = invalid_start_index;}

  static self from_underlying (int64_t id) {return self (id);}

  using base = int64_t;

};

namespace std
{
  template<typename IdName, int64_t invalid_start_index>
  struct hash<typesafe_id_generic<IdName, invalid_start_index>>
  {
    std::size_t operator() (const typesafe_id_generic<IdName, invalid_start_index>& k) const
    {
      return std::hash<int64_t> ().operator () (static_cast<int64_t> (k));
    }
  };
}

#define MAKE_TS_ID(NEWIDNAME) \
  class NEWIDNAME##_tag {}; \
  using NEWIDNAME = typesafe_id_generic<NEWIDNAME##_tag>; \
  static_assert (true, "")

#endif // TYPESAFE_ID_H
