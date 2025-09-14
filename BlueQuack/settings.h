/*
 * Settings Header File
 * Author - WireBits
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>

extern Preferences prefs;
extern const char* defaultName;

String getKeyboardName();

void setKeyboardName(const String& newName);

void resetKeyboardName();


#endif
