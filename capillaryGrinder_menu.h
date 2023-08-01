/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#ifndef MENU_GENERATED_CODE_H
#define MENU_GENERATED_CODE_H

#include <Arduino.h>
#include <tcMenu.h>
#include <Wire.h>
#include <LiquidCrystalIO.h>
#include <IoAbstractionWire.h>
#include <RemoteConnector.h>
#include "SerialTransport.h"
#include <RuntimeMenuItem.h>
#include <EditableLargeNumberMenuItem.h>
#include <IoAbstraction.h>
#include <EepromItemStorage.h>
#include <ArduinoEEPROMAbstraction.h>
#include "tcMenuLiquidCrystal.h"

// variables we declare that you may need to access
extern const PROGMEM ConnectorLocalInfo applicationInfo;
extern TcMenuRemoteServer remoteServer;
extern LiquidCrystal lcd;
extern LiquidCrystalRenderer renderer;

// Any externals needed by IO expanders, EEPROMs etc


// Global Menu Item exports
extern EnumMenuItem menuFaceChipSetDistanceStartGrindNotZeroed;
extern EnumMenuItem menuFaceChipSetDistanceStartGrindStart;
extern BackMenuItem menuBackFaceChipSetDistanceStartGrind;
extern SubMenuItem menuFaceChipSetDistanceStartGrind;
extern AnalogMenuItem menuFaceChipSetDistanceDistance;
extern BackMenuItem menuBackFaceChipSetDistance;
extern SubMenuItem menuFaceChipSetDistance;
extern EnumMenuItem menuFaceChipParametricStartGrindNotZeroed;
extern EnumMenuItem menuFaceChipParametricStartGrindStart;
extern BackMenuItem menuBackFaceChipParametricStartGrind;
extern SubMenuItem menuFaceChipParametricStartGrind;
extern AnalogMenuItem menuFaceChipParametricChannel;
extern AnalogMenuItem menuFaceChipParametricHeight;
extern AnalogMenuItem menuFaceChipParametricAngle;
extern AnalogMenuItem menuFaceChipParametricWide;
extern AnalogMenuItem menuFaceChipParametricThin;
extern BackMenuItem menuBackFaceChipParametric;
extern SubMenuItem menuFaceChipParametric;
extern BackMenuItem menuBackFaceChip;
extern SubMenuItem menuFaceChip;
extern EnumMenuItem menuFaceCapillaryStartGrindNotZeroed;
extern EnumMenuItem menuFaceCapillaryStartGrindStart;
extern BackMenuItem menuBackFaceCapillaryStartGrind;
extern SubMenuItem menuFaceCapillaryStartGrind;
extern BooleanMenuItem menuFaceCapillaryCapillaryMotor;
extern AnalogMenuItem menuFaceCapillaryDepth;
extern BackMenuItem menuBackFaceCapillary;
extern SubMenuItem menuFaceCapillary;
extern EnumMenuItem menuGrindCapillaryStartGrindZeroFirst;
extern EnumMenuItem menuGrindCapillaryStartGrindStart;
extern BackMenuItem menuBackGrindCapillaryStartGrind;
extern SubMenuItem menuGrindCapillaryStartGrind;
extern AnalogMenuItem menuGrindCapillaryFaceWidth;
extern AnalogMenuItem menuGrindCapillaryAngleDegrees;
extern AnalogMenuItem menuGrindCapillaryOuterDiameter;
extern AnalogMenuItem menuGrindCapillaryInnerDiameter;
extern BackMenuItem menuBackGrindCapillary;
extern SubMenuItem menuGrindCapillary;
extern ActionMenuItem menuCalibrateZero;
extern EditableLargeNumberMenuItem menuCalibrateOffset;
extern BackMenuItem menuBackCalibrate;
extern SubMenuItem menuCalibrate;

// Provide a wrapper to get hold of the root menu item and export setupMenu
inline MenuItem& rootMenuItem() { return menuCalibrate; }
void setupMenu();

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

void CALLBACK_FUNCTION checkZeroed(int id);
void CALLBACK_FUNCTION moveOffset(int id);
void CALLBACK_FUNCTION setZero(int id);
void CALLBACK_FUNCTION startFaceCapillary(int id);
void CALLBACK_FUNCTION startFaceChipDistance(int id);
void CALLBACK_FUNCTION startFaceChipParametric(int id);
void CALLBACK_FUNCTION startGrindCapillary(int id);

#endif // MENU_GENERATED_CODE_H
