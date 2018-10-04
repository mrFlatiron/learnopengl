#include "gl_shader.h"
#include "gl_headers.h"

#include "error_check.h"

#include <cstdio>

using std::literals::operator""s;

gl_shader::gl_shader ()
{
  
}

gl_shader::~gl_shader ()
{
  if (m_id)
    glDeleteShader (m_id);
}

gl_shader::gl_shader (gl_shader &&rhs)
{
  m_src = std::move (rhs.m_src);
  m_id = rhs.m_id;
  m_type = rhs.m_type;
  
  rhs.m_id = 0;
}

gl_shader &gl_shader::operator= (gl_shader &&rhs)
{
  m_src = std::move (rhs.m_src);
  m_id = rhs.m_id;
  m_type = rhs.m_type;
  
  rhs.m_id = 0;
  
  return *this;
}

gl_shader::gl_shader (std::string &&src, gl_shader_type type)
{
  set_src (std::move (src));
  set_type (type);
  
  compile ();
}

void gl_shader::set_src (std::string &&src)
{
  m_src = std::move (src);
}

void gl_shader::set_type (gl_shader_type type)
{
  m_type = type;
}

bool gl_shader::compile ()
{
  if (m_src.empty ())
    {
      gl_logger.log_error ("Shader source text is empty");
      return false;
    }
  
  if (!m_type)
    {
      gl_logger.log_error ("Type was not set");
      return false;
    }
  
  if (!register_shader ())
    return false;
  
  auto src_raw = m_src.c_str ();
  
  glShaderSource (m_id, 1, &src_raw, nullptr);
  glCompileShader (m_id);
  
  int success;
  char log[512];
  glGetShaderiv (m_id, GL_COMPILE_STATUS, &success);
  
  if (!success)
    {
      glGetShaderInfoLog (m_id, 512, NULL, log);
      gl_logger.log_error ("Shader compilation failed. Error: %s", log);
      m_id = 0;
      return false;
    }
  
  return true;
}

unsigned int gl_shader::enum_to_gl_const (gl_shader_type type)
{
  switch (type)
    {
    case gl_shader_type::vertex:
      return GL_VERTEX_SHADER;
    case gl_shader_type::fragment:
      return GL_FRAGMENT_SHADER;
    case gl_shader_type::geometry:
      return GL_GEOMETRY_SHADER;
    }
  
  return 0;
}

bool gl_shader::is_ok () const
{
  return m_id;
}

unsigned int gl_shader::gl_id () const
{
  return m_id;
}

std::string gl_shader::read_shader_src (const std::string &path_to_shader)
{
  FILE *fin = fopen (path_to_shader.c_str (), "r");
  
  if (!fin)
    return {};
  
  char buf[1024];
  buf[0] = 0;
  
  std::string retval;
  
  while (auto bytes_read = static_cast<int> (fread (buf, 1, 1023, fin)))
    {
      retval.append (buf, bytes_read);
      
      if (bytes_read < 1023)
        break;
    }
  
  fclose (fin);
  return retval;
}

bool gl_shader::register_shader ()
{
  m_id = glCreateShader (enum_to_gl_const (m_type.value ()));
  
  if (!m_id)
    gl_logger.log_error ("Unable to create shader");
  
  return m_id;
}
