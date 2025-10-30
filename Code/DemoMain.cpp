#include "SystemHandler.h"
#include "TextSystemHandler.h"

int main() {
    SystemHandler* systemHandler = new TextSystemHandler();
    systemHandler->systemMenue();
    delete systemHandler;
    return 0;
}