#include "Window.h"
#include "GUISystemHandler.h"
#include <iostream>

Window::Window(GUISystemHandler* guiSystem) 
    : m_gui_system_handler(guiSystem),
      m_main_box(Gtk::Orientation::VERTICAL),
      m_header_box(Gtk::Orientation::HORIZONTAL),
      m_content_box(Gtk::Orientation::VERTICAL),
      m_footer_box(Gtk::Orientation::HORIZONTAL),
      m_title_label("Greenhouse Management System"),
      m_main_menu_btn("Main Menu"),
      m_plant_mgmt_btn("Plant Management"),
      m_staff_mgmt_btn("Staff Management"),
      m_order_btn("Order Processing"),
      m_greenhouse_btn("Greenhouse View"),
      m_status_label("Ready")
{
    set_title("Greenhouse Management System");
    set_default_size(800, 600);
    
    // Setup main layout
    setupMainMenu();
}

void Window::setupMainMenu() {
    // Clear existing content
    clearMainArea();
    
    // Setup header
    m_header_box.set_margin(10);
    m_header_box.set_spacing(10);
    
    m_title_label.set_markup("<span size='x-large' weight='bold'>Greenhouse Management System</span>");
    m_header_box.append(m_title_label);
    m_header_box.append(m_main_menu_btn);
    m_header_box.append(m_plant_mgmt_btn);
    m_header_box.append(m_staff_mgmt_btn);
    m_header_box.append(m_order_btn);
    m_header_box.append(m_greenhouse_btn);
    
    // Setup content area
    m_content_box.set_margin(10);
    m_content_box.set_spacing(10);
    
    // Setup footer
    m_footer_box.set_margin(10);
    m_footer_box.append(m_status_label);
    
    // Assemble main layout
    m_main_box.append(m_header_box);
    m_main_box.append(m_content_box);
    m_main_box.append(m_footer_box);
    set_child(m_main_box);
    
    // Create main menu content
    auto* main_menu_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    main_menu_box->set_spacing(10);
    
    Gtk::Label* welcome_label = Gtk::make_managed<Gtk::Label>();
    welcome_label->set_markup("<span size='large'>Welcome to Greenhouse Management System</span>\n\nPlease select an option from the menu above.");
    welcome_label->set_margin(20);
    main_menu_box->append(*welcome_label);
    
    m_content_box.append(*main_menu_box);
    m_current_content = main_menu_box;
    
    // Connect signals
    m_main_menu_btn.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_main_menu_clicked));
    m_plant_mgmt_btn.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_plant_management_clicked));
    m_staff_mgmt_btn.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_staff_management_clicked));
    m_order_btn.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_order_processing_clicked));
    m_greenhouse_btn.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_greenhouse_view_clicked));
    
    updateStatus("System ready - Main menu displayed");
}

void Window::setupPlantManagement() {
    clearMainArea();
    
    auto* plant_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    plant_box->set_spacing(10);
    
    Gtk::Label* title_label = Gtk::make_managed<Gtk::Label>();
    title_label->set_markup("<span size='large' weight='bold'>Plant Management</span>");
    title_label->set_margin_bottom(20);
    plant_box->append(*title_label);
    
    // Plant type buttons
    Gtk::Button* add_plant_btn = Gtk::make_managed<Gtk::Button>("Add Regular Plant");
    Gtk::Button* add_pot_btn = Gtk::make_managed<Gtk::Button>("Add Pot");
    Gtk::Button* add_seed_btn = Gtk::make_managed<Gtk::Button>("Add Seed Packet");
    Gtk::Button* add_decoration_btn = Gtk::make_managed<Gtk::Button>("Add Decoration");
    
    add_plant_btn->set_size_request(200, 50);
    add_pot_btn->set_size_request(200, 50);
    add_seed_btn->set_size_request(200, 50);
    add_decoration_btn->set_size_request(200, 50);
    
    plant_box->append(*add_plant_btn);
    plant_box->append(*add_pot_btn);
    plant_box->append(*add_seed_btn);
    plant_box->append(*add_decoration_btn);
    
    // Connect signals
    add_plant_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addPlant();
        updateStatus("Regular plant added to greenhouse");
    });
    
    add_pot_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addPot();
        updateStatus("Pot added to greenhouse");
    });
    
    add_seed_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addSeedPacket();
        updateStatus("Seed packet added to greenhouse");
    });
    
    add_decoration_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addDecoration();
        updateStatus("Decoration added to greenhouse");
    });
    
    m_content_box.append(*plant_box);
    m_current_content = plant_box;
    updateStatus("Plant management - Select plant type to add");
}

