#include "logger_interface.h"



logger_interface::logger_interface ()
{

}

logger_interface::~logger_interface ()
{

}

void logger_interface::log_error (const char *format, ...)
{
  va_list args;
  va_start (args, format);

  log_string_with_severity (log_severity::error, format, args);

  va_end (args);
}

void logger_interface::log_warning (const char *format, ...)
{
  va_list args;
  va_start (args, format);

  log_string_with_severity (log_severity::warn, format, args);

  va_end (args);
}

void logger_interface::log_message (const char *format, ...)
{
  va_list args;
  va_start (args, format);

  log_string_with_severity (log_severity::info, format, args);

  va_end (args);
}

std::string logger_interface::log_severity_prefix (log_severity sev) const
{
  switch (sev)
    {
    case log_severity::info:
      return "[INFO ]:";
    case log_severity::warn:
      return "[WARN ]:";
    case log_severity::error:
      return "[ERROR]:";
    }

  ASSERT_RETURN (false, "");
}

std::string logger_interface::variadic_to_string (const char *format, va_list args)
{
  constexpr int initial_buf_size = 1024;
  constexpr int max_buf = 64 * initial_buf_size;

  std::string retval (initial_buf_size, 0);

  auto need_space = vsnprintf (retval.data (), initial_buf_size, format, args);

  if (need_space < initial_buf_size)
    return retval;

  ASSERT_RETURN (need_space < max_buf, "INTERNAL LOGGER ERROR: LOG MESSAGE IS TOO LONG");

  retval.resize (need_space + 1);

  vsnprintf (retval.data (), need_space + 1, format, args);

  return retval;
}

void logger_interface::log_string_with_severity (log_severity sev, const char *format, va_list args)
{
  std::string message = log_severity_prefix (sev);
  message += " ";

  message += variadic_to_string (format, args);
  message += "\n";

  log_string_impl (sev, message);
}
