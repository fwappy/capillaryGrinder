#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// This declares the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// EDIT THESE VALUES
int grindStepDistance = 10; // in microns
const unsigned long delayInterval = 20000; // This determines how long it will sit at each grind location in ms
int grindSpeed = 100; // in micron per second

// Z-Axis Stepper Motor Pins
const int stepPinZ = 10; 
const int dirPinZ = 9; 
const int enPinZ = 8;

// Capillary Stepper Motor Pins
const int stepPinCap = 11;
const int dirPinCap = 12;
const int enPinCap = 13;

// Button pins
const int potPin = A0;
const int next = 4;
const int start = 5;
const int stop = 3;
const int setZero = 2;

// Button States
int nextState = 0;
int startState = 0;
int setZeroState = 0;
int stopState = 0;

// Initial Variables
long OD = 360; // Outer Diameter
long ID = 75; // Inner Diameter
long angle = 15; // Angle
int potDial = 0; // Potentiometer Value
int menu = 0; // Determines what value you are changing on the home screen
int delayTime = 0; // Delay time will determine how fast the motor moves (will be set by using speed in micron / sec)
int depth = 0; // How deep the grinding needs to go
int percentage = 0; // How close to the end the grind is
int currentAngle = 0; // Used to make the screen not reset
int currentOD = 0; // Used to make the screen not reset
int currentID = 0; // Used to make the screen not reset
int stepCounter = 0; // Counts the number of downward steps that it takes
int currentSpeed = 0; // Used in setZeroFunc to stop screen from flickering
long endTime = 0; // Calculate the time that the program will stop
long grindTime = 0; // Calculate how long the grind will take
int faceWidth = 5; // Sets the width that remain on each side of the grind

// millis initialization
unsigned long initialMillis = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;



// Bool variable for zero being pressed
bool zeroPressed = false;
bool startPressed = false;
bool homeScreen = false;
bool finalGrind = false;
bool pressedZero = false;
bool finalGrindCompleted = false;
bool secondGrind = false;

// This function defines the set up
void setup() {
  //delay(5000);
  // LCD SetUP
  lcd.init();
  lcd.backlight();
  
  // Potentiometer Set-up 
  pinMode(potPin, INPUT);
  // Start Switch Set-Up
  pinMode(start, INPUT_PULLUP);
  // Next Button Set-Up
  pinMode(next, INPUT_PULLUP);
  
  // Set Zero Switch Set Up
  pinMode(setZero, INPUT_PULLUP);

  // Stop Button Set-Uo
  pinMode(stop, INPUT_PULLUP);

  // Z-Axis Pin Set Up
  pinMode(stepPinZ,OUTPUT); 
  pinMode(dirPinZ,OUTPUT);
  pinMode(enPinZ,OUTPUT);

  // Capillary Motor Rotation Set Up
  pinMode(stepPinCap,OUTPUT); 
  pinMode(dirPinCap,OUTPUT);
  pinMode(enPinCap,OUTPUT);

  // Set up motor to start running continuously
  digitalWrite(enPinZ,LOW);
  digitalWrite(enPinCap, HIGH);
  Serial.begin(115200);
  digitalWrite(dirPinCap, HIGH);
  analogWrite(stepPinCap, 128);
}

// This function shall be called whenever the stop button is pressed
// It completely stops the entire system until power is reset
void stopFunc(){
  // Kill Switch Set Up
  lcd.clear(); // Clears the screen
  digitalWrite(enPinCap, HIGH); // Turns off the capillary motor
  digitalWrite(enPinZ, HIGH); // Turns off the z-motor
  while(1); // Infinite loop in order to prevent anything else from occuring
}

// This function takes in a speed in microns per second, and
// returns the value in the delay time to be inputted into the move function
int delayTimeCalc(double speed){
  long travelPerRev = 4000; // microns
  long stepsPerRev = 40000; 
  double delayTime = (1 / speed) * 50000;
  return int(delayTime); 
}

