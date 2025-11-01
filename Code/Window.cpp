#include "Window.h"
#include "GUISystemHandler.h"
#include <iostream>

Window::Window(GUISystemHandler* guiSystem) 
    : m_gui_system_handler(guiSystem),
      m_current_content(nullptr)
{
    set_title("Greenhouse Management System");
    set_default_size(800, 600);
    
    // Create all widgets dynamically
    m_main_box = new Gtk::VBox(false, 5);
    m_header_box = new Gtk::HBox(false, 5);
    m_content_box = new Gtk::VBox(false, 10);
    m_footer_box = new Gtk::HBox(false, 5);
    
    m_title_label = new Gtk::Label("Greenhouse Management System");
    m_main_menu_btn = new Gtk::Button("Main Menu");
    m_plant_mgmt_btn = new Gtk::Button("Plant Management");
    m_staff_mgmt_btn = new Gtk::Button("Staff Management");
    m_order_btn = new Gtk::Button("Order Processing");
    m_greenhouse_btn = new Gtk::Button("Greenhouse View");
    m_status_label = new Gtk::Label("Ready");
    
    // Setup main layout
    setupMainMenu();
}

Window::~Window() {
    // Cleanup is handled by GTK's widget hierarchy
    // Don't delete widgets that have been added to containers
}

void Window::setupMainMenu() {
    // Clear existing content
    clearMainArea();

    // Setup header
    m_header_box->set_spacing(10);
    m_header_box->pack_start(*m_title_label, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_main_menu_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_plant_mgmt_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_staff_mgmt_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_order_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_greenhouse_btn, Gtk::PACK_SHRINK);

    // Setup content area
    m_content_box->set_spacing(10);

    // Setup footer
    m_footer_box->pack_start(*m_status_label, Gtk::PACK_SHRINK);

    // Assemble main layout
    m_main_box->pack_start(*m_header_box, Gtk::PACK_SHRINK);
    m_main_box->pack_start(*m_content_box, Gtk::PACK_EXPAND_WIDGET);
    m_main_box->pack_start(*m_footer_box, Gtk::PACK_SHRINK);

    add(*m_main_box);

    // Create main menu content
    Gtk::VBox* main_menu_box = Gtk::manage(new Gtk::VBox());
    main_menu_box->set_spacing(10);

    Gtk::Label* welcome_label = Gtk::manage(new Gtk::Label());
    welcome_label->set_markup("<span size='large'>Welcome to Greenhouse Management System</span>\n\nPlease select an option from the menu above.");
    welcome_label->set_padding(20, 20);
    main_menu_box->pack_start(*welcome_label, Gtk::PACK_EXPAND_WIDGET);

    m_content_box->pack_start(*main_menu_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = main_menu_box;

    // Connect signals
    m_main_menu_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_main_menu_clicked));
    m_plant_mgmt_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_plant_management_clicked));
    m_staff_mgmt_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_staff_management_clicked));
    m_order_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_order_processing_clicked));
    m_greenhouse_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_greenhouse_view_clicked));

    show_all_children();
    updateStatus("System ready - Main menu displayed");
}

