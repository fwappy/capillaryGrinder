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
int internalCalibrateOffsetOldValue;
int menuState = 0;
const int motorZTravelSpeed = 2500;
const int displayResetTime = 300;

uint8_t motorCapillaryTaskId;
bool internalMotorCapillaryStepState = LOW;

uint8_t motorZTaskId;
bool internalMotorZStepState = LOW;
long internalMotorZStepCount = 0;
long internalMotorZStepGoal;

// Function declarations
int MotorZPosition();
void moveMotorZ(int position, int speed = motorZTravelSpeed, bool relative = 1); // speed in um/sec
void internalMotorZStepInc();
void internalMotorZStepDec();
void stopMotorz();
void startMotorCapillary(int speed = 10); // speed in rpm
void internalMotorCapillaryStep();
void stopMotorCapillary();
int getMenuItemValue(int id);
void grindPass(int& depthRemaining, int& passDepth, int& grindRate, float& delayTime, bool done = 0);



void setup() {
  Serial.begin(9600);
  setupMenu();

  internalDigitalDevice().pinMode(motorZStepPin, OUTPUT);
  internalDigitalDevice().pinMode(motorZDirectionPin, OUTPUT);
  internalDigitalDevice().pinMode(motorZEnablePin, OUTPUT);

  internalDigitalDevice().pinMode(motorCapillaryStepPin, OUTPUT);
  internalDigitalDevice().pinMode(motorCapillaryDirectionPin, OUTPUT);
  internalDigitalDevice().pinMode(motorCapillaryEnablePin, OUTPUT);

  internalCalibrateOffsetOldValue = menuCalibrateOffset.getWhole();

  renderer.setResetIntervalTimeSeconds(displayResetTime);
}

void loop() {
  taskManager.runLoop();
}

int MotorZPosition() {
  return (internalMotorZStepCount / motorZstepsPerMicron);
}

void moveMotorZ(int position, int speed = motorZTravelSpeed, bool relative = 0) {  // speed in um/sec

  // Calculate Steps based on position
  if (relative) {
    internalMotorZStepGoal = (position * motorZstepsPerMicron) + internalMotorZStepCount;
  } else {
    internalMotorZStepGoal = (position * motorZstepsPerMicron);
  }

  // Calculate Delay Time based on speed
  int delayTime = 1 / (2000 * motorZstepsPerMicron * speed); // double check this

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
  if (internalMotorZStepState = LOW) {
    internalMotorZStepCount++;
  }

  internalMotorZStepState = !internalMotorZStepState;
}

void internalMotorZStepDec() {  // function for TaskManagerIO to tell motor to take step
  if (internalMotorZStepCount <= internalMotorZStepGoal) {
    stopMotorZ();
  }

  internalDigitalDevice().digitalWriteS(motorCapillaryStepPin, internalMotorZStepState);
  if (internalMotorZStepState = LOW) {
    internalMotorZStepCount--;
  }

  internalMotorZStepState = !internalMotorZStepState;
}

void stopMotorZ() {
  taskManager.cancelTask(motorZTaskId);
}

void startMotorCapillary(int speed = 10) {  //speed in rpm
  int delayTime = 1 / (2 * motorCapillaryStepsPerRev * speed); // most definitely incorrect

  motorCapillaryTaskId = taskManager.schedule(repeatMillis(delayTime), internalMotorCapillaryStep);
}

void internalMotorCapillaryStep() {  // function for TaskManagerIO to tell motor to take step
  internalDigitalDevice().digitalWriteS(motorCapillaryStepPin, internalMotorCapillaryStepState);

  internalMotorCapillaryStepState = !internalMotorCapillaryStepState;
}


void stopMotorCapillary() {
  taskManager.cancelTask(motorCapillaryTaskId);
}

int getMenuItemValue(int id) {
  MenuItem* item = getMenuItemById(id);

}

