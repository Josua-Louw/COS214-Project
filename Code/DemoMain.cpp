#include "SystemHandler.h"
#include "TextSystemHandler.h"
#include "GUISystemHandler.h"

int main() {
    SystemHandler* systemHandler = new GUISystemHandler();
    systemHandler->systemMenue();
    delete systemHandler;
    return 0;
}