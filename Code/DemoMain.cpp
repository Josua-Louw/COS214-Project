#include "SystemHandler.h"
#include "TextSystemHandler.h"

int main() {
    SystemHandler* systemHandler = new TextSystemHandler();
    delete systemHandler;
    return 0;
}