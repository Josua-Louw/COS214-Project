#include "Window.h"
#include "GUISystemHandler.h"

Window::Window(GUISystemHandler* guiSystem) : m_button("Click Me"), m_gui_system_handler(guiSystem)
{
    set_title("Greenhouse Management System");
    set_default_size(600, 1200);

    m_button.set_margin(10);
    m_button.set_size_request(100, 50);
    m_button.signal_clicked().connect(sigc::mem_fun(*m_gui_system_handler, &GUISystemHandler::addPlant));
    set_child(m_button);
}

void Window::on_button_click()
{
    m_button.set_label("Clicked");
}