void grindPass(int& depthRemaining, int& passDepth, int& grindRate, float& delayTime, bool done) {
  moveMotorZ(-1 * passDepth, grindRate, 1);
  depthRemaining = depthRemaining - passDepth
  if (passDepth <= depthRemaining) {
    taskManager.schedule(onceSeconds(delayTime), grindPass(depthRemaining, passDepth, grindRate, delayTime));
  }
  else if (depthRemaining > 0){
    passDepth = depthRemaining
    taskManager.schedule(onceSeconds(delayTime), grindPass(depthRemaining, passDepth, grindRate, delayTime));
  }
  else if (done = 1) {
    moveMotorZ(0, , 0);
    // return to UI
  }
  else if (depthRemaining = 0) {
    taskManager.schedule(onceSeconds(delayTime), grindPass(depthRemaining, passDepth, grindRate, delayTime, 1));
  }
  else {
    serlogF2(SER_ERROR, "Error: Grind operation went too far! Position relative to target in um:", depthRemaining);
  }
}

void CALLBACK_FUNCTION calibrateZero(int id = 0) {
  // display "Calibrating" message
  menuState = 2;
  renderer.takeOverDisplay(myDisplayCallback);

  // Software travels down at 10 micron per second until sound signal digital output of “1” is received.

  moveMotorZ(-1000, 10, 1);

  //check if sound signal is received every ??? milliseconds, cancel motor move and move on to next step (if motor stops, give error message)


  // Moves up 10 microns
  moveMotorZ(10, 50, 1);

  // Lowers at 1 micron a second until sound signal “1” is sent. (maximum 15 micron travel)
  moveMotorZ(15, 1, 1);

  // set zero position
  internalMotorZStepCount = 0 + (menuCalibrateOffset.getWhole() * motorZstepsPerMicron);

  // clear Not Zeroed entries
  setZeroed();

  // clear "Calibrating" message
  menuState = 0;

  // Move to Zero position
  moveMotorZ(0, 50, 0);
}

void CALLBACK_FUNCTION notZeroed(int id = 0) {
  // get value of selected menu item
  int val;
  switch (id) {
    case 13:
      val = menuGrindCapillaryStartGrindNotZeroed.getCurrentValue();
      break;
    case 18:
      val = menuFaceCapillaryStartGrindNotZeroed.getCurrentValue();
      break;
    case 28:
      val = menuFaceChipParametricStartGrindNotZeroed.getCurrentValue();
      break;
    case 32:
      val = menuFaceChipSetDistanceStartGrindNotZeroed.getCurrentValue();
      break;
    default:
      serlogF1(SER_ERROR, "Error: Must include menu entry in setZeroed()");
      menuState = -10;
      break;
  }
  serlogF3(SER_USER_1, "id, value = ", id, val);

  // 0 = zero, 1 = ignore
  if (val == 0) {
    calibrateZero();
  }
  else {
    setZeroed();
  }
}

