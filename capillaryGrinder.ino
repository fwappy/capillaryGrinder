#include "capillaryGrinder_menu.h"

void setup() {
    Serial.begin(9600);
    setupMenu();

}

void loop() {
    taskManager.runLoop();

}


void CALLBACK_FUNCTION setZeroed(int id) {
    // if selection is "ignore" or (id = NULL)
    //  Make start button visible/hide not zeroed selector for all categories
    // if selection is "zero" call CalibrateZero
}

void CALLBACK_FUNCTION CalibrateZero(int id) {
    // Software travels down at 10 micron per second until sound signal digital output of “1” is received. 
    // Moves up 10 microns
    // Lowers at 1 micron a second until sound signal “1” is sent. (maximum 15 micron travel)
    // reset currentOffset
    // call moveOffset()
    // Call setZeroed()
}


void CALLBACK_FUNCTION moveOffset(int id) {
    // move to match currentOffset to menu offset
}


void CALLBACK_FUNCTION startGrindCapillary(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION startFaceCapillary(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION startFaceChipParametric(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION startFaceChipDistance(int id) {
    // TODO - your menu change code
}
