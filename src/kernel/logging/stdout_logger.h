#ifndef STDOUT_LOGGER_H
#define STDOUT_LOGGER_H

#include "logger_interface.h"

class stdout_logger : public logger_interface
{
public:
  stdout_logger (bool autoflush = false);
  ~stdout_logger ();
private:
  void log_string_impl (log_severity, const std::string &msg) override;

  bool m_autoflush = false;
};

#endif // STDOUT_LOGGER_H
