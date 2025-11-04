#include "Window.h"
#include "GUISystemHandler.h"
#include <iostream>
#include "AddPlant.h"
#include "AddPot.h"
#include "AddSeed.h"
#include "AddDecoration.h"

Window::Window(GUISystemHandler* guiSystem) 
    : m_gui_system_handler(guiSystem),
      m_current_content(nullptr),
      m_add_plant_state(addPlantState::PLANT),  
      m_register_staff_state(registerStaffState::PLANT_CARETAKER),
      m_process_order_state(processOrderState::CUSTOMER_ORDER)
{
    moneyInTheBank = 1000.0;
    set_title("Greenhouse Management System");
    set_default_size(900, 700);
    set_border_width(10);
    
    // Create all widgets dynamically
    m_main_box = new Gtk::VBox(false, 10);
    m_header_box = new Gtk::HBox(false, 5);
    m_content_box = new Gtk::VBox(false, 15);
    m_footer_box = new Gtk::HBox(false, 5);
    
    m_title_label = new Gtk::Label("🌿 Greenhouse Management System 🌿");
    m_money_label = new Gtk::Label("💰 Money in the Bank: $1000.00");
    m_main_menu_btn = new Gtk::Button("🏠 Main Menu");
    m_plant_mgmt_btn = new Gtk::Button("🌱 Plants");
    m_staff_mgmt_btn = new Gtk::Button("👥 Staff");
    m_order_btn = new Gtk::Button("🛒 Orders");
    m_greenhouse_btn = new Gtk::Button("🏢 View");
    m_status_label = new Gtk::Label("Ready");
    
    // Make title label bigger and bold
    m_title_label->set_markup("<span size='x-large' weight='bold'>🌿 Greenhouse Management System 🌿</span>");
    
    // Setup main layout structure (only once)
    setupLayout();
    
    // Show initial content
    showMainMenu();
}

Window::~Window() {
    // GTK manages widget cleanup through parent-child relationships
    delete m_title_label;
    delete m_money_label;
    delete m_main_menu_btn;
    delete m_plant_mgmt_btn;
    delete m_staff_mgmt_btn;
    delete m_order_btn;
    delete m_greenhouse_btn;
    delete m_status_label;

    delete m_main_box;
    delete m_header_box;
    delete m_content_box;
    delete m_footer_box;
}

void Window::setupLayout() {
    // Setup header with navigation buttons
    m_header_box->set_spacing(5);
    m_header_box->pack_start(*m_title_label, Gtk::PACK_EXPAND_WIDGET);
    m_header_box->pack_start(*m_money_label, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_main_menu_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_plant_mgmt_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_staff_mgmt_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_order_btn, Gtk::PACK_SHRINK);
    m_header_box->pack_start(*m_greenhouse_btn, Gtk::PACK_SHRINK);

    // Add separator after header
    Gtk::HSeparator* sep1 = Gtk::manage(new Gtk::HSeparator());
    
    // Setup content area
    m_content_box->set_spacing(15);

    // Setup footer with status
    Gtk::HSeparator* sep2 = Gtk::manage(new Gtk::HSeparator());
    m_footer_box->pack_start(*m_status_label, Gtk::PACK_SHRINK);

    // Assemble main layout
    m_main_box->pack_start(*m_header_box, Gtk::PACK_SHRINK);
    m_main_box->pack_start(*sep1, Gtk::PACK_SHRINK);
    m_main_box->pack_start(*m_content_box, Gtk::PACK_EXPAND_WIDGET);
    m_main_box->pack_start(*sep2, Gtk::PACK_SHRINK);
    m_main_box->pack_start(*m_footer_box, Gtk::PACK_SHRINK);

    add(*m_main_box);

    // Connect navigation signals (only once)
    m_main_menu_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_main_menu_clicked));
    m_plant_mgmt_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_plant_management_clicked));
    m_staff_mgmt_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_staff_management_clicked));
    m_order_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_order_processing_clicked));
    m_greenhouse_btn->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_greenhouse_view_clicked));

    show_all_children();
}