void Window::setupStaffManagement() {
    clearMainArea();
    
    auto* staff_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    staff_box->set_spacing(10);
    
    Gtk::Label* title_label = Gtk::make_managed<Gtk::Label>();
    title_label->set_markup("<span size='large' weight='bold'>Staff Management</span>");
    title_label->set_margin_bottom(20);
    staff_box->append(*title_label);
    
    // Staff type buttons
    Gtk::Button* add_caretaker_btn = Gtk::make_managed<Gtk::Button>("Register Plant Caretaker");
    Gtk::Button* add_manager_btn = Gtk::make_managed<Gtk::Button>("Register Sales Manager");
    Gtk::Button* assign_care_btn = Gtk::make_managed<Gtk::Button>("Assign Care Task");
    Gtk::Button* assign_sale_btn = Gtk::make_managed<Gtk::Button>("Assign Sale Task");
    
    add_caretaker_btn->set_size_request(250, 50);
    add_manager_btn->set_size_request(250, 50);
    assign_care_btn->set_size_request(250, 50);
    assign_sale_btn->set_size_request(250, 50);
    
    staff_box->append(*add_caretaker_btn);
    staff_box->append(*add_manager_btn);
    staff_box->append(*assign_care_btn);
    staff_box->append(*assign_sale_btn);
    
    // Connect signals
    add_caretaker_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->registerPlantCaretaker();
        updateStatus("Plant caretaker registered");
    });
    
    add_manager_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->registerSalesManager();
        updateStatus("Sales manager registered");
    });
    
    assign_care_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->assignCareTask();
        updateStatus("Care task assigned to staff");
    });
    
    assign_sale_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->assignSaleTask();
        updateStatus("Sale task assigned to staff");
    });
    
    m_content_box.append(*staff_box);
    m_current_content = staff_box;
    updateStatus("Staff management - Select action");
}

void Window::setupOrderProcessing() {
    clearMainArea();
    
    auto* order_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    order_box->set_spacing(10);
    
    Gtk::Label* title_label = Gtk::make_managed<Gtk::Label>();
    title_label->set_markup("<span size='large' weight='bold'>Order Processing</span>");
    title_label->set_margin_bottom(20);
    order_box->append(*title_label);
    
    // Order buttons
    Gtk::Button* create_order_btn = Gtk::make_managed<Gtk::Button>("Create New Order");
    Gtk::Button* add_plant_order_btn = Gtk::make_managed<Gtk::Button>("Add Plant to Order");
    Gtk::Button* add_pot_order_btn = Gtk::make_managed<Gtk::Button>("Add Pot to Order");
    Gtk::Button* add_seed_order_btn = Gtk::make_managed<Gtk::Button>("Add Seeds to Order");
    Gtk::Button* add_decor_order_btn = Gtk::make_managed<Gtk::Button>("Add Decoration to Order");
    Gtk::Button* process_order_btn = Gtk::make_managed<Gtk::Button>("Process Order");
    
    create_order_btn->set_size_request(250, 50);
    add_plant_order_btn->set_size_request(250, 50);
    add_pot_order_btn->set_size_request(250, 50);
    add_seed_order_btn->set_size_request(250, 50);
    add_decor_order_btn->set_size_request(250, 50);
    process_order_btn->set_size_request(250, 50);
    
    order_box->append(*create_order_btn);
    order_box->append(*add_plant_order_btn);
    order_box->append(*add_pot_order_btn);
    order_box->append(*add_seed_order_btn);
    order_box->append(*add_decor_order_btn);
    order_box->append(*process_order_btn);
    
    // Connect signals
    create_order_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->createOrder();
        updateStatus("New order created");
    });
    
    add_plant_order_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addPlantToOrder();
        updateStatus("Plant added to current order");
    });
    
    add_pot_order_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addPotToOrder();
        updateStatus("Pot added to current order");
    });
    
    add_seed_order_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addSeedToOrder();
        updateStatus("Seed packet added to current order");
    });
    
    add_decor_order_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->addDecorationToOrder();
        updateStatus("Decoration added to current order");
    });
    
    process_order_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->processCustomerOrder();
        updateStatus("Order processed successfully");
    });
    
    m_content_box.append(*order_box);
    m_current_content = order_box;
    updateStatus("Order processing - Create and manage customer orders");
}

