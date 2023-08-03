#include "capillaryGrinder_menu.h"

// Z-axis Stepper Motor Pins
const int pinMotorZStep = 5;
const int pinMotorZDirection = 6;
const int pinMotorZEnable = 7;
const int stepsPerMicronZ = 10;

// Capillary Stepper Motor Pins
const int pinMotorCapillaryStep = 8;
const int pinMotorCapillaryDirection = 9;
const int pinMotorCapillaryEnable = 10;
const int stepsPerRevCapillary = 200;

// Global Variables
uint8_t taskIdCapillary;
int internalMotorCapillaryStepState = LOW;

void setup() {
    Serial.begin(9600);
    setupMenu();
    
    internalDigitalDevice().pinMode(pinMotorZStep, OUTPUT);
    internalDigitalDevice().pinMode(pinMotorZDirection, OUTPUT);
    internalDigitalDevice().pinMode(pinMotorZEnable, OUTPUT);
    
    internalDigitalDevice().pinMode(pinMotorCapillaryStep, OUTPUT);
    internalDigitalDevice().pinMode(pinMotorCapillaryDirection, OUTPUT);
    internalDigitalDevice().pinMode(pinMotorCapillaryEnable, OUTPUT);
}

void loop() {
    taskManager.runLoop();
}


void moveZAxis(long distance, int speed) {  // speed in um/sec
    // Set Direction based on +/- distance
    digitalWrite(pinMotorZDirection, distance > 0);
  
    // Calculate Steps based on distance
    long steps = abs(distance) * stepsPerMicronZ;
  
    // Calculate Delay Time based on speed
    int delayTime = 1/(2000*stepsPerMicronZ*speed); // double check this

    // Move Number of Steps
    for(int x = 0; x < steps; x++){
      taskManager.schedule(onceMillis(delayTime), internalMotorZStepHigh);
      taskManager.schedule(onceMillis(delayTime), internalMotorZStepLow);
    }
}

  void internalMotorZStepHigh() {  // function for TaskManagerIO to tell motor to take step
    internalDigitalDevice().digitalWrite(pinMotorZStep,HIGH);
  }


  void internalMotorZStepLow() {  // function for TaskManagerIO to tell motor to take step
    internalDigitalDevice().digitalWrite(pinMotorZStep,LOW);
  }


void startCapillary(int speed) {  //speed in rpm
    int delayTime = 1/(2*stepsPerRevCapillary*speed);  // most definitely incorrect
  
    taskIdCapillary = taskManager.schedule(repeatMillis(delayTime), internalCapillaryStep);
}

  void internalCapillaryStep() {  // function for TaskManagerIO to tell motor to take step
    internalDigitalDevice().digitalWriteS(pinMotorCapillaryStep, internalMotorCapillaryStepState);

    internalMotorCapillaryStepState = !internalMotorCapillaryStepState; 
  }


void stopCapillary() {
    taskManager.cancelTask(taskIdCapillary);
}

void CALLBACK_FUNCTION setZeroed(int id) {
    // if selection is "ignore" or (id = NULL)
    //  Make start button visible/hide not zeroed selector for all categories
    // if selection is "zero" call CalibrateZero
    

    if (id.getCurrentValue() == "zero") {  //this is wrong, but i dont know what id should be
        // call CalibrateZero
    } else {
        //  Make start button visible/hide not zeroed selector for all categories
    }
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