void Window::showMainMenu() {
    clearMainArea();

    Gtk::VBox* main_menu_box = Gtk::manage(new Gtk::VBox(false, 20));
    main_menu_box->set_border_width(20);

    Gtk::Label* welcome_label = Gtk::manage(new Gtk::Label());
    welcome_label->set_markup(
        "<span size='xx-large' weight='bold'>Welcome!</span>\n\n"
        "<span size='large'>Select an option from the menu above to get started.</span>\n\n"
        "• <b>Plants</b>: Add plants, pots, seeds, and decorations\n"
        "• <b>Staff</b>: Register and manage staff members\n"
        "• <b>Orders</b>: Process customer orders\n"
        "• <b>View</b>: See greenhouse summary and inventory"
    );
    welcome_label->set_line_wrap(true);
    
    main_menu_box->pack_start(*welcome_label, Gtk::PACK_EXPAND_WIDGET);

    m_content_box->pack_start(*main_menu_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = main_menu_box;

    show_all_children();
    updateStatus("Ready - Select an option from the menu");
}

void Window::setupPlantManagement() {
    clearMainArea();

    Gtk::VBox* plant_box = Gtk::manage(new Gtk::VBox(false, 15));
    plant_box->set_border_width(20);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='xx-large' weight='bold'>🌱 Plant Management</span>");
    plant_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    Gtk::Label* instruction_label = Gtk::manage(new Gtk::Label());
    instruction_label->set_markup("<span size='large'>Click a button to add items to your greenhouse:</span>");
    instruction_label->set_margin_top(10);
    instruction_label->set_margin_bottom(10);
    plant_box->pack_start(*instruction_label, Gtk::PACK_SHRINK);

    // Create a grid for better button layout
    Gtk::Grid* button_grid = Gtk::manage(new Gtk::Grid());
    button_grid->set_row_spacing(15);
    button_grid->set_column_spacing(15);
    button_grid->set_halign(Gtk::ALIGN_CENTER);

    // Plant type buttons with better labels
    Gtk::Button* add_plant_btn = Gtk::manage(new Gtk::Button("🌹 Add Plant\n(Regular flowering/foliage plant)"));
    Gtk::Button* add_pot_btn = Gtk::manage(new Gtk::Button("🏺 Add Pot\n(Container for plants)"));
    Gtk::Button* add_seed_btn = Gtk::manage(new Gtk::Button("🌰 Add Seeds\n(Seed packets for growing)"));
    Gtk::Button* add_decoration_btn = Gtk::manage(new Gtk::Button("✨ Add Decoration\n(Ornamental items)"));

    add_plant_btn->set_size_request(280, 80);
    add_pot_btn->set_size_request(280, 80);
    add_seed_btn->set_size_request(280, 80);
    add_decoration_btn->set_size_request(280, 80);

    button_grid->attach(*add_plant_btn, 0, 0, 1, 1);
    button_grid->attach(*add_pot_btn, 1, 0, 1, 1);
    button_grid->attach(*add_seed_btn, 0, 1, 1, 1);
    button_grid->attach(*add_decoration_btn, 1, 1, 1, 1);

    plant_box->pack_start(*button_grid, Gtk::PACK_SHRINK);

    // Add info box
    Gtk::Frame* info_frame = Gtk::manage(new Gtk::Frame("ℹ️  Information"));
    Gtk::Label* info_label = Gtk::manage(new Gtk::Label(
        "Items added will be stored in your greenhouse inventory.\n"
        "Use the 'View' menu to see all items."
    ));
    info_label->set_margin_start(10);
    info_label->set_margin_end(10);
    info_label->set_margin_top(10);
    info_label->set_margin_bottom(10);
    info_frame->add(*info_label);
    plant_box->pack_start(*info_frame, Gtk::PACK_SHRINK);

    // Connect signals - set state then call handler
    add_plant_btn->signal_clicked().connect([this, add_plant_btn]() {
        if (moneyInTheBank < 10.0) {
            updateStatus("⚠️ Not enough funds to add a plant");
            return;
        }
        add_plant_btn->set_sensitive(false);
        m_add_plant_state = addPlantState::PLANT;
        m_gui_system_handler->addPlant();
        updateStatus("✓ Regular plant added to greenhouse");
        setMoneyInTheBank(moneyInTheBank - 10.0); // Deduct cost for adding a plant
        add_plant_btn->set_sensitive(true);
    });

    add_pot_btn->signal_clicked().connect([this, add_pot_btn]() {
        if (moneyInTheBank < 5.0) {
            updateStatus("⚠️ Not enough funds to add a pot");
            return;
        }
        add_pot_btn->set_sensitive(false);
        m_add_plant_state = addPlantState::POT;
        m_gui_system_handler->addPlant();
        updateStatus("✓ Pot added to greenhouse");
        setMoneyInTheBank(moneyInTheBank - 5.0); // Deduct cost for adding a pot
        add_pot_btn->set_sensitive(true);
    });

    add_seed_btn->signal_clicked().connect([this, add_seed_btn]() {
        if (moneyInTheBank < 3.0) {
            updateStatus("⚠️ Not enough funds to add a seed packet");
            return;
        }
        add_seed_btn->set_sensitive(false);
        m_add_plant_state = addPlantState::SEED;
        m_gui_system_handler->addPlant();
        updateStatus("✓ Seed packet added to greenhouse");
        setMoneyInTheBank(moneyInTheBank - 3.0); // Deduct cost for adding a seed packet
        add_seed_btn->set_sensitive(true);
    });

    add_decoration_btn->signal_clicked().connect([this, add_decoration_btn]() {
        if (moneyInTheBank < 3.0) {
            updateStatus("⚠️ Not enough funds to add a decoration");
            return;
        }
        add_decoration_btn->set_sensitive(false);
        m_add_plant_state = addPlantState::DECORATION;
        m_gui_system_handler->addPlant();
        updateStatus("✓ Decoration added to greenhouse");
        setMoneyInTheBank(moneyInTheBank - 3.0); // Deduct cost for adding a decoration
        add_decoration_btn->set_sensitive(true);
    });

    m_content_box->pack_start(*plant_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = plant_box;

    show_all_children();
    updateStatus("Plant management - Select item type to add");
}

void Window::setupStaffManagement() {
    clearMainArea();

    Gtk::VBox* staff_box = Gtk::manage(new Gtk::VBox(false, 15));
    staff_box->set_border_width(20);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='xx-large' weight='bold'>👥 Staff Management</span>");
    staff_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    Gtk::Label* instruction_label = Gtk::manage(new Gtk::Label());
    instruction_label->set_markup("<span size='large'>Register new staff members:</span>");
    instruction_label->set_margin_top(10);
    instruction_label->set_margin_bottom(10);
    staff_box->pack_start(*instruction_label, Gtk::PACK_SHRINK);

    // Registration section
    Gtk::Frame* register_frame = Gtk::manage(new Gtk::Frame("Register New Staff"));
    Gtk::VBox* register_box = Gtk::manage(new Gtk::VBox(false, 15));
    register_box->set_border_width(20);
    register_box->set_halign(Gtk::ALIGN_CENTER);

    Gtk::Button* add_caretaker_btn = Gtk::manage(new Gtk::Button("🧑‍🌾 Register Plant Caretaker"));
    Gtk::Button* add_manager_btn = Gtk::manage(new Gtk::Button("💼 Register Sales Manager"));

    add_caretaker_btn->set_size_request(350, 70);
    add_manager_btn->set_size_request(350, 70);

    register_box->pack_start(*add_caretaker_btn, Gtk::PACK_SHRINK);
    register_box->pack_start(*add_manager_btn, Gtk::PACK_SHRINK);
    register_frame->add(*register_box);
    staff_box->pack_start(*register_frame, Gtk::PACK_EXPAND_WIDGET);

    // Info section
    Gtk::Frame* info_frame = Gtk::manage(new Gtk::Frame("ℹ️  Information"));
    Gtk::Label* info_label = Gtk::manage(new Gtk::Label(
        "Plant Caretakers handle plant care tasks.\n"
        "Sales Managers process customer orders and sales."
    ));
    info_label->set_margin_start(10);
    info_label->set_margin_end(10);
    info_label->set_margin_top(10);
    info_label->set_margin_bottom(10);
    info_frame->add(*info_label);
    staff_box->pack_start(*info_frame, Gtk::PACK_SHRINK);

    // Connect signals - set state then call handler
    add_caretaker_btn->signal_clicked().connect([this, add_caretaker_btn]() {
        if (moneyInTheBank < 100.0) {
            updateStatus("⚠️ Not enough funds to hire a plant caretaker");
            return;
        }
        add_caretaker_btn->set_sensitive(false);
        m_register_staff_state = registerStaffState::PLANT_CARETAKER;
        m_gui_system_handler->registerStaffMember();
        updateStatus("✓ Plant caretaker registered successfully");
        setMoneyInTheBank(getMoneyInTheBank() - 100.0); // Deduct cost for hiring a caretaker
        add_caretaker_btn->set_sensitive(true);
    });

    add_manager_btn->signal_clicked().connect([this, add_manager_btn]() {
        if (moneyInTheBank < 150.0) {
            updateStatus("⚠️ Not enough funds to hire a sales manager");
            return;
        }
        add_manager_btn->set_sensitive(false);
        m_register_staff_state = registerStaffState::SALES_MANAGER;
        m_gui_system_handler->registerStaffMember();
        updateStatus("✓ Sales manager registered successfully");
        setMoneyInTheBank(getMoneyInTheBank() - 150.0); // Deduct cost for hiring a manager
        add_manager_btn->set_sensitive(true);
    });

    m_content_box->pack_start(*staff_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = staff_box;

    show_all_children();
    updateStatus("Staff management - Register new staff members");
}

void Window::setupOrderProcessing() {
    clearMainArea();

    Gtk::VBox* order_box = Gtk::manage(new Gtk::VBox(false, 15));
    order_box->set_border_width(20);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='xx-large' weight='bold'>🛒 Order Processing</span>");
    order_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    Gtk::Label* instruction_label = Gtk::manage(new Gtk::Label());
    instruction_label->set_markup("<span size='large'>Choose order type and process orders:</span>");
    instruction_label->set_margin_top(10);
    instruction_label->set_margin_bottom(10);
    order_box->pack_start(*instruction_label, Gtk::PACK_SHRINK);

    // Order type selection section
    Gtk::Frame* type_frame = Gtk::manage(new Gtk::Frame("Order Type"));
    Gtk::HBox* type_box = Gtk::manage(new Gtk::HBox(false, 15));
    type_box->set_border_width(15);
    type_box->set_halign(Gtk::ALIGN_CENTER);
    
    Gtk::Button* customer_order_btn = Gtk::manage(new Gtk::Button("👤 Customer Order\n(Simulated)"));
    Gtk::Button* admin_order_btn = Gtk::manage(new Gtk::Button("🔧 Admin Order\n(Manual)"));
    
    customer_order_btn->set_size_request(250, 80);
    admin_order_btn->set_size_request(250, 80);
    
    type_box->pack_start(*customer_order_btn, Gtk::PACK_EXPAND_WIDGET);
    type_box->pack_start(*admin_order_btn, Gtk::PACK_EXPAND_WIDGET);
    type_frame->add(*type_box);
    order_box->pack_start(*type_frame, Gtk::PACK_SHRINK);

    // Manual order creation section (for admin orders)
    Gtk::Frame* manual_frame = Gtk::manage(new Gtk::Frame("Manual Order Creation (Admin Only)"));
    Gtk::VBox* manual_vbox = Gtk::manage(new Gtk::VBox(false, 10));
    manual_vbox->set_border_width(15);
    
    Gtk::Button* create_order_btn = Gtk::manage(new Gtk::Button("📝 Create New Order"));
    create_order_btn->set_size_request(300, 50);
    manual_vbox->pack_start(*create_order_btn, Gtk::PACK_SHRINK);
    
    // Add items section
    Gtk::Label* add_items_label = Gtk::manage(new Gtk::Label("Add Items to Current Order:"));
    add_items_label->set_margin_top(10);
    add_items_label->set_margin_bottom(5);
    manual_vbox->pack_start(*add_items_label, Gtk::PACK_SHRINK);
    
    Gtk::Grid* items_grid = Gtk::manage(new Gtk::Grid());
    items_grid->set_row_spacing(10);
    items_grid->set_column_spacing(10);
    items_grid->set_halign(Gtk::ALIGN_CENTER);

    Gtk::Button* add_plant_order_btn = Gtk::manage(new Gtk::Button("🌹 Add Plant"));
    Gtk::Button* add_pot_order_btn = Gtk::manage(new Gtk::Button("🏺 Add Pot"));
    Gtk::Button* add_seed_order_btn = Gtk::manage(new Gtk::Button("🌰 Add Seeds"));
    Gtk::Button* add_decor_order_btn = Gtk::manage(new Gtk::Button("✨ Add Decoration"));

    add_plant_order_btn->set_size_request(180, 45);
    add_pot_order_btn->set_size_request(180, 45);
    add_seed_order_btn->set_size_request(180, 45);
    add_decor_order_btn->set_size_request(180, 45);

    items_grid->attach(*add_plant_order_btn, 0, 0, 1, 1);
    items_grid->attach(*add_pot_order_btn, 1, 0, 1, 1);
    items_grid->attach(*add_seed_order_btn, 0, 1, 1, 1);
    items_grid->attach(*add_decor_order_btn, 1, 1, 1, 1);
    
    manual_vbox->pack_start(*items_grid, Gtk::PACK_SHRINK);
    
    // Process order button
    Gtk::Button* process_order_btn = Gtk::manage(new Gtk::Button("✅ Process Order"));
    process_order_btn->set_size_request(300, 50);
    process_order_btn->set_margin_top(10);
    manual_vbox->pack_start(*process_order_btn, Gtk::PACK_SHRINK);
    
    manual_frame->add(*manual_vbox);
    order_box->pack_start(*manual_frame, Gtk::PACK_SHRINK);

    // Info section
    Gtk::Frame* info_frame = Gtk::manage(new Gtk::Frame("ℹ️  Information"));
    Gtk::Label* info_label = Gtk::manage(new Gtk::Label(
        "• Customer Order: Automatically generates a random order and processes it\n"
        "• Admin Order: Manually create and build an order step-by-step"
    ));
    info_label->set_margin_start(10);
    info_label->set_margin_end(10);
    info_label->set_margin_top(10);
    info_label->set_margin_bottom(10);
    info_frame->add(*info_label);
    order_box->pack_start(*info_frame, Gtk::PACK_SHRINK);

    // Connect signals for order type buttons
    customer_order_btn->signal_clicked().connect([this, customer_order_btn]() {
        customer_order_btn->set_sensitive(false);
        m_process_order_state = processOrderState::CUSTOMER_ORDER;
        m_gui_system_handler->processCustomerOrder();
        updateStatus("✓ Customer order generated and processed successfully!");
        customer_order_btn->set_sensitive(true);
    });

    admin_order_btn->signal_clicked().connect([this]() {
        m_process_order_state = processOrderState::SELF_ORDER;
        m_order_builders.clear(); // Clear any previous order builders
        updateStatus("ℹ️  Admin order mode selected - Create order below");
    });

    // Connect signals for manual order creation
    create_order_btn->signal_clicked().connect([this, create_order_btn]() {
        create_order_btn->set_sensitive(false);
        if (m_process_order_state != processOrderState::SELF_ORDER) {
            updateStatus("⚠️  Select 'Admin Order' type first");
            create_order_btn->set_sensitive(true);
            return;
        }
        for (auto builder : m_order_builders) {
            delete builder; // Clean up previous builders
        }
        m_order_builders.clear(); // Start fresh order
        updateStatus("✓ New admin order created - Add items to the order");
        create_order_btn->set_sensitive(true);
    });

    add_plant_order_btn->signal_clicked().connect([this]() {
        // Add plant builder to the order
        // Note: You'll need to include the proper headers for OrderBuilder classes
        m_order_builders.push_back(new AddPlant(m_gui_system_handler->getGreenHouse()));
        updateStatus("✓ Plant added to current order");
    });

    add_pot_order_btn->signal_clicked().connect([this]() {
        // Add pot builder to the order
        m_order_builders.push_back(new AddPot(m_gui_system_handler->getGreenHouse()));
        updateStatus("✓ Pot added to current order");
    });

    add_seed_order_btn->signal_clicked().connect([this]() {
        // Add seed builder to the order
        m_order_builders.push_back(new AddSeed(m_gui_system_handler->getGreenHouse()));
        updateStatus("✓ Seeds added to current order");
    });

    add_decor_order_btn->signal_clicked().connect([this]() {
        // Add decoration builder to the order
        m_order_builders.push_back(new AddDecoration(m_gui_system_handler->getGreenHouse()));
        updateStatus("✓ Decoration added to current order");
    });

    process_order_btn->signal_clicked().connect([this, process_order_btn]() {
        if (m_process_order_state != processOrderState::SELF_ORDER) {
            updateStatus("⚠️  Select 'Admin Order' type first");
            return;
        }
        process_order_btn->set_sensitive(false);
        //m_process_order_state = processOrderState::SELF_ORDER;
        m_gui_system_handler->processCustomerOrder();
        updateStatus("✓ Admin order processed successfully!");
        m_process_order_state = processOrderState::NONE; // Reset state
        m_order_builders.clear(); // Clear current order builders
        process_order_btn->set_sensitive(true);
    });

    m_content_box->pack_start(*order_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = order_box;

    show_all_children();
    updateStatus("Order processing - Select order type");
}


void Window::setupGreenhouseView() {
    clearMainArea();

    Gtk::VBox* greenhouse_box = Gtk::manage(new Gtk::VBox(false, 15));
    greenhouse_box->set_border_width(20);

    Gtk::Label* title_label = Gtk::manage(new Gtk::Label());
    title_label->set_markup("<span size='xx-large' weight='bold'>🏢 Greenhouse Overview</span>");
    greenhouse_box->pack_start(*title_label, Gtk::PACK_SHRINK);

    // Button section
    Gtk::HBox* button_box = Gtk::manage(new Gtk::HBox(false, 10));
    
    Gtk::Button* view_summary_btn = Gtk::manage(new Gtk::Button("📊 Summary"));
    Gtk::Button* view_inventory_btn = Gtk::manage(new Gtk::Button("📦 Inventory"));
    Gtk::Button* view_staff_btn = Gtk::manage(new Gtk::Button("👥 Staff Info"));

    view_summary_btn->set_size_request(150, 50);
    view_inventory_btn->set_size_request(150, 50);
    view_staff_btn->set_size_request(150, 50);

    button_box->pack_start(*view_summary_btn, Gtk::PACK_EXPAND_WIDGET);
    button_box->pack_start(*view_inventory_btn, Gtk::PACK_EXPAND_WIDGET);
    button_box->pack_start(*view_staff_btn, Gtk::PACK_EXPAND_WIDGET);

    greenhouse_box->pack_start(*button_box, Gtk::PACK_SHRINK);

    // Text view for displaying information
    Gtk::Frame* display_frame = Gtk::manage(new Gtk::Frame("Information Display"));
    Gtk::ScrolledWindow* scrolled_window = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window->set_size_request(850, 450);

    Gtk::TextView* text_view = Gtk::manage(new Gtk::TextView());
    text_view->set_editable(false);
    text_view->set_cursor_visible(false);
    text_view->set_wrap_mode(Gtk::WRAP_WORD);
    text_view->set_left_margin(10);
    text_view->set_right_margin(10);
    text_view->set_top_margin(10);
    text_view->set_bottom_margin(10);
    
    // Set monospace font for better alignment
    Pango::FontDescription font("Monospace 11");
    text_view->override_font(font);
    
    // Show initial summary
    auto buffer = text_view->get_buffer();
    buffer->set_text("Click a button above to view greenhouse information.");
    
    scrolled_window->add(*text_view);
    display_frame->add(*scrolled_window);
    greenhouse_box->pack_start(*display_frame, Gtk::PACK_EXPAND_WIDGET);

    // Connect signals
    view_summary_btn->signal_clicked().connect([this, text_view]() {
        std::string summary = m_gui_system_handler->getGreenhouseSummary();
        auto buffer = text_view->get_buffer();
        buffer->set_text(summary);
        updateStatus("📊 Greenhouse summary displayed");
    });

    view_inventory_btn->signal_clicked().connect([this, text_view]() {
        std::string inventory = m_gui_system_handler->getInventory();
        auto buffer = text_view->get_buffer();
        buffer->set_text(inventory);
        updateStatus("📦 Inventory displayed");
    });

    view_staff_btn->signal_clicked().connect([this, text_view]() {
        std::string staff = m_gui_system_handler->getStaffInfo();
        auto buffer = text_view->get_buffer();
        buffer->set_text(staff);
        updateStatus("👥 Staff information displayed");
    });

    // water_plants_btn->signal_clicked().connect([this, water_plants_btn]() {
    //     water_plants_btn->set_sensitive(false);
    //     m_gui_system_handler->waterAllPlants();
    //     updateStatus("✓ All plants have been watered");
    //     water_plants_btn->set_sensitive(true);
    // });

    // fertilize_plants_btn->signal_clicked().connect([this, fertilize_plants_btn]() {
    //     fertilize_plants_btn->set_sensitive(false);
    //     m_gui_system_handler->fertilizeAllPlants();
    //     updateStatus("✓ All plants have been fertilized");
    //     fertilize_plants_btn->set_sensitive(true);
    // });

    m_content_box->pack_start(*greenhouse_box, Gtk::PACK_EXPAND_WIDGET);
    m_current_content = greenhouse_box;

    show_all_children();
    updateStatus("Greenhouse view - Select an action");
}

void Window::clearMainArea() {
    std::vector<Gtk::Widget*> children = m_content_box->get_children();
    for (Gtk::Widget* child : children) {
        m_content_box->remove(*child);
    }
    m_current_content = nullptr;
}

void Window::updateStatus(const std::string& message) {
    m_status_label->set_markup("<b>Status:</b> " + message);
    std::cout << "Status: " << message << std::endl;
}

// Signal handler implementations
void Window::on_main_menu_clicked() {
    showMainMenu();
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

void Window::setMoneyInTheBank(double amount) {
    moneyInTheBank = amount;
    m_money_label->set_markup("💰 Money in the Bank: $" + std::to_string(moneyInTheBank));
}