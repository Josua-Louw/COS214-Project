#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm.h>
#include <vector>

class GUISystemHandler;

enum class addPlantState {
    NONE,
    PLANT,
    POT,
    SEED,
    DECORATION
};

enum class registerStaffState {
    NONE,
    PLANT_CARETAKER,
    SALES_MANAGER
};

enum class processOrderState {
    NONE,
    CUSTOMER_ORDER,
    SELF_ORDER
};

class Window : public Gtk::Window {
public:

  
  Window(GUISystemHandler* guiSystem);
  virtual ~Window();
  
  void updateStatus(const std::string& message);
  void clearMainArea();

  addPlantState   getAddPlantState()      const { return m_add_plant_state; }
  registerStaffState getRegisterStaffState() const { return m_register_staff_state; }
  processOrderState  getProcessOrderState()  const { return m_process_order_state; }

  std::vector<OrderBuilder*>& getOrderBuilders() { return m_order_builders; }


protected:

  addPlantState      m_add_plant_state      = addPlantState::NONE;
  registerStaffState m_register_staff_state = registerStaffState::NONE;
  processOrderState  m_process_order_state  = processOrderState::NONE;

  // For admin orders
  std::vector<OrderBuilder*> m_order_builders;

  void setupLayout();
  void showMainMenu();
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

  // Main layout - using pointers since VBox/HBox need proper initialization
  Gtk::VBox* m_main_box;
  Gtk::HBox* m_header_box;
  Gtk::VBox* m_content_box;
  Gtk::HBox* m_footer_box;

  // Header widgets - using pointers for consistency
  Gtk::Label* m_title_label;
  Gtk::Button* m_main_menu_btn;
  Gtk::Button* m_plant_mgmt_btn;
  Gtk::Button* m_staff_mgmt_btn;
  Gtk::Button* m_order_btn;
  Gtk::Button* m_greenhouse_btn;

  // Content area (will be dynamically updated)
  Gtk::Widget* m_current_content;

  // Footer - using pointer
  Gtk::Label* m_status_label;
};

#endif // WINDOW_H