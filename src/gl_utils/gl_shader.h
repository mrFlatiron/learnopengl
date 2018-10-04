#ifndef GL_SHADER_H
#define GL_SHADER_H

#include <string>
#include <optional>

enum class gl_shader_type
{
  vertex,
  fragment,
  geometry,
};

class gl_shader
{
public:
  gl_shader ();
  ~gl_shader ();

  gl_shader (gl_shader &&rhs);
  gl_shader &operator= (gl_shader &&rhs);

  gl_shader (const gl_shader &rhs) = delete;
  gl_shader &operator= (const gl_shader &rhs) = delete;

  gl_shader (std::string &&src, gl_shader_type type);

  void set_src (std::string &&src);
  void set_type (gl_shader_type type);

  bool compile ();
  
  
  bool is_ok () const;
  unsigned int gl_id () const;
  
  static std::string read_shader_src (const std::string &path_to_shader);
private:
  std::string m_src;
  unsigned int m_id = 0;
  std::optional<gl_shader_type> m_type;
private:
  bool register_shader ();
  static unsigned int enum_to_gl_const (gl_shader_type type);
};

#endif // GL_SHADER_H
