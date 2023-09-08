//TODO - function that displays a message when the grind is in progress (progress bar?) and allows you to stop grind by clicking


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
long internalMotorZStepCount = 0;
long internalMotorZStepGoal;

// Declare Default Values
void CalibrateZero(int id = -1);

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

int MotorZPosition(){
  return (internalMotorZStepCount / motorZstepsPerMicron);
}

void moveMotorZ(int position, int speed, bool relative = 0) {  // speed in um/sec

    // Calculate Steps based on position
    if (relative) {
        internalMotorZStepGoal = (position * motorZstepsPerMicron) + internalMotorZStepCount;
    } else {
    internalMotorZStepGoal = (position * motorZstepsPerMicron);
    }
    
    // Calculate Delay Time based on speed
    int delayTime = 1/(2000*motorZstepsPerMicron*speed); // double check this

    // Set Direction
    if (internalMotorZStepGoal > internalMotorZStepCount) {

        digitalWrite(motorZDirectionPin, HIGH);
        motorZTaskId = taskManager.schedule(repeatMillis(delayTime), internalMotorZStepInc); 
    } else if (internalMotorZStepGoal < internalMotorZStepCount) {

        digitalWrite(motorZDirectionPin, LOW);
        motorZTaskId = taskManager.schedule(repeatMillis(delayTime), internalMotorZStepDec); 
    }    
}

  void internalMotorZStepInc() {  // function for TaskManagerIO to tell motor to take step
    if (internalMotorZStepCount >= internalMotorZStepGoal) {
        stopMotorZ();
    }

    internalDigitalDevice().digitalWriteS(motorCapillaryStepPin, internalMotorZStepState);
    if (internalMotorZStepState = LOW){
        internalMotorZStepCount++;
    }

    internalMotorZStepState = !internalMotorZStepState;
  }

  void internalMotorZStepDec() {  // function for TaskManagerIO to tell motor to take step
    if (internalMotorZStepCount <= internalMotorZStepGoal) {
        stopMotorZ();
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
  
    motorCapillaryTaskId = taskManager.schedule(repeatMillis(delayTime), internalMotorCapillaryStep);
}

  void internalMotorCapillaryStep() {  // function for TaskManagerIO to tell motor to take step
    internalDigitalDevice().digitalWriteS(motorCapillaryStepPin, internalMotorCapillaryStepState);

    internalMotorCapillaryStepState = !internalMotorCapillaryStepState; 
  }


void stopMotorCapillary() {
    taskManager.cancelTask(motorCapillaryTaskId);
}

void CALLBACK_FUNCTION setZeroed(int id) {
    // if selection is "ignore" or (id = NULL)
    //  Make start button visible/hide not zeroed selector for all categories
    // if selection is "zero" call CalibrateZero
    
/*
    if (menuGrindCapillaryStartGrindNotZeroed.getCurrentValue() == 0) {  //make work for all entries
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
    }*/
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
//    moveMotorZ(CalibrateOffset.getCurrentValue(), 10);
}


void CALLBACK_FUNCTION startGrindCapillary(int id) {
    menuMgr.save();
    // TODO
}


void CALLBACK_FUNCTION startFaceCapillary(int id) {
    menuMgr.save();
    // TODO
}


void CALLBACK_FUNCTION startFaceChipParametric(int id) {
    menuMgr.save();
    // TODO
}


void CALLBACK_FUNCTION startFaceChipDistance(int id) {
    menuMgr.save();
    // TODO
}
