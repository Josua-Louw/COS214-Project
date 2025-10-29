#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm.h>

class GUISystemHandler;

class Window : public Gtk::Window {
public:
  Window(GUISystemHandler* guiSystem);
protected:
  void on_button_click();
  Gtk::Button m_button;
  GUISystemHandler* m_gui_system_handler;
};

#endif // WINDOW_H