#ifndef GL_ARRAY_OBJECT_H
#define GL_ARRAY_OBJECT_H

#include "gold/enum/containers/enum_vector.h"


enum class gl_attribute
{
  pos,
  tex_coords,
  color,
  normals,
};

constexpr int enum_end (gl_attribute) {return 4;}
unsigned int enum_to_gl_const (gl_attribute attr);


struct gl_attr_params
{
  size_t offset = 0;
  size_t length = 0;
  bool is_allocated = false;
  bool is_enabled = false;
};

struct gl_array_layout
{
  gl_array_layout () = default;
  ~gl_array_layout () = default;

  gl_array_layout (const gl_array_layout &rhs) = default;
  gl_array_layout &operator= (const gl_array_layout &) = default;

  gl_array_layout (gl_array_layout &&rhs);
  gl_array_layout &operator= (gl_array_layout &&rhs);

  size_t vertex_count = 0;
  enum_vector<gl_attribute, gl_attr_params> attr_params;

  size_t vertex_length () const;
  size_t total_size () const;
  size_t stride () const;
};

namespace detail
{
template<typename T>
class gl_vertex_base
{
  friend class gl_array_object;
public:
  T m_data_begin = nullptr;
  const gl_array_layout *m_layout = nullptr;

  gl_vertex_base (T data_begin, const gl_array_layout *layout)
  {
    m_data_begin = data_begin;
    m_layout = layout;
  }

  std::pair<const float *, size_t> get_attribute (gl_attribute attr) const
  {
    gl_attr_params &params = m_layout->attr_params[attr];
    ASSERT_RETURN (params.is_allocated, std::make_pair (nullptr, 0));

    const float *pos = m_data_begin + params.offset;

    return std::make_pair (pos, params.length);
  }
};
}

class gl_mutable_vertex : private detail::gl_vertex_base<float *>
{
  friend class gl_array_object;
  using base = detail::gl_vertex_base<float *>;
public:
  gl_mutable_vertex (float *data_begin, const gl_array_layout *layout);
  using base::get_attribute;
  void set_attribute (gl_attribute attr, const std::vector<float> &values);
};

class gl_const_vertex : private detail::gl_vertex_base<const float *>
{
  friend class gl_array_object;
  using base = detail::gl_vertex_base<const float *>;
public:
  gl_const_vertex (const float *data_begin, const gl_array_layout *layout);
  using base::get_attribute;
};

class gl_array_object
{
public:
  gl_array_object ();
  ~gl_array_object ();

  gl_array_object (const gl_array_object &) = delete;
  gl_array_object &operator= (const gl_array_object &) = delete;

  gl_array_object (gl_array_object &&rhs);
  gl_array_object &operator= (gl_array_object &&rhs);

  gl_array_object (std::vector<float> &&data, const gl_array_layout &layout);

  gl_array_object (const gl_array_layout &layout);
  const gl_array_layout &layout () const;

  gl_const_vertex get_vertex_handle (size_t index) const;
  gl_mutable_vertex get_vertex_handle (size_t index);

  bool activate ();
  bool send_to_gpu (unsigned int mode);

  static gl_array_object make_textured_cube ();
private:
  unsigned int m_vao_id = 0;
  unsigned int m_vbo_id = 0;
  std::vector<float> m_data;
  gl_array_layout m_layout;
private:
  bool bind_all ();
};



#endif // GL_ARRAY_OBJECT_H
