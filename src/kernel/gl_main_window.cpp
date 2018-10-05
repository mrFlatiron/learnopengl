#include "gl_main_window.h"
#include "gl_utils/error_check.h"
#include "gl_utils/gl_headers.h"

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_opengl.h>

#include "gl_utils/gl_polar_camera.h"
#include "gl_utils/gl_array_object.h"
#include "gl_utils/gl_shader.h"
#include "gl_utils/gl_shader_program.h"
#include "gl_utils/gl_textures_manager.h"
#include "gl_utils/gl_texture.h"
#include "gl_utils/gl_texture_filtering.h"
#include "gl_utils/gl_scene_handler.h"
//#include "gl_utils/gl_scene_model_guard.h"
#include "gl_utils/gl_matrix_stacker.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "3rd_party/stb_image.h"

#include "gold/utils.h"

using std::literals::operator""s;

constexpr const char *src_path = "/home/yozhek/learnopengl/src/";
constexpr const char *res_path = "/home/yozhek/learnopengl/resources/";

gl_main_window::gl_main_window (bool limiting_framerate, chr::milliseconds frame_time)
  : m_frame_time (frame_time)
{
  m_limiting_framerate = limiting_framerate;

  m_native_handle = SDL_CreateWindow ("LearnOpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screen_width, m_screen_height,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);


  if (!m_native_handle)
    {
      gl_logger.log_error ("Failed to create main window");
      m_can_be_closed = true;
      return;
    }

  SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK,
                       SDL_GL_CONTEXT_PROFILE_CORE );

  SDL_SetRelativeMouseMode (SDL_TRUE);

  m_gl_context = SDL_GL_CreateContext (m_native_handle);

  if (!m_gl_context)
    {
      gl_logger.log_error ("Failed to create gl context");
      m_can_be_closed = true;
      return;
    }

  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if( glewError != GLEW_OK )
    {
      gl_logger.log_error ( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
      m_can_be_closed = true;
      return;
    }


  glEnable (GL_DEPTH_TEST);

  if (gl_error_happened ())
    {
      gl_logger.log_error ("Failed to glEnable (GL_DEPTH_TEST)");
      m_can_be_closed = true;
      return;
    }


  if (!load_resources ())
    {
      m_can_be_closed = true;
      return;
    }

  put_in (m_camera);
  put_in (m_scene);

  m_scene->projection_matrix () = glm::perspective (static_cast<float> (M_PI / 4), static_cast<float> (m_screen_width) / m_screen_height, 0.1f, 100.0f);

  m_cube_positions =
  {
    glm::vec3 (-5, -5, -5),
    glm::vec3 (5, -5, -5),
    glm::vec3 (-5, 5, -5),
    glm::vec3 (-5, -5 , 5),
    glm::vec3 (-5, 5, 5),
    glm::vec3 (5, -5, 5),
    glm::vec3 (5, 5, -5),
    glm::vec3 (5, 5, 5)
  };

  return;
}

gl_main_window::~gl_main_window ()
{
  if (m_gl_context)
    SDL_GL_DeleteContext (m_gl_context);

  if (m_native_handle)
    SDL_DestroyWindow (m_native_handle);
}

bool gl_main_window::can_be_closed () const
{
  return m_can_be_closed;
}

void gl_main_window::process_event (const SDL_Event &native_event, std::chrono::nanoseconds delta_time)
{
  FIX_UNUSED (delta_time);

  if (native_event.type == SDL_QUIT)
    m_can_be_closed = true;

  if (native_event.type == SDL_WINDOWEVENT)
    {
      if (native_event.window.type == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
          glViewport (0, 0, native_event.window.data1, native_event.window.data2);
          m_screen_width = native_event.window.data1;
          m_screen_height = native_event.window.data2;
        }
    }

  if (native_event.type == SDL_KEYDOWN)
    {

      if (native_event.key.keysym.scancode == SDL_SCANCODE_S)
        m_s_pressed = true;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_W)
        m_w_pressed = true;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_A)
        m_a_pressed = true;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_D)
        m_d_pressed = true;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_Z)
        m_camera->to_init_state ();

    }

  if (native_event.type == SDL_KEYUP)
    {
      if (native_event.key.keysym.scancode == SDL_SCANCODE_S)
        m_s_pressed = false;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_W)
        m_w_pressed = false;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_A)
        m_a_pressed = false;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_D)
        m_d_pressed = false;

      if (native_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        m_can_be_closed = true;

    }

  if (native_event.type == SDL_MOUSEMOTION)
    {
      m_delta_phi += m_mouse_sensetivity * native_event.motion.xrel;
      m_delta_psi += m_mouse_sensetivity * native_event.motion.yrel;
    }


}

