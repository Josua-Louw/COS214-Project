#include "GUISystemHandler.h"

GUISystemHandler::GUISystemHandler() = default;

GUISystemHandler::~GUISystemHandler() = default;

void GUISystemHandler::systemMenue()
{
    auto app = Gtk::Application::create("org.gtkmm.example");
    app->make_window_and_run<Window>(0, nullptr, this);
}

void GUISystemHandler::addPlant()
{
    // GUI flow not implemented yet.
    std::cout << "Add Plant GUI flow not implemented yet." << std::endl;
}

void GUISystemHandler::registerStaffMember()
{
    // GUI flow not implemented yet.
}

void GUISystemHandler::processCustomerOrder()
{
    // GUI flow not implemented yet.
}