#include "capillaryGrinder_menu.h"

void setup() {
    Serial.begin(9600);
    setupMenu();

}

void loop() {
    taskManager.runLoop();

}



void CALLBACK_FUNCTION setZero(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION setOffset(int id) {
    // TODO - your menu change code
}
