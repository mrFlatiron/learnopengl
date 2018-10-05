#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/*
 * If you are compiling this and you are not me, you will probably want to
 * change variables below. Append '/' to paths, please.
 */


namespace app_config
{
#ifdef MR_FLATIRON
constexpr const char *SRC_PATH = "/home/yozhek/learnopengl/src/";
constexpr const char *RESOURCES_PATH = "/home/yozhek/learnopengl/resources/";
#else
static_assert (false, "Define your own paths here and move this assert below them. "
               "Guard it with your new macro. Write a following line to config_compilation.hack"
               "QMAKE_CXXFLAGS += -DYOUR_GUARD_MACRO");
constexpr const char *SRC_PATH = "";
constexpr const char *RESOURCES_PATH = "";
#endif
}

#endif // APP_CONFIG_H
