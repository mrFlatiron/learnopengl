#ifndef GL_APPLICATION_H
#define GL_APPLICATION_H

class gl_main_window;

class gl_application
{
public:
  gl_application (int argc, char *argv[]);
  ~gl_application ();

  void run ();
private:
  bool init_everything ();

  unique_ptr<gl_main_window> m_main_window;
  bool m_init_ok = false;
  bool m_exit_required = false;

  chr::milliseconds m_ideal_frame_time {16};

  chr::nanoseconds  m_delta_time;
  chr::time_point<chr::steady_clock, chr::nanoseconds> m_start_iteration_tp;
  chr::steady_clock m_steady_clock;

  chr::milliseconds ideal_frame_time () const;

  void process_input ();
  void render ();
};

#endif // GL_APPLICATION_H
