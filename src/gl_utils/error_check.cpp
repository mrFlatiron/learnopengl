#include "error_check.h"
#include "gl_headers.h"

stdout_logger gl_logger (true);

std::optional<std::string> get_gl_error (const char *reason)
{
  auto error = glGetError ();
  if (error == GL_NO_ERROR)
    return std::nullopt;

  return std::string (reason);
}

bool get_gl_error (const char *reason, std::string &out)
{
  auto error = glGetError ();
  if (error == GL_NO_ERROR)
    return false;

  out = reason;
  return true;
}

bool gl_error_happened ()
{
  auto error = glGetError ();
  ASSERT_RETURN (error == GL_NO_ERROR, true);
  return false;
}
