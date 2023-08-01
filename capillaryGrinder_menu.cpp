/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "capillaryGrinder_menu.h"

// Global variable declarations
const  ConnectorLocalInfo applicationInfo = { "CapillaryGrinder", "5dfce237-d428-470a-aa66-36a7f5931a23" };
TcMenuRemoteServer remoteServer(applicationInfo);
ArduinoEEPROMAbstraction glArduinoEeprom(&EEPROM);
LiquidCrystal lcd(0, 1, 2, 4, 5, 6, 7);
LiquidCrystalRenderer renderer(lcd, 16, 2);
NoInitialisationNeeded serialInitializer;
SerialTagValueTransport serialTransport(&Serial);
TagValueRemoteServerConnection serialConnection(serialTransport, serialInitializer);

// Global Menu Item declarations
const char enumStrFaceChipSetDistanceStartGrindNotZeroed_0[] = "Zero";
const char enumStrFaceChipSetDistanceStartGrindNotZeroed_1[] = "Ignore";
const char* const enumStrFaceChipSetDistanceStartGrindNotZeroed[]  = { enumStrFaceChipSetDistanceStartGrindNotZeroed_0, enumStrFaceChipSetDistanceStartGrindNotZeroed_1 };
const EnumMenuInfo minfoFaceChipSetDistanceStartGrindNotZeroed = { "NotZeroed", 32, 0xffff, 1, setZeroed, enumStrFaceChipSetDistanceStartGrindNotZeroed };
EnumMenuItem menuFaceChipSetDistanceStartGrindNotZeroed(&minfoFaceChipSetDistanceStartGrindNotZeroed, 0, nullptr, INFO_LOCATION_PGM);
const char enumStrFaceChipSetDistanceStartGrindStart_0[] = "No";
const char enumStrFaceChipSetDistanceStartGrindStart_1[] = "Im Sure";
const char* const enumStrFaceChipSetDistanceStartGrindStart[]  = { enumStrFaceChipSetDistanceStartGrindStart_0, enumStrFaceChipSetDistanceStartGrindStart_1 };
const EnumMenuInfo minfoFaceChipSetDistanceStartGrindStart = { "Start", 31, 0xffff, 1, startFaceChipDistance, enumStrFaceChipSetDistanceStartGrindStart };
EnumMenuItem menuFaceChipSetDistanceStartGrindStart(&minfoFaceChipSetDistanceStartGrindStart, 0, &menuFaceChipSetDistanceStartGrindNotZeroed, INFO_LOCATION_PGM);
const SubMenuInfo minfoFaceChipSetDistanceStartGrind = { "StartGrind", 30, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackFaceChipSetDistanceStartGrind(&minfoFaceChipSetDistanceStartGrind, &menuFaceChipSetDistanceStartGrindStart, INFO_LOCATION_PGM);
SubMenuItem menuFaceChipSetDistanceStartGrind(&minfoFaceChipSetDistanceStartGrind, &menuBackFaceChipSetDistanceStartGrind, nullptr, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoFaceChipSetDistanceDistance = { "Distance", 29, 0xffff, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuFaceChipSetDistanceDistance(&minfoFaceChipSetDistanceDistance, 0, &menuFaceChipSetDistanceStartGrind, INFO_LOCATION_PGM);
const SubMenuInfo minfoFaceChipDistance = { "Distance", 20, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackFaceChipDistance(&minfoFaceChipDistance, &menuFaceChipSetDistanceDistance, INFO_LOCATION_PGM);
SubMenuItem menuFaceChipDistance(&minfoFaceChipDistance, &menuBackFaceChipDistance, nullptr, INFO_LOCATION_PGM);
const char enumStrFaceChipParametricStartGrindNotZeroed_0[] = "Zero";
const char enumStrFaceChipParametricStartGrindNotZeroed_1[] = "Ignore";
const char* const enumStrFaceChipParametricStartGrindNotZeroed[]  = { enumStrFaceChipParametricStartGrindNotZeroed_0, enumStrFaceChipParametricStartGrindNotZeroed_1 };
const EnumMenuInfo minfoFaceChipParametricStartGrindNotZeroed = { "NotZeroed", 28, 0xffff, 1, setZeroed, enumStrFaceChipParametricStartGrindNotZeroed };
EnumMenuItem menuFaceChipParametricStartGrindNotZeroed(&minfoFaceChipParametricStartGrindNotZeroed, 0, nullptr, INFO_LOCATION_PGM);
const char enumStrFaceChipParametricStartGrindStart_0[] = "No";
const char enumStrFaceChipParametricStartGrindStart_1[] = "Im Sure";
const char* const enumStrFaceChipParametricStartGrindStart[]  = { enumStrFaceChipParametricStartGrindStart_0, enumStrFaceChipParametricStartGrindStart_1 };
const EnumMenuInfo minfoFaceChipParametricStartGrindStart = { "Start", 27, 0xffff, 1, startFaceChipParametric, enumStrFaceChipParametricStartGrindStart };
EnumMenuItem menuFaceChipParametricStartGrindStart(&minfoFaceChipParametricStartGrindStart, 0, &menuFaceChipParametricStartGrindNotZeroed, INFO_LOCATION_PGM);
const SubMenuInfo minfoFaceChipParametricStartGrind = { "StartGrind", 26, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackFaceChipParametricStartGrind(&minfoFaceChipParametricStartGrind, &menuFaceChipParametricStartGrindStart, INFO_LOCATION_PGM);
SubMenuItem menuFaceChipParametricStartGrind(&minfoFaceChipParametricStartGrind, &menuBackFaceChipParametricStartGrind, nullptr, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoFaceChipParametricChannel = { "Channel", 25, 0xffff, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuFaceChipParametricChannel(&minfoFaceChipParametricChannel, 0, &menuFaceChipParametricStartGrind, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoFaceChipParametricHeight = { "Height", 24, 0xffff, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuFaceChipParametricHeight(&minfoFaceChipParametricHeight, 0, &menuFaceChipParametricChannel, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoFaceChipParametricAngle = { "Angle", 23, 0xffff, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuFaceChipParametricAngle(&minfoFaceChipParametricAngle, 0, &menuFaceChipParametricHeight, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoFaceChipParametricWide = { "Wide", 22, 0xffff, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuFaceChipParametricWide(&minfoFaceChipParametricWide, 0, &menuFaceChipParametricAngle, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoFaceChipParametricThin = { "Thin", 21, 0xffff, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuFaceChipParametricThin(&minfoFaceChipParametricThin, 0, &menuFaceChipParametricWide, INFO_LOCATION_PGM);
const SubMenuInfo minfoFaceChipParametric = { "Parametric", 19, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackFaceChipParametric(&minfoFaceChipParametric, &menuFaceChipParametricThin, INFO_LOCATION_PGM);
SubMenuItem menuFaceChipParametric(&minfoFaceChipParametric, &menuBackFaceChipParametric, &menuFaceChipDistance, INFO_LOCATION_PGM);
const SubMenuInfo minfoFaceChip = { "Face Chip", 4, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackFaceChip(&minfoFaceChip, &menuFaceChipParametric, INFO_LOCATION_PGM);
SubMenuItem menuFaceChip(&minfoFaceChip, &menuBackFaceChip, nullptr, INFO_LOCATION_PGM);
const char enumStrFaceCapillaryStartGrindNotZeroed_0[] = "Zero";
const char enumStrFaceCapillaryStartGrindNotZeroed_1[] = "Ignore";
const char* const enumStrFaceCapillaryStartGrindNotZeroed[]  = { enumStrFaceCapillaryStartGrindNotZeroed_0, enumStrFaceCapillaryStartGrindNotZeroed_1 };
const EnumMenuInfo minfoFaceCapillaryStartGrindNotZeroed = { "NotZeroed", 18, 0xffff, 1, setZeroed, enumStrFaceCapillaryStartGrindNotZeroed };
EnumMenuItem menuFaceCapillaryStartGrindNotZeroed(&minfoFaceCapillaryStartGrindNotZeroed, 0, nullptr, INFO_LOCATION_PGM);
const char enumStrFaceCapillaryStartGrindStart_0[] = "No";
const char enumStrFaceCapillaryStartGrindStart_1[] = "Im Sure";
const char* const enumStrFaceCapillaryStartGrindStart[]  = { enumStrFaceCapillaryStartGrindStart_0, enumStrFaceCapillaryStartGrindStart_1 };
const EnumMenuInfo minfoFaceCapillaryStartGrindStart = { "Start", 17, 0xffff, 1, startFaceCapillary, enumStrFaceCapillaryStartGrindStart };
EnumMenuItem menuFaceCapillaryStartGrindStart(&minfoFaceCapillaryStartGrindStart, 0, &menuFaceCapillaryStartGrindNotZeroed, INFO_LOCATION_PGM);
const SubMenuInfo minfoFaceCapillaryStartGrind = { "StartGrind", 16, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackFaceCapillaryStartGrind(&minfoFaceCapillaryStartGrind, &menuFaceCapillaryStartGrindStart, INFO_LOCATION_PGM);
SubMenuItem menuFaceCapillaryStartGrind(&minfoFaceCapillaryStartGrind, &menuBackFaceCapillaryStartGrind, nullptr, INFO_LOCATION_PGM);
const BooleanMenuInfo minfoFaceCapillaryCapillaryMotor = { "CapillaryMotor", 15, 20, 1, NO_CALLBACK, NAMING_ON_OFF };
BooleanMenuItem menuFaceCapillaryCapillaryMotor(&minfoFaceCapillaryCapillaryMotor, true, &menuFaceCapillaryStartGrind, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoFaceCapillaryDepth = { "Depth", 14, 18, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuFaceCapillaryDepth(&minfoFaceCapillaryDepth, 0, &menuFaceCapillaryCapillaryMotor, INFO_LOCATION_PGM);
const SubMenuInfo minfoFaceCapillary = { "FaceCapillary", 3, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackFaceCapillary(&minfoFaceCapillary, &menuFaceCapillaryDepth, INFO_LOCATION_PGM);
SubMenuItem menuFaceCapillary(&minfoFaceCapillary, &menuBackFaceCapillary, &menuFaceChip, INFO_LOCATION_PGM);
const char enumStrGrindCapillaryStartGrindZeroFirst_0[] = "Zero";
const char enumStrGrindCapillaryStartGrindZeroFirst_1[] = "Ignore";
const char* const enumStrGrindCapillaryStartGrindZeroFirst[]  = { enumStrGrindCapillaryStartGrindZeroFirst_0, enumStrGrindCapillaryStartGrindZeroFirst_1 };
const EnumMenuInfo minfoGrindCapillaryStartGrindZeroFirst = { "NotZeroed", 13, 0xffff, 1, setZeroed, enumStrGrindCapillaryStartGrindZeroFirst };
EnumMenuItem menuGrindCapillaryStartGrindZeroFirst(&minfoGrindCapillaryStartGrindZeroFirst, 0, nullptr, INFO_LOCATION_PGM);
const char enumStrGrindCapillaryStartGrindStart_0[] = "No";
const char enumStrGrindCapillaryStartGrindStart_1[] = "Im Sure";
const char* const enumStrGrindCapillaryStartGrindStart[]  = { enumStrGrindCapillaryStartGrindStart_0, enumStrGrindCapillaryStartGrindStart_1 };
const EnumMenuInfo minfoGrindCapillaryStartGrindStart = { "Start", 12, 0xffff, 1, startGrindCapillary, enumStrGrindCapillaryStartGrindStart };
EnumMenuItem menuGrindCapillaryStartGrindStart(&minfoGrindCapillaryStartGrindStart, 0, &menuGrindCapillaryStartGrindZeroFirst, INFO_LOCATION_PGM);
const SubMenuInfo minfoGrindCapillaryStartGrind = { "StartGrind", 11, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackGrindCapillaryStartGrind(&minfoGrindCapillaryStartGrind, &menuGrindCapillaryStartGrindStart, INFO_LOCATION_PGM);
SubMenuItem menuGrindCapillaryStartGrind(&minfoGrindCapillaryStartGrind, &menuBackGrindCapillaryStartGrind, nullptr, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoGrindCapillaryFaceWidth = { "FaceWidth", 10, 16, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuGrindCapillaryFaceWidth(&minfoGrindCapillaryFaceWidth, 0, &menuGrindCapillaryStartGrind, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoGrindCapillaryAngleDegrees = { "AngleDegrees", 9, 14, 9000, NO_CALLBACK, 0, 100, "d" };
AnalogMenuItem menuGrindCapillaryAngleDegrees(&minfoGrindCapillaryAngleDegrees, 0, &menuGrindCapillaryFaceWidth, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoGrindCapillaryOuterDiameter = { "OuterDiameter", 8, 12, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuGrindCapillaryOuterDiameter(&minfoGrindCapillaryOuterDiameter, 0, &menuGrindCapillaryAngleDegrees, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoGrindCapillaryInnerDiameter = { "InnerDiameter", 7, 10, 1000, NO_CALLBACK, 0, 10, "um" };
AnalogMenuItem menuGrindCapillaryInnerDiameter(&minfoGrindCapillaryInnerDiameter, 0, &menuGrindCapillaryOuterDiameter, INFO_LOCATION_PGM);
const SubMenuInfo minfoGrindCapillary = { "GrindCapillary", 2, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackGrindCapillary(&minfoGrindCapillary, &menuGrindCapillaryInnerDiameter, INFO_LOCATION_PGM);
SubMenuItem menuGrindCapillary(&minfoGrindCapillary, &menuBackGrindCapillary, &menuFaceCapillary, INFO_LOCATION_PGM);
const AnyMenuInfo minfoCalibrateZero = { "Zero", 6, 0xffff, 0, CalibrateZero };
ActionMenuItem menuCalibrateZero(&minfoCalibrateZero, nullptr, INFO_LOCATION_PGM);
const AnyMenuInfo minfoCalibrateOffset = { "Offset", 5, 2, 0, moveOffset };
EditableLargeNumberMenuItem menuCalibrateOffset(&minfoCalibrateOffset, LargeFixedNumber(4, 0, 0U, 0U, false), true, &menuCalibrateZero, INFO_LOCATION_PGM);
const SubMenuInfo minfoCalibrate = { "Calibrate", 1, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackCalibrate(&minfoCalibrate, &menuCalibrateOffset, INFO_LOCATION_PGM);
SubMenuItem menuCalibrate(&minfoCalibrate, &menuBackCalibrate, &menuGrindCapillary, INFO_LOCATION_PGM);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    setSizeBasedEEPROMStorageEnabled(true);
    menuMgr.setEepromRef(&glArduinoEeprom);
    // Now add any readonly, non-remote and visible flags.
    menuFaceChipParametricStartGrindStart.setVisible(false);
    menuFaceChipSetDistanceStartGrindStart.setVisible(false);
    menuGrindCapillaryStartGrindStart.setVisible(false);
    menuFaceCapillaryStartGrindStart.setVisible(false);

    // Code generated by plugins.
    Wire.begin();
    lcd.setIoAbstraction(ioFrom8574(0x27, 0xff, &Wire));
    lcd.begin(16, 2);
    renderer.setUpdatesPerSecond(10);
    lcd.configureBacklightPin(3);
    lcd.backlight();
    switches.init(internalDigitalIo(), SWITCHES_POLL_EVERYTHING, true);
    menuMgr.initForEncoder(&renderer, &menuCalibrate, 2, 3, 8);
    remoteServer.addConnection(&serialConnection);
}

