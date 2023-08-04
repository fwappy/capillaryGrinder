#include "capillaryGrinder_menu.h"

// Z-axis Stepper Motor Pins
const int motorZStepPin = 5;
const int motorZDirectionPin = 6;
const int motorZEnablePin = 7;
const int motorZstepsPerMicron = 10;

// Capillary Stepper Motor Pins
const int motorCapillaryStepPin = 8;
const int motorCapillaryDirectionPin = 9;
const int motorCapillaryEnablePin = 10;
const int motorCapillaryStepsPerRev = 200;

// Global Variables
uint8_t motorCapillaryTaskId;
bool internalMotorCapillaryStepState = LOW;

uint8_t motorZTaskId;
bool internalMotorZStepState = LOW;
unsigned long internalMotorZStepCount = 0;
unsigned long internalMotorZStepMax;

void setup() {
    Serial.begin(9600);
    setupMenu();
    
    internalDigitalDevice().pinMode(motorZStepPin, OUTPUT);
    internalDigitalDevice().pinMode(motorZDirectionPin, OUTPUT);
    internalDigitalDevice().pinMode(motorZEnablePin, OUTPUT);
    
    internalDigitalDevice().pinMode(motorCapillaryStepPin, OUTPUT);
    internalDigitalDevice().pinMode(motorCapillaryDirectionPin, OUTPUT);
    internalDigitalDevice().pinMode(motorCapillaryEnablePin, OUTPUT);
}

void loop() {
    taskManager.runLoop();
}


void moveMotorZ(long distance, int speed) {  // speed in um/sec
    // Set Direction based on +/- distance
    digitalWrite(motorZDirectionPin, distance > 0);
  
    // Calculate Steps based on distance
    internalMotorZStepGoal = internalMotorZStepCount+(distance * motorZstepsPerMicron);

    // Calculate Delay Time based on speed
    int delayTime = 1/(2000*motorZstepsPerMicron*speed); // double check this

    if (distance >= 0) {
        digitalWrite(motorZDirectionPin, HIGH);
        motorZTaskId = taskManager.schedule(repeatMillis(delayTime), internalMotorZStepInc); 
    } else if (distance < 0) {
        digitalWrite(motorZDirectionPin, LOW);
        motorZTaskId = taskManager.schedule(repeatMillis(delayTime), internalMotorZStepDec); 
    }    
}

  void internalMotorZStepInc() {  // function for TaskManagerIO to tell motor to take step
    if (internalMotorZStepCount <= internalMotorZStepMax) {
        stopMotorZ()
    }

    internalDigitalDevice().digitalWriteS(motorCapillaryStepPin, internalMotorZStepState);
    if (internalMotorZStepState = LOW){
        internalMotorZStepCount++;
    }

    internalMotorZStepState = !internalMotorZStepState;
  }

  void internalMotorZStepDec() {  // function for TaskManagerIO to tell motor to take step
    if (internalMotorZStepCount <= internalMotorZStepMax) {
        stopMotorZ()
    }

    internalDigitalDevice().digitalWriteS(motorCapillaryStepPin, internalMotorZStepState);
    if (internalMotorZStepState = LOW){
        internalMotorZStepCount--;
    }

    internalMotorZStepState = !internalMotorZStepState;
  }

void stopMotorZ() {
    taskManager.cancelTask(motorZTaskId);
}

void startMotorCapillary(int speed) {  //speed in rpm
    int delayTime = 1/(2*motorCapillaryStepsPerRev*speed);  // most definitely incorrect
  
    taskIdMotorCapillary = taskManager.schedule(repeatMillis(delayTime), internalMotorCapillaryStep);
}

  void internalMotorCapillaryStep() {  // function for TaskManagerIO to tell motor to take step
    internalDigitalDevice().digitalWriteS(motorCapillaryStepPin, internalMotorCapillaryStepState);

    internalMotorCapillaryStepState = !internalMotorCapillaryStepState; 
  }


void stopMotorCapillary() {
    taskManager.cancelTask(taskIdMotorCapillary);
}

void CALLBACK_FUNCTION setZeroed(int id) {
    // if selection is "ignore" or (id = NULL)
    //  Make start button visible/hide not zeroed selector for all categories
    // if selection is "zero" call CalibrateZero
    

    if (id.getCurrentValue() == "zero") {  //this is wrong, but i dont know what id should be
        CalibrateZero();
    } else {
        //  Make start button visible/ hide not zeroed selector for all categories
        GrindCapillaryStartGrindNotZeroed.setVisible(False);
        FaceCapillaryStartGrindNotZeroed.setVisible(False);
        FaceChipParametricStartGrindNotZeroed.setVisible(False);
        FaceChipSetDistanceStartGrindNotZeroed.setVisible(False);

        GrindCapillaryStartGrindStart.setVisible(True);
        FaceCapillaryStartGrindStart.setVisible(True);
        FaceChipParametricStartGrindStart.setVisible(True);
        FaceChipSetDistanceStartGrindStart.setVisible(True);
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