void Window::setupPlantManagement() {
    clearMainArea();

    Gtk::VBox* plant_box = Gtk::manage(new Gtk::VBox());
    plant_box->set_spacing(10);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='large' weight='bold'>Plant Management</span>");
    plant_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    // Plant type buttons
    Gtk::Button* add_plant_btn = Gtk::manage(new Gtk::Button("Add Regular Plant"));
    Gtk::Button* add_pot_btn = Gtk::manage(new Gtk::Button("Add Pot"));
    Gtk::Button* add_seed_btn = Gtk::manage(new Gtk::Button("Add Seed Packet"));
    Gtk::Button* add_decoration_btn = Gtk::manage(new Gtk::Button("Add Decoration"));

    add_plant_btn->set_size_request(200, 50);
    add_pot_btn->set_size_request(200, 50);
    add_seed_btn->set_size_request(200, 50);
    add_decoration_btn->set_size_request(200, 50);

    plant_box->pack_start(*add_plant_btn, Gtk::PACK_SHRINK);
    plant_box->pack_start(*add_pot_btn, Gtk::PACK_SHRINK);
    plant_box->pack_start(*add_seed_btn, Gtk::PACK_SHRINK);
    plant_box->pack_start(*add_decoration_btn, Gtk::PACK_SHRINK);

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

    m_content_box->pack_start(*plant_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = plant_box;

    show_all_children();
    updateStatus("Plant management - Select plant type to add");
}

void Window::setupStaffManagement() {
    clearMainArea();

    Gtk::VBox* staff_box = Gtk::manage(new Gtk::VBox());
    staff_box->set_spacing(10);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='large' weight='bold'>Staff Management</span>");
    staff_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    // Staff type buttons
    Gtk::Button* add_caretaker_btn = Gtk::manage(new Gtk::Button("Register Plant Caretaker"));
    Gtk::Button* add_manager_btn = Gtk::manage(new Gtk::Button("Register Sales Manager"));
    Gtk::Button* assign_care_btn = Gtk::manage(new Gtk::Button("Assign Care Task"));
    Gtk::Button* assign_sale_btn = Gtk::manage(new Gtk::Button("Assign Sale Task"));

    add_caretaker_btn->set_size_request(250, 50);
    add_manager_btn->set_size_request(250, 50);
    assign_care_btn->set_size_request(250, 50);
    assign_sale_btn->set_size_request(250, 50);

    staff_box->pack_start(*add_caretaker_btn, Gtk::PACK_SHRINK);
    staff_box->pack_start(*add_manager_btn, Gtk::PACK_SHRINK);
    staff_box->pack_start(*assign_care_btn, Gtk::PACK_SHRINK);
    staff_box->pack_start(*assign_sale_btn, Gtk::PACK_SHRINK);

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

    m_content_box->pack_start(*staff_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = staff_box;

    show_all_children();
    updateStatus("Staff management - Select action");
}

void Window::setupOrderProcessing() {
    clearMainArea();

    Gtk::VBox* order_box = Gtk::manage(new Gtk::VBox());
    order_box->set_spacing(10);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='large' weight='bold'>Order Processing</span>");
    order_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    // Order buttons
    Gtk::Button* create_order_btn = Gtk::manage(new Gtk::Button("Create New Order"));
    Gtk::Button* add_plant_order_btn = Gtk::manage(new Gtk::Button("Add Plant to Order"));
    Gtk::Button* add_pot_order_btn = Gtk::manage(new Gtk::Button("Add Pot to Order"));
    Gtk::Button* add_seed_order_btn = Gtk::manage(new Gtk::Button("Add Seeds to Order"));
    Gtk::Button* add_decor_order_btn = Gtk::manage(new Gtk::Button("Add Decoration to Order"));
    Gtk::Button* process_order_btn = Gtk::manage(new Gtk::Button("Process Order"));

    create_order_btn->set_size_request(250, 50);
    add_plant_order_btn->set_size_request(250, 50);
    add_pot_order_btn->set_size_request(250, 50);
    add_seed_order_btn->set_size_request(250, 50);
    add_decor_order_btn->set_size_request(250, 50);
    process_order_btn->set_size_request(250, 50);

    order_box->pack_start(*create_order_btn, Gtk::PACK_SHRINK);
    order_box->pack_start(*add_plant_order_btn, Gtk::PACK_SHRINK);
    order_box->pack_start(*add_pot_order_btn, Gtk::PACK_SHRINK);
    order_box->pack_start(*add_seed_order_btn, Gtk::PACK_SHRINK);
    order_box->pack_start(*add_decor_order_btn, Gtk::PACK_SHRINK);
    order_box->pack_start(*process_order_btn, Gtk::PACK_SHRINK);

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

    m_content_box->pack_start(*order_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = order_box;

    show_all_children();
    updateStatus("Order processing - Create and manage customer orders");
}

void Window::setupGreenhouseView() {
    clearMainArea();

    Gtk::VBox* greenhouse_box = Gtk::manage(new Gtk::VBox());
    greenhouse_box->set_spacing(10);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='large' weight='bold'>Greenhouse Overview</span>");
    greenhouse_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    // Greenhouse action buttons
    Gtk::Button* view_summary_btn = Gtk::manage(new Gtk::Button("View Greenhouse Summary"));
    Gtk::Button* view_inventory_btn = Gtk::manage(new Gtk::Button("View Inventory"));
    Gtk::Button* view_staff_btn = Gtk::manage(new Gtk::Button("View Staff"));
    Gtk::Button* water_plants_btn = Gtk::manage(new Gtk::Button("Water All Plants"));
    Gtk::Button* fertilize_plants_btn = Gtk::manage(new Gtk::Button("Fertilize All Plants"));

    view_summary_btn->set_size_request(250, 50);
    view_inventory_btn->set_size_request(250, 50);
    view_staff_btn->set_size_request(250, 50);
    water_plants_btn->set_size_request(250, 50);
    fertilize_plants_btn->set_size_request(250, 50);

    greenhouse_box->pack_start(*view_summary_btn, Gtk::PACK_SHRINK);
    greenhouse_box->pack_start(*view_inventory_btn, Gtk::PACK_SHRINK);
    greenhouse_box->pack_start(*view_staff_btn, Gtk::PACK_SHRINK);
    greenhouse_box->pack_start(*water_plants_btn, Gtk::PACK_SHRINK);
    greenhouse_box->pack_start(*fertilize_plants_btn, Gtk::PACK_SHRINK);

    // Text view for displaying greenhouse information
    Gtk::ScrolledWindow* scrolled_window = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    Gtk::TextView* text_view = Gtk::manage(new Gtk::TextView());
    text_view->set_editable(false);
    text_view->set_cursor_visible(false);
    scrolled_window->add(*text_view);
    greenhouse_box->pack_start(*scrolled_window, Gtk::PACK_EXPAND_WIDGET);

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

    m_content_box->pack_start(*greenhouse_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = greenhouse_box;

    show_all_children();
    updateStatus("Greenhouse view - Select action to view or manage greenhouse");
}

void Window::clearMainArea() {
    // Remove all children from content box
    std::vector<Gtk::Widget*> children = m_content_box->get_children();
    for (Gtk::Widget* child : children) {
        m_content_box->remove(*child);
    }
    m_current_content = nullptr;
}

void Window::updateStatus(const std::string& message) {
    m_status_label->set_text("Status: " + message);
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