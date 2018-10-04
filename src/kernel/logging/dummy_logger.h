#ifndef DUMMY_LOGGER_H
#define DUMMY_LOGGER_H

#include "logger_interface.h"

class dummy_logger : public logger_interface
{
public:
  dummy_logger () {}

private:
  void log_string_impl (log_severity, const std::string &) override {}
};

#endif // DUMMY_LOGGER_H
