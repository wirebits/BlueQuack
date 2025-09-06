/*
 * BlueQuack
 * A classic bluetooth-controlled USB Rubber Ducky clone built with ESP32 boards.
 * Author - WireBits
*/

#include "FS.h"
#include "SD.h"
#include "run.h"
#include "SPI.h"
#include "view.h"
#include "settings.h"
#include <BleKeyboard.h>
#include <Preferences.h>

#define SD_CS 5
File scriptFile;
const int ledPin = 2;

Preferences prefs;
String keyboardName;
BleKeyboard* bleKeyboard;

const char* defaultName = "BlueQuack";

void showHelp() {
  Serial.println("\nAvailable Commands:");
  Serial.println("  payload N                  - Run payload-N.txt from SD card (N = number)");
  Serial.println("  view N                     - Show contents of payload-N.txt");
  Serial.println("  list                       - Show all payload files in SD card");
  Serial.println("  mute                       - Mute system sound");
  Serial.println("  unmute                     - Unmute system sound");
  Serial.println("  name <NEW_KEYBOARD_NAME>   - Change BLE keyboard name and restart");
  Serial.println("  reset name                 - Reset keyboard name to default and restart");
  Serial.println("  help                       - Show this help message\n");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  prefs.begin("blekbd", false);
  keyboardName = getKeyboardName();
  Serial.print("[*] Keyboard Name: ");
  Serial.println(keyboardName);
  bleKeyboard = new BleKeyboard(keyboardName.c_str(), "Espressif", 100);
  bleKeyboard->begin();
  Serial.println("[*] Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("[!] Card Mount Failed!");
    return;
  }
  if (SD.cardType() == CARD_NONE) {
    Serial.println("[!] No SD card attached!");
    return;
  }
  Serial.println("[*] SD card ready!");
}

void loop() {
  if (bleKeyboard->isConnected()) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command.startsWith("payload ")) {
      String num = command.substring(8);
      String filename = "/payload-" + num + ".txt";
      Serial.print("[*] Executing: ");
      Serial.println(filename);
      if (SD.exists(filename)) {
        runPayload(filename);
      } else {
        Serial.println("[!] File not found!");
      }
    }
    else if (command.startsWith("view ")) {
      String num = command.substring(5);
      String filename = "/payload-" + num + ".txt";
      Serial.print("[*] Viewing: ");
      Serial.println(filename);
      if (SD.exists(filename)) {
        viewFile(filename);
      } else {
        Serial.println("[!] File not found!");
      }
    }
    else if (command == "mute") {
      Serial.println("[*] Muting system sound...");
      bleKeyboard->releaseAll();  
      bleKeyboard->write(KEY_MEDIA_MUTE);
    }
    else if (command == "unmute") {
      Serial.println("[*] Unmuting system sound...");
      bleKeyboard->releaseAll();  
      bleKeyboard->write(KEY_MEDIA_MUTE);
    }
    else if (command.startsWith("name ")) {
      String newName = command.substring(5);
      newName.trim();
      setKeyboardName(newName);
    }
    else if (command.equalsIgnoreCase("reset name")) {
      resetKeyboardName();
    }
    else if (command == "help") {
      showHelp();
    }
    else if (command == "list") {
      listDir(SD, "/", 0);
    }
  }
}