// This function is called to complete the grind
// It will lower the capillary slowly until it has gone down the calculated distance
void runInitial(long distance) {
  // Makes the capillary motor begin to move
  digitalWrite(enPinCap, LOW);
  // Write to the screen that the capillary motor is moving
  lcd.setCursor(0,0);
  lcd.print("                       ");
  lcd.setCursor(0,0);
  lcd.print("Grind Started");
  // Set Direction of Z-Axis to be down
  digitalWrite(dirPinZ, HIGH);
  // Calculate the number of steps
  int steps = distance * 10;
  // Calculate the number of 10 micron steps necessary
  int stepCount = steps / (grindStepDistance * 10);
  // Calculate the number of steps remaining after 
  int remainingSteps = steps - stepCount * (grindStepDistance * 10);
  // Set up for the Percent counter
  lcd.setCursor(0,1);
  lcd.print("Percent Done:");
  // Check how far we have moved
  if(stepCounter < stepCount) { 
    // This tells it to move down 10 microns
    move(100, 1, delayTimeCalc(grindSpeed));
  } 
  else {
    // reset the current timer
    currentMillis = 0;
    // consider the start button unpressed
    startPressed = false;
    // run the remaining steps
    runFinal(remainingSteps);
  }
  
}

// This function will run the remaining steps as calculated in runInitial
void runFinal(int remainingSteps) {
  // Move the remaining steps
  move(remainingSteps, 1, 100);
  // This is set for the checkGrind function
  finalGrind = true;
}


// Move takes a step value, direction should be 1 or 0, where 1 is down and 0 is up
// delay time determines the speed. Typically 100 us.
void move(long steps, int direction, int delayTime){
  // Write direction of motor
  digitalWrite(dirPinZ, direction);
  // For Loop for number of steps
  for(int x = 0; x < steps; x++){
    if(digitalRead(stopState) != HIGH){
      stopFunc();
    }
    // Move Motor
    digitalWrite(stepPinZ,HIGH); 
    delayMicroseconds(delayTime); 
    digitalWrite(stepPinZ,LOW); 
    delayMicroseconds(delayTime);
  }
}

long endTimeCalc(long initialMillis, int distance){
  long steps = distance / 10;
  return (steps * 20000 + 30000 + initialMillis);
}

void checkGrind() {
  // Determine the current time
  currentMillis = millis();
  // Calculate the percentage if we are either in the initial or final grind
  if(startPressed || finalGrind){
    double percentage = 100 - (100 * (endTime - currentMillis) / grindTime);
    lcd.setCursor(15,1);
    lcd.print("%");
    lcd.setCursor(13,1);
    lcd.print(int(percentage));
  }
  // if it has been more than the delayInterval(which can be set at the top of the program)
  // and the start button has been pressed
  if(currentMillis - previousMillis >= delayInterval && startPressed){
      // Reset to count for another 20 seconds
      previousMillis = currentMillis;
      stepCounter++;
      // lcd.setCursor(8,1);
      // lcd.print(stepCounter);
      runInitial(distance(OD, ID, angle));
      // delay to prevent rapid looping
      delayMicroseconds(100);
  } 
  // if we have reached the stage of the final grind, and it has been 30 seconds since our previous movement
  else if (finalGrind && currentMillis - previousMillis >= delayInterval + 10000) {
    // reset the time
    previousMillis = currentMillis;
    // Move up half a centimeter in order to remove the capillary tube
    move(100000, 0, delayTimeCalc(1000));
    // Turn off the capillary motor
    digitalWrite(enPinCap, HIGH);
    // Print That the grind is done on the LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Grind Complete");
    lcd.setCursor(0,1);
    lcd.print("Press start");
    finalGrind = false;
    finalGrindCompleted = true;
    startPressed = false;
    secondGrind = true;
  }
  Serial.println("StartPressed: ");
  Serial.print(startPressed);
  Serial.println("secondGrind: ");
  Serial.print(secondGrind);
  Serial.println("finalGrindCompleted: ");
  Serial.print(finalGrindCompleted);
  // If start has been pressed again and the final grind was completed, we can 
  // reset the system to be ready for the next capillary tube
  if(startPressed && secondGrind && finalGrindCompleted){
    move(75000, 0, delayTimeCalc(1000));
    Serial.println("in loop");
    startPressed = false;
    finalGrindCompleted = false;
    homeScreen = false;
    secondGrind = false;
    delay(200L);
  }

}
// This function calculates the distance that we need to travel in order to properly grind at the given angle
long distance(int OD, int ID, int angle){
  double angleRad = angle * M_PI / 180;
  int R = (OD - ID) / 2;
  long distance = R * cos(angleRad) - faceWidth;
  return distance;
}

// This function will print the home screen
void lcdMenuSetup(){
  // LCD Print
  lcd.cursor_on();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Angle:");
  lcd.setCursor(6, 0);
  lcd.print("   "); 
  lcd.setCursor(6, 0);
  lcd.print(angle); 
  lcd.setCursor(12, 0);
  lcd.print("   "); 
  lcd.setCursor(10,0);
  lcd.print("OD:");
  lcd.print(OD);
  lcd.setCursor(4, 1);
  lcd.print("   "); 
  lcd.setCursor(0,1);
  lcd.print("ID:");
  lcd.print(ID);
  lcd.print("              ");
}

