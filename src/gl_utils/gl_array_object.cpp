#include "gl_array_object.h"
#include "error_check.h"
#include "gl_headers.h"

#include "gold/range_utils.h"
#include "gold/utils.h"

gl_array_object::gl_array_object ()
{

}

gl_array_object::~gl_array_object ()
{
}

gl_array_object &gl_array_object::operator= (gl_array_object &&rhs)
{
  m_vao_id = rhs.m_vao_id;
  m_vbo_id = rhs.m_vbo_id;
  m_data = std::move (rhs.m_data);
  m_layout = std::move (rhs.m_layout);

  rhs.m_vao_id = 0;
  rhs.m_vbo_id = 0;

  return *this;
}

gl_array_object::gl_array_object (gl_array_object &&rhs)
  : m_vao_id (rhs.m_vao_id),
    m_vbo_id (rhs.m_vbo_id),
    m_data (std::move (rhs.m_data)),
    m_layout (std::move (rhs.m_layout))
{
  rhs.m_vao_id = 0;
  rhs.m_vbo_id = 0;
}

gl_array_object::gl_array_object (std::vector<float> &&data, const gl_array_layout &layout)
  : m_data (std::move (data))
{
  m_layout = layout;

  glGenVertexArrays (1, &m_vao_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glGenVertexArrays");
      return;
    }

  glGenBuffers (1, &m_vbo_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glGenBuffers");
      return;
    }

  bind_all ();
}

gl_array_object::gl_array_object (const gl_array_layout &layout)
{
  m_layout = layout;

  m_data.resize (layout.total_size ());

  glGenVertexArrays (1, &m_vao_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glGenVertexArrays");
      return;
    }

  glGenBuffers (1, &m_vbo_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glGenBuffers");
      return;
    }

  bind_all ();
}

const gl_array_layout &gl_array_object::layout () const
{
  return m_layout;
}

gl_const_vertex gl_array_object::get_vertex_handle (size_t index) const
{
  auto pos = m_layout.vertex_length () * index;

  return gl_const_vertex (m_data.data () + pos, &m_layout);
}

gl_mutable_vertex gl_array_object::get_vertex_handle (size_t index)
{
  auto pos = m_layout.vertex_length () * index;

  return gl_mutable_vertex (m_data.data () + pos, &m_layout);
}

bool gl_array_object::activate ()
{
  if (!m_vao_id || !m_vbo_id)
    {
      gl_logger.log_error ("No vao or vbo to activate");
      return false;
    }

  glBindVertexArray (m_vao_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glBindVertexArray");
      return false;
    }

  return true;
}

bool gl_array_object::send_to_gpu (unsigned int mode)
{
  glBufferData (GL_ARRAY_BUFFER, m_layout.total_size () * sizeof (float), m_data.data (), mode);

  for (auto attr: enum_range<gl_attribute> ())
    {
      const gl_attr_params &params = layout ().attr_params[attr];

      if (layout ().attr_params[attr].is_allocated)
        glVertexAttribPointer (enum_to_gl_const (attr), params.length, GL_FLOAT, GL_FALSE, m_layout.stride () * sizeof (float), (void *)(params.offset * sizeof (float)));
    }

  for (auto attr : enum_range<gl_attribute> ())
    {
      const gl_attr_params &params = layout ().attr_params[attr];

      if (params.is_enabled)
        glEnableVertexAttribArray (enum_to_gl_const (attr));
    }

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to send_to_gpu");
      return false;
    }

  return true;
}

gl_array_object gl_array_object::make_textured_cube ()
{
  vector<float> cube_vertices = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0, 0, -1,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0, 0, -1,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0, 0, -1,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0, 0, -1,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0, 0, -1,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0, 0, -1,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0, 0, 1,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0, 0, 1,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0, 0, 1,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0, 0, 1,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0, 0, 1,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0, 0, 1,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1, 0, 0,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1, 0, 0,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1, 0, 0,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1, 0, 0,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1, 0, 0,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1, 0, 0,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1, 0, 0,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1, 0, 0,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1, 0, 0,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1, 0, 0,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1, 0, 0,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1, 0, 0,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0, -1, 0,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0, -1, 0,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0, -1, 0,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0, -1, 0,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0, -1, 0,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0, -1, 0,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0, 1, 0,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0, 1, 0,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0, 1, 0,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0, 1, 0,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0, 1, 0,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0, 1, 0,
  };

  gl_array_layout layout;

  layout.attr_params[gl_attribute::pos].is_allocated = true;
  layout.attr_params[gl_attribute::pos].is_enabled = true;
  layout.attr_params[gl_attribute::pos].length = 3;
  layout.attr_params[gl_attribute::pos].offset = 0;

  layout.attr_params[gl_attribute::tex_coords].is_allocated = true;
  layout.attr_params[gl_attribute::tex_coords].is_enabled = true;
  layout.attr_params[gl_attribute::tex_coords].length = 2;
  layout.attr_params[gl_attribute::tex_coords].offset = 3;

  layout.attr_params[gl_attribute::normals].is_allocated = true;
  layout.attr_params[gl_attribute::normals].is_enabled = true;
  layout.attr_params[gl_attribute::normals].length = 3;
  layout.attr_params[gl_attribute::normals].offset = 5;

  layout.vertex_count = 36;

  return gl_array_object (std::move (cube_vertices), layout);
}

bool gl_array_object::bind_all ()
{
  glBindVertexArray (m_vao_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glBindVertexArray");
      return false;
    }

  glBindBuffer (GL_ARRAY_BUFFER, m_vbo_id);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glBindBuffer");
      return false;
    }

  return true;
}

gl_array_layout::gl_array_layout (gl_array_layout &&rhs)
{
  vertex_count = rhs.vertex_count;
  attr_params = rhs.attr_params;

  rhs.vertex_count = 0;
}

gl_array_layout &gl_array_layout::operator= (gl_array_layout &&rhs)
{
  vertex_count = rhs.vertex_count;
  attr_params = rhs.attr_params;

  rhs.vertex_count = 0;

  return *this;
}

size_t gl_array_layout::vertex_length () const
{
  size_t retval = 0;

  for (auto attr : enum_range<gl_attribute> ())
    {
      if (attr_params[attr].is_allocated)
        retval += attr_params[attr].length;
    }

  return retval;
}

size_t gl_array_layout::total_size () const
{
  return vertex_count * vertex_length ();
}

size_t gl_array_layout::stride () const
{
  return vertex_length ();
}

unsigned int enum_to_gl_const (gl_attribute attr)
{
  switch (attr)
    {
    case gl_attribute::pos:
      return 0;
    case gl_attribute::tex_coords:
      return 1;
    case gl_attribute::color:
      return 2;
    case gl_attribute::normals:
      return 3;
    }

  ASSERT_RETURN (false, 0);
}

gl_mutable_vertex::gl_mutable_vertex (float *data_begin, const gl_array_layout *layout)
  : base (data_begin, layout)
{

}

void gl_mutable_vertex::set_attribute (gl_attribute attr, const std::vector<float> &values)
{
  auto &params = m_layout->attr_params[attr];
  ASSERT_RETURN (params.is_allocated && params.length == values.size (), );

  auto insert_pos = m_data_begin + params.offset;

  for (int i : range (isize (values)))
    insert_pos[i] = values[i];
}

gl_const_vertex::gl_const_vertex (const float *data_begin, const gl_array_layout *layout)
  : base (data_begin, layout)
{

}
