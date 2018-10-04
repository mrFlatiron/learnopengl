#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#ifndef DEBUG_TRIG_LIMIT
#define DEBUG_TRIG_LIMIT 3
#endif

#ifdef __GNUC__

  #include <csignal>

  #ifdef DEBUG
    #define DEBUG_PAUSE(reason) {static int DEBUG_triggered = 0; \
  DEBUG_triggered++; \
  if (DEBUG_triggered <= DEBUG_TRIG_LIMIT) std::raise (SIGTRAP);}
  #else
    #define DEBUG_PAUSE(reason)
  #endif

#else

  #ifdef __WIN32__
    #ifdef DEBUG
      #define DEBUG_PAUSE(reason) (__debugbreak ());
    #else
      #define DEBUG_PAUSE(reason)
    #endif

  #else

    #define DEBUG_PAUSE(reason)

  #endif //__WIN32__

#endif //__GNUC>__

#define DEBUG_ASSERT(assertion) if (!(assertion)) DEBUG_PAUSE ("");
#define ASSERT_RETURN(assertion, retval) if (!(assertion)) {DEBUG_PAUSE (""); return retval;}

#endif // DEBUG_UTILS_H
