#include "gl_shader_program.h"
#include "gl_shader.h"
#include "gl_headers.h"

#include "error_check.h"
#include "glm/gtc/type_ptr.hpp"

using std::literals::operator""s;

gl_shader_program::gl_shader_program ()
{
  
}

gl_shader_program::~gl_shader_program ()
{
  if (m_id)
    glDeleteProgram (m_id);
}

gl_shader_program &gl_shader_program::operator= (gl_shader_program &&rhs)
{
  m_id = rhs.m_id;
  
  rhs.m_id = 0;
  
  return *this;
}

gl_shader_program::gl_shader_program (gl_shader_program &&rhs)
{
  m_id = rhs.m_id;
  
  rhs.m_id = 0;
}

bool gl_shader_program::attach_shader (const gl_shader &shader)
{
  if (!m_id)
    m_id = glCreateProgram ();
  
  if (!m_id)
    {
      gl_logger.log_error ("Failed to create a program during first shader attachment");
      return false;
    }
  
  if (!shader.is_ok ())
    {
      gl_logger.log_error ("Shader is not valid");
      return false;
    }
  
  glAttachShader (m_id, shader.gl_id ());
  
  if (gl_error_happened ())
    {
      gl_logger.log_error ("Error while attaching a shader");
      return false;
    }
  
  return true;
}

bool gl_shader_program::link ()
{
  glLinkProgram (m_id);

  int  success;
  char info_log[512];

  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  
  if (!success)
    {
      glGetProgramInfoLog(m_id, 512, NULL, info_log);
      gl_logger.log_error ("Linking failed. Error: %s", info_log);
      return false;
    }
  
  return true;
}

bool gl_shader_program::use ()
{
  glUseProgram (gl_id ());

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUseProgram");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, float val)
{
  glUniform1f (var_location, val);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, int val)
{
  glUniform1i (var_location, val);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const glm::vec2 &val)
{
  glUniform2fv (var_location, 2, glm::value_ptr (val));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const std::vector<int> &val)
{
  if (val.empty ())
    return false;

  if (val.size () == 1u)
    return set_uniform (var_location, val[0]);

  if (val.size () == 2u)
    glUniform2iv (var_location, 1, val.data ());

  if (val.size () == 3u)
    glUniform3iv (var_location, 1, val.data ());

  if (val.size () == 4u)
    glUniform4iv (var_location, 1, val.data ());

  if (val.size () >= 5u)
    {
      gl_logger.log_error ("Wrong value passed to a uniform");
      return false;
    }

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const std::vector<float> &val)
{
  if (val.empty ())
    return false;

  if (val.size () == 1u)
    return set_uniform (var_location, val[0]);

  if (val.size () == 2u)
    glUniform2fv (var_location, 1, val.data ());

  if (val.size () == 3u)
    glUniform3fv (var_location, 1, val.data ());

  if (val.size () == 4u)
    glUniform4fv (var_location, 1, val.data ());

  if (val.size () >= 5u)
    {
      gl_logger.log_error ("Wrong value passed to a uniform");
      return false;
    }

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const glm::vec3 &val)
{
  glUniform3fv (var_location, 3, glm::value_ptr (val));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const glm::vec4 &val)
{
  glUniform4fv (var_location, 1, glm::value_ptr (val));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const glm::mat2 &val)
{
  glUniformMatrix2fv (var_location, 1, GL_FALSE, glm::value_ptr (val));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const glm::mat3 &val)
{
  glUniformMatrix3fv (var_location, 1, GL_FALSE, glm::value_ptr (val));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

bool gl_shader_program::set_uniform (int var_location, const glm::mat4 &val)
{
  glUniformMatrix4fv (var_location, 1, GL_FALSE, glm::value_ptr (val));

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glUniform*");
      return false;
    }

  return true;
}

unsigned int gl_shader_program::gl_id () const
{
  return m_id;
}

int gl_shader_program::uniform_location (const std::string &var_name)
{
  auto retval = glGetUniformLocation (gl_id (), var_name.c_str ());

  if (retval == -1)
    gl_logger.log_error ("Failed to glGetUniformLocation");

  return retval;
}
