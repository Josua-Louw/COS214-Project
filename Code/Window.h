#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm.h>
#include <vector>

class GUISystemHandler;

class Window : public Gtk::Window {
public:
  Window(GUISystemHandler* guiSystem);
  void updateStatus(const std::string& message);
  void clearMainArea();
  Gtk::Box* getMainBox() { return &m_main_box; }

protected:
  void setupMainMenu();
  void setupPlantManagement();
  void setupStaffManagement();
  void setupOrderProcessing();
  void setupGreenhouseView();

  // Signal handlers
  void on_main_menu_clicked();
  void on_plant_management_clicked();
  void on_staff_management_clicked();
  void on_order_processing_clicked();
  void on_greenhouse_view_clicked();

  GUISystemHandler* m_gui_system_handler;
  
  // Main layout
  Gtk::Box m_main_box;
  Gtk::Box m_header_box;
  Gtk::Box m_content_box;
  Gtk::Box m_footer_box;
  
  // Header widgets
  Gtk::Label m_title_label;
  Gtk::Button m_main_menu_btn;
  Gtk::Button m_plant_mgmt_btn;
  Gtk::Button m_staff_mgmt_btn;
  Gtk::Button m_order_btn;
  Gtk::Button m_greenhouse_btn;
  
  // Content area (will be dynamically updated)
  Gtk::Box* m_current_content;
  
  // Footer
  Gtk::Label m_status_label;
};

#endif // WINDOW_H