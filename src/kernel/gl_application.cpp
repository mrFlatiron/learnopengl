#include "gl_application.h"
#include "gl_utils/gl_headers.h"
#include "gl_utils/error_check.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#include "gl_main_window.h"
#include "gold/utils.h"

gl_application::gl_application (int argc, char *argv[])
{
  FIX_UNUSED (argc, argv);

  m_init_ok = init_everything ();

  if (!m_init_ok)
    {
      gl_logger.log_error ("Initialization failed. Aborting startup");
      return;
    }

}

gl_application::~gl_application ()
{

}

void gl_application::run ()
{
  while (!m_main_window->can_be_closed ())
    {
      m_start_iteration_tp = m_steady_clock.now ();

      process_input ();

      if (m_main_window->can_be_closed ())
        return;

      render ();
    }
}

bool gl_application::init_everything ()
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      gl_logger.log_error ("SDL was not initialized");
      return false;
    };



  put_in (m_main_window, false, m_ideal_frame_time);


  if (!m_main_window->gl_context ())
    return false;



  return true;
}

std::chrono::milliseconds gl_application::ideal_frame_time () const
{
  return m_ideal_frame_time;
}

void gl_application::process_input ()
{
  SDL_Event event;
//  auto start_event_handle_tp = m_steady_clock.now ();

  while (auto events_count = SDL_PollEvent (&event))
    {
      if (events_count > 0)
        {
          m_main_window->process_event (event, m_delta_time);
        }
    }

//  m_delta_time += chr::duration_cast<chr::milliseconds> (m_steady_clock.now () - start_event_handle_tp);
}

void gl_application::render ()
{
  auto render_start = m_steady_clock.now ();

  if (m_limit_frame_rate && m_delta_time < m_ideal_frame_time)
    {
      m_delta_time += m_steady_clock.now () - m_start_iteration_tp;
      return;
    }

  m_main_window->render (m_delta_time);
  m_delta_time = m_steady_clock.now () - render_start;

}
