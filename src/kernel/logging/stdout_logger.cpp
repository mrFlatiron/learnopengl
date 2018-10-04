#include "stdout_logger.h"
#include <cstdio>

stdout_logger::stdout_logger (bool autoflush)
{
  m_autoflush = autoflush;
}

stdout_logger::~stdout_logger ()
{
  fflush (stdout);
}

void stdout_logger::log_string_impl (log_severity, const std::string &msg)
{
  printf ("%s", msg.c_str ());

  if (m_autoflush)
    fflush (stdout);
}
