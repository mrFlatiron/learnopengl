#ifndef ERROR_CHECK_H
#define ERROR_CHECK_H

#include "kernel/logging/stdout_logger.h"

extern stdout_logger gl_logger;

std::optional<std::string> get_gl_error (const char *reason);
bool get_gl_error (const char *reason, std::string &out);
bool gl_error_happened ();


#endif // ERROR_CHECK_H
