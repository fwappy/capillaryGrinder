#include "capillaryGrinder_menu.h"

// Input Encoder Pins
const int pinEncoderA = 2;
const int pinEncoderB = 3;
const int pinEncoderButton = 4;

// Z-axis Stepper Motor Pins
const int pinMotorZStep = 5;
const int pinMotorZDirection = 6;
const int pinMotorZEnable = 7;
const int stepsPerMicronZ = 10;

// Capillary Stepper Motor Pins
const int pinMotorCapillaryStep = 8;
const int pinMotorCapillaryDirection = 9;
const int pinMotorCapillaryEnable = 10;

// Global Variables


void setup() {
    Serial.begin(9600);

    // Setup Code goes here     
    
    setupMenu();

}

void loop() {
    taskManager.runLoop();
}


void moveZAxis(long distance, int speed) {
    // Set Direction based on +/- distance
    digitalWrite(pinMotorZDirection, distance > 0);
  
    // Calculate Steps based on distance
    long steps = abs(distance) * stepsPerMicronZ;
  
    // Calculate Delay Time based on speed
    int delayTime = ;

    // Move Number of Steps
    for(int x = 0; x < steps; x++){

    digitalWrite(pinMotorZStep, HIGH); 
    delayMicroseconds(delayTime); 
    digitalWrite(pinMotorZStep, LOW); 
    delayMicroseconds(delayTime);
  }
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
    // TODO
}


void CALLBACK_FUNCTION startFaceCapillary(int id) {
    // TODO
}


void CALLBACK_FUNCTION startFaceChipParametric(int id) {
    // TODO
}


void CALLBACK_FUNCTION startFaceChipDistance(int id) {
    // TODO
}