// This function determines the direction for the z-axis motor to move
// If the velocity given is negative, that means up, therefore this will
// return 0. If positive, it will return 1, meaning the motor will move down
int direction(int number){
  if(number < 0){
    return 0;
  }
  else{
    return 1;
  }
}


// This function will allow for the dial to control the motor, allowing 
// the zero to be set  
void setZeroFunc(){
  bool zeroing = digitalRead(setZero);
  // Read the location of the potentiometer
  int motorMove = analogRead(potPin);
  // Map the potentiometer values to mean various speeds
  int speed = map(motorMove, 0, 1023, 500, -500);
  // Move the motor in the direction and speed that was specified
  if( speed >= 50 || speed <= -50){
    move(100, direction(speed), delayTimeCalc(abs(speed)));
    if(speed < (currentSpeed + 5) && speed > (currentSpeed - 5)){
      lcd.setCursor(7,1);
      lcd.print("       ");
      if(direction(speed)){
        lcd.setCursor(7,1);
        lcd.print("+");
      }
      else{
        lcd.setCursor(7,1);
      }
      
      lcd.print(speed);
    }
    currentSpeed = speed;

    
  }
  else{
    lcd.setCursor(8,1);
    lcd.print("      ");
    lcd.setCursor(8,1);
    lcd.print(0);
  }
  
  // continue to run the function until the button is pressed again
  if(zeroing) {
    setZeroFunc();
    pressedZero = false;
  }
  else{
    homeScreen = false;
    delay(200L);
  }
}

void loop() {
  stopState = digitalRead(stop);
  zeroPressed = digitalRead(setZero);
  if(stopState == LOW){
    stopFunc();
  }
  if(zeroPressed == LOW) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Use Dial to Move");
    lcd.setCursor(0,1);
    lcd.print("Speed: ");
    pressedZero = true;
    delay(200L);
    setZeroFunc();
  }
  
  if(homeScreen == false){
    lcdMenuSetup(); // Adds values to the LCD
    homeScreen = true;
  }
  

  // Read in next button state
  nextState = digitalRead(next);
  
  // Read in if next state is high or low
  if(nextState == LOW){
      // Menu functions as which value you are editing, 0 is angle, 1 is OD, 2 is ID
      menu += 1;
      // If we reach 3, it will reset to allow you to edit the angle again
      if(menu == 3){
        menu = 0;
      }
      delay(200L);
    }
  // Useless else statement
  else{
    menu = menu;
  }
  // Read in the 
  int potValue = analogRead(potPin);
  // If statements that allow for editting the different parameters
  if(menu == 0){
    lcd.setCursor(7,0);
    angle = map(potValue, 0, 1023, 40, 10);
    if(currentAngle != angle){
      lcd.setCursor(6, 0);
      lcd.print("   "); 
      lcd.setCursor(6, 0);
      lcd.print(angle);
    }
    currentAngle = angle; 
  }
  else if(menu == 1){
    lcd.setCursor(15,0);
    int OD_map = map(potValue, 0, 1023, 60, 30);    
    OD = OD_map * 10;
    if(currentOD != OD){
      lcd.setCursor(13, 0);
      lcd.print("   "); 
      lcd.setCursor(13, 0);
      lcd.print(OD);
    }
    currentOD = OD;
  }
  else if(menu == 2){
    lcd.setCursor(4,1);
    int ID_map = map(potValue, 0, 1023, 25, 1);
    ID = ID_map * 5;
    if(currentID != ID){
      lcd.setCursor(3, 1);
      lcd.print("   "); 
      lcd.setCursor(3, 1);
      lcd.print(ID);
    }
    currentID = ID;
  }
  // Determine if start button gets pressed
  startState = digitalRead(start);
  // If it does, begin the process
  if(startState == LOW && secondGrind == true){
    startPressed = true;
  }
  
  if(startState == LOW && secondGrind == false){
    // Call run function with that depth
    startPressed = true;
    initialMillis = millis();
    endTime = endTimeCalc(initialMillis, distance(OD, ID, angle));
    grindTime = endTime - initialMillis;
    runInitial(distance(OD, ID, angle));
    delay(200L);
  }
  checkGrind();
}