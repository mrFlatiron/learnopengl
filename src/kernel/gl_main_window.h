#ifndef GL_MAIN_WINDOW_H
#define GL_MAIN_WINDOW_H

#include <SDL2/SDL.h>
#include "gl_utils/gl_textures_fwd.h"
#include <glm/fwd.hpp>

class gl_application;
class gl_polar_camera;
class gl_textures_manager;
class gl_array_object;
class gl_shader;
class gl_shader_program;
class gl_scene_handler;


class gl_main_window
{
  friend class gl_application;
public:
  gl_main_window (bool limiting_framerate, chr::milliseconds frame_time = chr::milliseconds {17});
  ~gl_main_window ();

  bool can_be_closed () const;
  void process_event (const SDL_Event &native_event, chr::nanoseconds delta_time);
  bool render (std::chrono::nanoseconds delta_time);
private:
  SDL_Window *m_native_handle = nullptr;
  SDL_GLContext m_gl_context = nullptr;

  int m_screen_width = 1200;
  int m_screen_height = 800;
  bool m_limiting_framerate = false;
  chr::milliseconds m_frame_time;

  float m_mouse_sensetivity = 0.01;
  float m_speed_sec = 5;

  bool m_can_be_closed = false;
  bool m_w_pressed = false;
  bool m_s_pressed = false;
  bool m_a_pressed = false;
  bool m_d_pressed = false;

  float m_delta_phi = 0;
  float m_delta_psi = 0;

  unique_ptr<gl_polar_camera> m_camera;
  unique_ptr<gl_textures_manager> m_tex_manager;
  unique_ptr<gl_shader> m_vertex_shader;
  unique_ptr<gl_shader> m_fragment_shader;
  unique_ptr<gl_shader_program> m_shader_program;
  unique_ptr<gl_array_object> m_cube;
  unique_ptr<gl_scene_handler> m_scene;

  unsigned int m_face_tex_loc = 0;
  unsigned int m_container_tex_loc = 0;
  unsigned int m_matrix_loc = 0;
  unsigned int m_color_loc = 0;

  vector<glm::vec3> m_cube_positions;


  SDL_GLContext gl_context();
  bool load_resources ();
};

#endif // GL_MAIN_WINDOW_H
