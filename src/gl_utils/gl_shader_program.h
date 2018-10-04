#ifndef GL_SHADER_PROGRAM_H
#define GL_SHADER_PROGRAM_H

#include <string>
#include "glm/fwd.hpp"

class gl_shader;

class gl_shader_program
{
public:
  gl_shader_program ();
  ~gl_shader_program ();
  
  gl_shader_program (const gl_shader_program &rhs) = delete;
  gl_shader_program &operator= (const gl_shader_program &rhs) = delete;
  
  gl_shader_program (gl_shader_program &&rhs);
  gl_shader_program &operator= (gl_shader_program &&rhs);

  bool attach_shader (const gl_shader &shader);
  bool link ();
  bool use ();


//  bool set_uniform (const std::string &var_name, float val);
//  bool set_uniform (const std::string &var_name, int val);

//  bool set_uniform (const std::string &var_name, const glm::vec2 &val);
//  bool set_uniform (const std::string &var_name, const std::vector<int> &val);
//  bool set_uniform (const std::string &var_name, const std::vector<float> &val);

//  bool set_uniform (const std::string &var_name, const glm::vec3 &val);
//  bool set_uniform (const std::string &var_name, const glm::vec4 &val);
//  bool set_uniform (const std::string &var_name, const glm::mat2 &val);
//  bool set_uniform (const std::string &var_name, const glm::mat3 &val);
//  bool set_uniform (const std::string &var_name, const glm::mat4 &val);

  int uniform_location (const std::string &var_name);

  bool set_uniform (int var_location, float val);
  bool set_uniform (int var_location, int val);

  bool set_uniform (int var_location, const glm::vec2 &val);
  bool set_uniform (int var_location, const std::vector<int> &val);
  bool set_uniform (int var_location, const std::vector<float> &val);

  bool set_uniform (int var_location, const glm::vec3 &val);
  bool set_uniform (int var_location, const glm::vec4 &val);
  bool set_uniform (int var_location, const glm::mat2 &val);
  bool set_uniform (int var_location, const glm::mat3 &val);
  bool set_uniform (int var_location, const glm::mat4 &val);

  unsigned int gl_id () const;
private:
  unsigned int m_id = 0;
};

#endif // GL_SHADER_PROGRAM_H