void Window::setupGreenhouseView() {
    clearMainArea();
    
    auto* greenhouse_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    greenhouse_box->set_spacing(10);
    
    Gtk::Label* title_label = Gtk::make_managed<Gtk::Label>();
    title_label->set_markup("<span size='large' weight='bold'>Greenhouse Overview</span>");
    title_label->set_margin_bottom(20);
    greenhouse_box->append(*title_label);
    
    // Greenhouse action buttons
    Gtk::Button* view_summary_btn = Gtk::make_managed<Gtk::Button>("View Greenhouse Summary");
    Gtk::Button* view_inventory_btn = Gtk::make_managed<Gtk::Button>("View Inventory");
    Gtk::Button* view_staff_btn = Gtk::make_managed<Gtk::Button>("View Staff");
    Gtk::Button* water_plants_btn = Gtk::make_managed<Gtk::Button>("Water All Plants");
    Gtk::Button* fertilize_plants_btn = Gtk::make_managed<Gtk::Button>("Fertilize All Plants");
    
    view_summary_btn->set_size_request(250, 50);
    view_inventory_btn->set_size_request(250, 50);
    view_staff_btn->set_size_request(250, 50);
    water_plants_btn->set_size_request(250, 50);
    fertilize_plants_btn->set_size_request(250, 50);
    
    greenhouse_box->append(*view_summary_btn);
    greenhouse_box->append(*view_inventory_btn);
    greenhouse_box->append(*view_staff_btn);
    greenhouse_box->append(*water_plants_btn);
    greenhouse_box->append(*fertilize_plants_btn);
    
    // Text view for displaying greenhouse information
    Gtk::ScrolledWindow* scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled_window->set_vexpand(true);
    scrolled_window->set_hexpand(true);
    scrolled_window->set_margin(10);
    
    Gtk::TextView* text_view = Gtk::make_managed<Gtk::TextView>();
    text_view->set_editable(false);
    text_view->set_cursor_visible(false);
    scrolled_window->set_child(*text_view);
    greenhouse_box->append(*scrolled_window);
    
    // Connect signals
    view_summary_btn->signal_clicked().connect([this, text_view]() {
        std::string summary = m_gui_system_handler->getGreenhouseSummary();
        auto buffer = text_view->get_buffer();
        buffer->set_text(summary);
        updateStatus("Greenhouse summary displayed");
    });
    
    view_inventory_btn->signal_clicked().connect([this, text_view]() {
        std::string inventory = m_gui_system_handler->getInventory();
        auto buffer = text_view->get_buffer();
        buffer->set_text(inventory);
        updateStatus("Inventory displayed");
    });
    
    view_staff_btn->signal_clicked().connect([this, text_view]() {
        std::string staff = m_gui_system_handler->getStaffInfo();
        auto buffer = text_view->get_buffer();
        buffer->set_text(staff);
        updateStatus("Staff information displayed");
    });
    
    water_plants_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->waterAllPlants();
        updateStatus("All plants watered");
    });
    
    fertilize_plants_btn->signal_clicked().connect([this]() {
        m_gui_system_handler->fertilizeAllPlants();
        updateStatus("All plants fertilized");
    });
    
    m_content_box.append(*greenhouse_box);
    m_current_content = greenhouse_box;
    updateStatus("Greenhouse view - Select action to view or manage greenhouse");
}

void Window::clearMainArea() {
    // Remove all children from content box except the first one (header)
    while (m_content_box.get_first_child() != nullptr) {
        m_content_box.remove(*m_content_box.get_first_child());
    }
}

void Window::updateStatus(const std::string& message) {
    m_status_label.set_text("Status: " + message);
    std::cout << "GUI Status: " << message << std::endl;
}

// Signal handler implementations
void Window::on_main_menu_clicked() {
    setupMainMenu();
}

void Window::on_plant_management_clicked() {
    setupPlantManagement();
}

void Window::on_staff_management_clicked() {
    setupStaffManagement();
}

void Window::on_order_processing_clicked() {
    setupOrderProcessing();
}

void Window::on_greenhouse_view_clicked() {
    setupGreenhouseView();
}