void setZeroed() {
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

void CALLBACK_FUNCTION moveOffset(int id = 0) {
  internalMotorZStepCount = internalMotorZStepCount + ((menuCalibrateOffset.getWhole() - internalCalibrateOffsetOldValue) * motorZstepsPerMicron);
  internalCalibrateOffsetOldValue = menuCalibrateOffset.getWhole();
  moveMotorZ(0, 50, 0);
}


void CALLBACK_FUNCTION startGrindCapillary(int id) {
  menuState = 1;
  renderer.takeOverDisplay(myDisplayCallback);
  menuMgr.save();

  int grindDelayTime = 20;

  float angleRad = menuGrindCapillaryAngleDegrees.getCurrentValue() * M_PI / 180;
  int R = (menuGrindCapillaryOuterDiameter.getCurrentValue() - menuGrindCapillaryInnerDiameter.getCurrentValue()) / 2;
  float depthRemaining = R * cos(AngleRad) - FaceWidth;

  startMotorCapillary();

  // TODO
// add ability to set feedDepth, delaty time, total depth in UI

  taskManager.schedule(onceSeconds(delayTime), grindPass(depthRemaining, passDepth, grindRate, delayTime));

}


void CALLBACK_FUNCTION startFaceCapillary(int id) {
  menuState = 1;
  renderer.takeOverDisplay(myDisplayCallback);
  menuMgr.save();

  if (menuFaceCapillaryCapillaryMotor.getCurrentValue() == true) {
    startMotorCapillary();
  }
  else {
    stopMotorCapillary();
  }
  
  // TODO
  /*

                • Wait FaceDelayTime
                • //default value is 60 seconds
                • If (FaceDepthRemaining/FaceStepDistance > 1)
                    ◦ StepDistance = FaceStepDistance
                    ◦ //(default value is 1 microns)
                    ◦ Move down StepDistance
                    ◦ At FaceSpeed rate 
                    ◦ //(default is 1 microns/second)
                    ◦ FaceDepthRemaining = FaceDepthRemaining - StepDistance
                    ◦ Wait FaceDelayTime
                • Else if (FaceDepthRemaining/FaceStepDistance < 1)
                    ◦ StepDistance = FaceDepthRemaining
                    ◦ Move down StepDistance
                    ◦ At FaceSpeed rate 
                    ◦ //(default is 1 microns/second)
                    ◦ FaceDepthRemaining = FaceDepthRemaining - StepDistance
                    ◦ Wait GrindDelayTime
                    ◦ Move up 20,000 microns At TravelSpeed
                        ▪ //default value is 2500 microns/second
                    ◦ Give Grind complete message
                        ▪ OK
                            • Return to main menu
                • Else
                    ◦ Printscreen = “error face distance”
   */
}


void CALLBACK_FUNCTION startFaceChipParametric(int id) {
  menuState = 1;
  renderer.takeOverDisplay(myDisplayCallback);
  menuMgr.save();
  // TODO
    /*
   *                ◦ Wait ChipDelayTime
                    ◦ //Default is 30 seconds
                    ◦ Move down FlatChannelDepth
                    ◦ Wait ChipDelayTime
                    ◦ If (ChipDepthRemaining/ChipStepDistance > 1)
                        ▪ StepDistance = ChipStepDistance
                        ▪ //(default value is 5 microns)
                        ▪ Move down StepDistance
                        ▪ At ChipSpeed rate 
                        ▪ //(default is 1 microns/second)
                        ▪ ChipDepthRemaining = ChipDepthRemaining - StepDistance
                        ▪ Wait ChipDelayTime
                    ◦ Else if (ChipDepthRemaining/ChipStepDistance < 1)
                        ▪ StepDistance = ChipDepthRemaining
                        ▪ Move down StepDistance
                        ▪ At ChipSpeed rate 
                        ▪ //(default is 1 microns/second)
                        ▪ ChipDepthRemaining = ChipDepthRemaining - StepDistance
                        ▪ Wait ChipDelayTime
                        ▪ Move up 20,000 microns At TravelSpeed
                            • //default value is 2500 microns/second
                        ▪ Give Grind complete message
                            • OK
                                ◦ Return to main menu
                    ◦ Else
                        ▪ Printscreen = “error chip distance”


   */
}


void CALLBACK_FUNCTION startFaceChipDistance(int id) {
  menuState = 1;
  renderer.takeOverDisplay(myDisplayCallback);
  menuMgr.save();
  // TODO
}

// This will be called frequently by the renderer class
// here we give control back when the button is clicked.
void myDisplayCallback(unsigned int encoderValue, RenderPressMode clicked) {
  // At this point clicked is the status of the select button
  // it can be RPRESS_NONE, RPRESS_PRESSED or RPRESS_HELD
  // encoderValue is the current value of the rotary encoder

  // menuState 0  | menu
  // menuState 1  | grinding
  // menuState 2  | zeroing
  // menuState -x | error
  if (clicked == true) {
    menuState = 0;
  }
  switch (menuState) {
   case 0:
    stopMotorZ();
    stopMotorCapillary();
    renderer.giveBackDisplay();
    
  case 1:
    // display "grinding"
    
  case 2:
    // display "zeroing"
    
  default:
    //display error (menuState)

  }
    
  /*TODO:
    Display Grinding message when grinding (displayState = 1)
    Display Zeroing Message when zeroing (displayState = 2)
    cancel active task and return to menu when button clicked
  */
}
