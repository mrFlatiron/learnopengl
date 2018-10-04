#ifndef RANGE_UTILS_H
#define RANGE_UTILS_H

struct integer_iterator
{
  using self = integer_iterator;
  using value_type = int;
  using difference_type	= int;
  using pointer	= const int *;
  using reference = int;

  int m_internals = 0;

  integer_iterator (int start) {m_internals = start;}

  reference operator* () const {return m_internals;}
  self &operator++ () { m_internals++; return *this; }
  self operator++ (int) {self temp = *this; m_internals++; return temp;}
  bool operator== (const self &rhs) const {return m_internals == rhs.m_internals;}
  bool operator!= (const self &rhs) const {return m_internals != rhs.m_internals;}
};

struct range
{
  using value_type = int;

  int m_size = 0;

  range (int size) {m_size = size;}

  integer_iterator begin () const {return integer_iterator (0);}
  integer_iterator end () const {return integer_iterator (m_size);}
};

template<typename Range,
         typename Iter = decltype (std::declval<Range> ().begin ()),
         typename T = typename Iter::value_type>
std::vector<T> to_vector (Range &&range)
{
  std::vector<T> retval;

  for (auto it = range.begin (); it != range.end (); it++)
    retval.push_back (*it);

  return retval;
}

namespace detail
{
template<typename Range,
         typename Iter = decltype (std::declval<Range> ().begin ()),
         typename T = typename Iter::value_type>
struct range_type_helper
{
  using type = T;
};
}

template<typename Range>
using range_value_type = typename detail::range_type_helper<Range>::type;

template<typename ContainerRef,
         typename Container = std::remove_reference_t<ContainerRef>,
         typename Tuple = typename Container::value_type,
         typename Key = std::remove_const_t<decltype (std::declval<Tuple> ().first)>>
std::vector<Key> map_keys (ContainerRef &&range)
{
  std::vector<Key> retval;

  for (auto it = range.cbegin (); it != range.cend (); it++)
    retval.push_back ((*it).first);

  return retval;
}

#endif // RANGE_UTILS_H