void gl_main_window::render (chr::nanoseconds delta_time)
{
  constexpr auto millisecond_div_second = static_cast<float> (1)  / chr::milliseconds::period::den;

  float move_val = millisecond_div_second * chr::duration_cast<chr::milliseconds> (delta_time).count () * m_speed_sec;

  bool effective_w = m_w_pressed && (!m_s_pressed);
  bool effective_s = m_s_pressed && (!m_w_pressed);
  bool effective_a = m_a_pressed && (!m_d_pressed);
  bool effective_d = m_d_pressed && (!m_a_pressed);

  if (effective_w && effective_a)
    {
      move_val *= M_SQRT1_2;
      m_camera->move_forward (move_val);
      m_camera->move_left (move_val);
    }
  if (effective_w && effective_d)
    {
      move_val *= M_SQRT1_2;
      m_camera->move_forward (move_val);
      m_camera->move_right (move_val);
    }
  if (effective_s && effective_a)
    {
      move_val *= M_SQRT1_2;
      m_camera->move_backward (move_val);
      m_camera->move_left (move_val);
    }
  if (effective_s && effective_d)
    {
      move_val *= M_SQRT1_2;
      m_camera->move_backward (move_val);
      m_camera->move_right (move_val);
    }

  if (effective_w && (!effective_a && !effective_d))
    m_camera->move_forward (move_val);

  if (effective_a && (!effective_w && !effective_s))
    m_camera->move_left (move_val);

  if (effective_s && (!effective_a && !effective_d))
    m_camera->move_backward (move_val);

  if (effective_d && (!effective_w && !effective_s))
    m_camera->move_right (move_val);


  m_camera->rotate (-m_delta_phi, -m_delta_psi);
  m_delta_phi = 0;
  m_delta_psi = 0;

  m_scene->view_matrix () = m_camera->matrix ();

  m_shader_program->use ();

  glClearColor (1, 1, 1, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  {
    gl_matrix_stacker stack (m_scene->model_matrix ());

    stack.mult_left (glm::scale (glm::mat4 (1), glm::vec3 (2, 2, 2)));

    m_shader_program->set_uniform (m_matrix_loc, m_scene->result_matrix ());
    m_shader_program->set_uniform (m_color_loc, vector<float> {1.0f, 1.0f, 1.0f});

    glDrawArrays (GL_TRIANGLES, 0, m_cube->layout ().vertex_count);
  }

  {
    gl_matrix_stacker stack (m_scene->model_matrix ());

    stack.
        mult_left (glm::scale (glm::mat4 (1), glm::vec3 (1.0f / 5, 1.0f / 5, 1.0f / 5))).
        mult_left (glm::translate (glm::mat4 (1.0f), glm::vec3 (-1.0f, -1.0f, -1.0f)));

    m_shader_program->set_uniform (m_matrix_loc, m_scene->result_matrix ());
    m_shader_program->set_uniform (m_color_loc,  vector<float> {0.0f, 0.0f, 0.0f});
    glDrawArrays (GL_TRIANGLES, 0, m_cube->layout ().vertex_count);
  }


  {
    gl_matrix_stacker stack (m_scene->model_matrix ());

    stack.
        mult_left (glm::scale (glm::mat4 (1), glm::vec3 (1.0f / 5, 1.0f / 5, 1.0f / 5))).
        mult_left (glm::translate (glm::mat4 (1.0f), glm::vec3 (1.0f, -1.0f, -1.0f)));

    m_shader_program->set_uniform (m_matrix_loc, m_scene->result_matrix ());
    m_shader_program->set_uniform (m_color_loc,  vector<float> {1.0f, 0.0f, 0.0f});
    glDrawArrays (GL_TRIANGLES, 0, m_cube->layout ().vertex_count);
  }


  {
    gl_matrix_stacker stack (m_scene->model_matrix ());

    stack.
        mult_left (glm::scale (glm::mat4 (1), glm::vec3 (1.0f / 5, 1.0f / 5, 1.0f / 5))).
        mult_left (glm::translate (glm::mat4 (1.0f), glm::vec3 (-1.0f, 1.0f, -1.0f)));

    m_shader_program->set_uniform (m_matrix_loc, m_scene->result_matrix ());
    m_shader_program->set_uniform (m_color_loc,  vector<float> {0, 1, 0});
    glDrawArrays (GL_TRIANGLES, 0, m_cube->layout ().vertex_count);
  }

  {
    gl_matrix_stacker stack (m_scene->model_matrix ());

    stack.
        mult_left (glm::scale (glm::mat4 (1), glm::vec3 (1.0f / 5, 1.0f / 5, 1.0f / 5))).
        mult_left (glm::translate (glm::mat4 (1.0f), glm::vec3 (-1.0f, -1.0f, 1.0f)));

    m_shader_program->set_uniform (m_matrix_loc, m_scene->result_matrix ());
    m_shader_program->set_uniform (m_color_loc,  vector<float> {0, 0, 1});
    glDrawArrays (GL_TRIANGLES, 0, m_cube->layout ().vertex_count);
  }

  m_shader_program->set_uniform (m_color_loc,  vector<float> {1, 1, 1});

  for (int i = 0; i < 8; i++)
    {
      gl_matrix_stacker stack (m_scene->model_matrix ());
      stack.mult_left (glm::translate (glm::mat4 (1.0f), m_cube_positions[i]));

      m_shader_program->set_uniform (m_matrix_loc, m_scene->result_matrix ());
      glDrawArrays (GL_TRIANGLES, 0, m_cube->layout ().vertex_count);
    }

  SDL_GL_SwapWindow (m_native_handle);
}

SDL_GLContext gl_main_window::gl_context ()
{
  return m_gl_context;
}

bool gl_main_window::load_resources ()
{
  put_in (m_vertex_shader, gl_shader::read_shader_src (src_path + "shaders/vertex_shader.vs"s),
                                  gl_shader_type::vertex);

  put_in (m_fragment_shader, gl_shader::read_shader_src (src_path + "shaders/frag_shader.fs"s),
                                    gl_shader_type::fragment);

  if (!m_vertex_shader->is_ok ())
    return false;

  if (!m_fragment_shader->is_ok ())
    return false;

  put_in (m_shader_program);

  if (!m_shader_program->attach_shader (*m_vertex_shader))
    return false;

  if (!m_shader_program->attach_shader (*m_fragment_shader))
    return false;

  if (!m_shader_program->link ())
    return false;

  if (!m_shader_program->use ())
    return false;

  put_in (m_cube, gl_array_object::make_textured_cube ());
  m_cube->send_to_gpu (GL_STATIC_DRAW);


  int x, y, channels;
  auto container_data = stbi_load ((res_path + "container.jpg"s).c_str (), &x, &y, &channels, 0);
  if (!container_data)
    {
      fprintf (stderr, "Image is not loaded\n");
      return 0;
    }

  put_in (m_tex_manager);

  auto cont_tex_id = m_tex_manager->create_texture ();
  if (!cont_tex_id.is_valid ())
    return 0;

  m_tex_manager->set_wrap_method (cont_tex_id, gl_texture_wrap_direction::left_right, gl_texture_wrap_method::repeat);
  m_tex_manager->set_wrap_method (cont_tex_id, gl_texture_wrap_direction::top_bottom, gl_texture_wrap_method::repeat);

  gl_texture_filtering filter;

  filter.use_mipmaps = true;
  filter.mipmap_method = gl_texture_filter_method::linear;
  filter.pixel_method = gl_texture_filter_method::linear;

  m_tex_manager->set_filtering_method (cont_tex_id, gl_texture_filter_type::minification, filter);

  filter.use_mipmaps = false;
  m_tex_manager->set_filtering_method (cont_tex_id, gl_texture_filter_type::magnification, filter);

  m_tex_manager->set_tex_data (cont_tex_id, GL_RGB, GL_RGB, x, y, container_data);
  m_tex_manager->generate_mipmap (cont_tex_id);

  stbi_image_free(container_data);

  auto face_data = stbi_load ((res_path + "awesomeface.png"s).c_str (), &x, &y, &channels, 0);
  if (!face_data)
    {
      fprintf (stderr, "Image is not loaded\n");
      return 0;
    }

  auto face_tex_id = m_tex_manager->create_texture ();

  filter.use_mipmaps = true;
  filter.mipmap_method = gl_texture_filter_method::linear;
  filter.pixel_method = gl_texture_filter_method::linear;

  m_tex_manager->set_filtering_method (face_tex_id, gl_texture_filter_type::minification, filter);

  filter.use_mipmaps = false;
  m_tex_manager->set_filtering_method (face_tex_id, gl_texture_filter_type::magnification, filter);

  m_tex_manager->set_tex_data (face_tex_id, GL_RGB, GL_RGBA, x, y, face_data);
  m_tex_manager->generate_mipmap (face_tex_id);


  stbi_image_free (face_data);

  m_shader_program->use ();

  m_tex_manager->activate_texture (0, cont_tex_id);
  m_tex_manager->activate_texture (1, face_tex_id);

  auto text0_loc = m_shader_program->uniform_location ("texture0");
  auto text1_loc = m_shader_program->uniform_location ("texture1");

  m_shader_program->set_uniform (text0_loc, 0);
  m_shader_program->set_uniform (text1_loc, 1);

  m_matrix_loc = m_shader_program->uniform_location ("matrix");
  m_color_loc = m_shader_program->uniform_location ("color");

  return true;
}
