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

include (config/config_compilation.hack)

INCLUDEPATH += src

DISTFILES += \
    src/shaders/frag_shader.fs \
    src/shaders/vertex_shader.vs \
    config/config_compilation.hack

HEADERS += \
    src/3rd_party/stb_image.h \
    src/gl_utils/gl_headers.h \
    src/gl_utils/gl_polar_camera.h \
    src/gl_utils/gl_shader.h \
    src/gl_utils/gl_shader_program.h \
    src/gl_utils/gl_texture.h \
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
    src/gl_utils/gl_matrix_stacker.h \
    config/app_config.h \
    src/kernel/ECS/entity_fwd.h \
    src/kernel/ECS/entities_container.h \
    src/kernel/ECS/object_bounding_area.h \
    src/kernel/physics/velocity.h \
    src/kernel/physics/rotation.h \
    src/kernel/physics/mass_center.h \
    src/kernel/physics/primitives_3d.h \
    src/kernel/physics/impact_result.h \
    src/kernel/physics/collisions.h \
    src/kernel/math/math.h \
    src/kernel/ECS/physical_props.h

SOURCES += \
    src/3rd_party/stb_image_impl.cpp \
    src/gl_utils/gl_polar_camera.cpp \
    src/gl_utils/gl_shader.cpp \
    src/gl_utils/gl_shader_program.cpp \
    src/gl_utils/gl_texture.cpp \
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
    src/gl_utils/gl_matrix_stacker.cpp \
    src/kernel/ECS/entities_container.cpp \
    src/kernel/ECS/object_bounding_area.cpp \
    src/kernel/physics/velocity.cpp \
    src/kernel/physics/rotation.cpp \
    src/kernel/physics/mass_center.cpp \
    src/kernel/physics/primitives_3d.cpp \
    src/kernel/physics/impact_result.cpp \
    src/kernel/physics/collisions.cpp \
    src/kernel/ECS/physical_props.cpp



