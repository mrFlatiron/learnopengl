TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += precompile_header

PRECOMPILED_HEADER = src/precompiled/precompiled_header.h

LIBS += -lSDL2
LIBS += -lGLEW
LIBS += -lGL
QMAKE_CXXFLAGS_DEBUG += -DDEBUG
QMAKE_CXXFLAGS += -Wall -Werror -std=c++17

INCLUDEPATH += src

DISTFILES += \
    src/shaders/frag_shader.fs \
    src/shaders/vertex_shader.vs

HEADERS += \
    src/3rd_party/stb_image.h \
    src/gl_utils/gl_camera.h \
    src/gl_utils/gl_headers.h \
    src/gl_utils/gl_polar_camera.h \
    src/gl_utils/gl_shader.h \
    src/gl_utils/gl_shader_program.h \
    src/gl_utils/gl_texture.h \
    src/gl_utils/gl_textures_container.h \
    src/gold/enum/containers/enum_bitset.h \
    src/gold/enum/containers/enum_vector.h \
    src/gold/enum/enum_helper.h \
    src/gold/enum/enum_misc.h \
    src/gold/enum/enum_range.h \
    src/gold/debug_utils.h \
    src/gold/range_utils.h \
    src/gold/typesafe_id.h \
    src/gold/utils.h \
    src/precompiled/precompiled_header.h \
    src/gl_utils/gl_textures_fwd.h \
    src/gl_utils/gl_texture_filtering.h \
    src/gl_utils/gl_textures_manager.h \
    src/gl_utils/gl_array_object.h \
    src/gl_utils/error_check.h \
    src/kernel/gl_application.h \
    src/kernel/logging/logger_interface.h \
    src/kernel/logging/stdout_logger.h \
    src/kernel/logging/dummy_logger.h \
    src/kernel/gl_main_window.h \
    src/gl_utils/gl_scene_handler.h \
    src/gl_utils/gl_scene_model_guard.h \
    src/gl_utils/gl_matrix_stacker.h

SOURCES += \
    src/3rd_party/stb_image_impl.cpp \
    src/gl_utils/gl_camera.cpp \
    src/gl_utils/gl_polar_camera.cpp \
    src/gl_utils/gl_shader.cpp \
    src/gl_utils/gl_shader_program.cpp \
    src/gl_utils/gl_texture.cpp \
    src/gl_utils/gl_textures_container.cpp \
    src/main/main.cpp \
    src/gl_utils/gl_texture_filtering.cpp \
    src/gl_utils/gl_textures_manager.cpp \
    src/gl_utils/gl_array_object.cpp \
    src/gl_utils/error_check.cpp \
    src/kernel/gl_application.cpp \
    src/kernel/logging/logger_interface.cpp \
    src/kernel/logging/stdout_logger.cpp \
    src/kernel/logging/dummy_logger.cpp \
    src/kernel/gl_main_window.cpp \
    src/gl_utils/gl_scene_handler.cpp \
    src/gl_utils/gl_scene_model_guard.cpp \
    src/gl_utils/gl_matrix_stacker.cpp



