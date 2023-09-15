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

void CALLBACK_FUNCTION calibrateZero(int id = 0) {
    // Software travels down at 10 micron per second until sound signal digital output of “1” is received. 

    moveMotorZ(-1000, 10, 1);

    //check if sound signal is received every ??? milliseconds, cancel motor move and move on to next step (if motor stops, give error message)


    // Moves up 10 microns
    moveMotorZ(10, 50, 1);

    // Lowers at 1 micron a second until sound signal “1” is sent. (maximum 15 micron travel)
    moveMotorZ(15, 1, 1);

    // reset current position
    internalMotorZStepCount = 0;

    // call moveOffset()
    // Call setZeroed()
}

int getMenuItemValue(int id) {
  MenuItem* item = getMenuItemById(id);
  if (item->getMenuType() == MENUTYPE_ENUM_VALUE){
    ValueMenuItem* valueItem = dynamic_cast<ValueMenuItem*>(item);
  }
  return valueItem->getCurrentValue();
}

void CALLBACK_FUNCTION setZeroed(int id = 0) {
    // get value of selected menu item
    int val;
    switch (id) {
        case -1:
            val = 0;
            break;
        case 0:
            val = 1;
            break;
        default:
            val = getMenuItemValue(id);
    }  
    serlogF3(SER_USER_1, "id, value = ", id, val);

    // 0 = zero, 1 = ignore
    if (val == 0){
        calibrateZero();
    }
    else {
        //  Make start button visible/ hide not zeroed selector for all categories
        menuGrindCapillaryStartGrindNotZeroed.setVisible(false);
        menuFaceCapillaryStartGrindNotZeroed.setVisible(false);
        menuFaceChipParametricStartGrindNotZeroed.setVisible(false);
        menuFaceChipSetDistanceStartGrindNotZeroed.setVisible(false);

        menuGrindCapillaryStartGrindStart.setVisible(true);
        menuFaceCapillaryStartGrindStart.setVisible(true);
        menuFaceChipParametricStartGrindStart.setVisible(true);
        menuFaceChipSetDistanceStartGrindStart.setVisible(true);
    }
    }

void CALLBACK_FUNCTION moveOffset(int id = 0) {
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
