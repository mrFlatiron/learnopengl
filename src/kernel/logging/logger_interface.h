#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include <cstdarg>


enum class log_severity
{
  info,
  warn,
  error,
};

class logger_interface
{
public:
  logger_interface ();
  virtual ~logger_interface ();

  void log_error (const char *format, ...);
  void log_warning (const char *format, ...);
  void log_message (const char *format, ...);

protected:
  virtual void log_string_impl (log_severity, const std::string &str) = 0;
  virtual std::string log_severity_prefix (log_severity sev) const;
private:
  static std::string variadic_to_string (const char *format, va_list args);
  void log_string_with_severity (log_severity sev, const char *format, va_list args);
};

#endif // LOGGER_INTERFACE_H
