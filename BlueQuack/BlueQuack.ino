/*
 * BlueQuack
 * A classic bluetooth-controlled USB Rubber Ducky clone built with ESP32 boards.
 * Author - WireBits
*/

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <BleKeyboard.h>
#include <Preferences.h>

#define SD_CS 5
File scriptFile;
const int ledPin = 2;

Preferences prefs;
String keyboardName;
BleKeyboard* bleKeyboard;

const char* defaultName = "BlueQuack";

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("[*] Listing directory: %s\n", dirname);
  File root = fs.open(dirname);
  if (!root || !root.isDirectory()) {
    Serial.println("[!] Failed to open directory!");
    return;
  }
  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) listDir(fs, file.name(), levels - 1);
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void executeBlock(const String &block) {
  int start = 0;
  while (true) {
    int nl = block.indexOf('\n', start);
    String line = (nl == -1) ? block.substring(start) : block.substring(start, nl);
    line.trim();
    if (line.length() > 0) {
      scriptFileLines(line);
    }
    if (nl == -1) break;
    start = nl + 1;
  }
}

void runPayload(String path) {
  File f = SD.open(path);
  if (!f) {
    Serial.println("[!] Failed to open payload file!");
    return;
  }
  String line = "";
  bool inLoop = false;
  bool infiniteLoop = false;
  long loopCount = 0;
  String loopBody = "";
  while (f.available()) {
    char c = f.read();
    if (c == '\n') {
      line.trim();
      if (line.length() > 0) {
        String u = line; 
        u.toUpperCase();
        if (!inLoop) {
          if (u.startsWith("LOOP")) {
            int sp = line.indexOf(' ');
            String nstr = (sp == -1) ? "" : line.substring(sp + 1);
            nstr.trim();
            loopCount = nstr.toInt();
            inLoop = true;
            infiniteLoop = false;
            loopBody = "";
          } 
          else if (u == "INF") {
            inLoop = true;
            infiniteLoop = true;
            loopBody = "";
          }
          else {
            scriptFileLines(line);
          }
        } 
        else {
          if (u == "EXIT") {
            if (infiniteLoop) {
              while (true) {
                executeBlock(loopBody);
                delay(50);
              }
            } else {
              for (long i = 0; i < loopCount; i++) {
                executeBlock(loopBody);
              }
            }
            inLoop = false;
            infiniteLoop = false;
            loopCount = 0;
            loopBody = "";
          } else {
            loopBody += line;
            loopBody += '\n';
          }
        }
      }
      line = "";
    } else if ((int)c != 13) {
      line += c;
    }
  }
  line.trim();
  if (line.length() > 0) {
    String u = line; u.toUpperCase();
    if (!inLoop) {
      if (u.startsWith("LOOP") || u == "INF") {
        return;
      } else if (u == "EXIT") {
        return;
      } else {
        scriptFileLines(line);
      }
    } else {
      if (u == "EXIT") {
        if (infiniteLoop) {
          while (true) {
            executeBlock(loopBody);
            delay(50);
          }
        } else {
          for (long i = 0; i < loopCount; i++) {
            executeBlock(loopBody);
          }
        }
        inLoop = false;
      } else {
        return;
      }
    }
  }
  if (inLoop) {
    return;
  }
  f.close();
}

void viewFile(String path) {
  File file = SD.open(path);
  if (!file) {
    Serial.println("[!] Failed to open file!");
    return;
  }
  Serial.println("------------------------------");
  while (file.available()) {
    Serial.write(file.read());
  }
  Serial.println("\n------------------------------");
  file.close();
}

void scriptFileLines(String lines) {
  int space_1 = lines.indexOf(" ");
  String cmd = (space_1 == -1) ? lines : lines.substring(0, space_1);
  String arg = (space_1 == -1) ? "" : lines.substring(space_1 + 1);
  String ucmd = cmd; 
  ucmd.toUpperCase();
  if (ucmd == "TYPE") {
    if (arg.endsWith("-")) {
      arg.remove(arg.length() - 1);
      for (int i = 0; i < arg.length(); i++) {
        bleKeyboard->print(String(arg[i]));
        delay(30);
      }
      bleKeyboard->write(KEY_RETURN);
    } else {
      for (int i = 0; i < arg.length(); i++) {
        bleKeyboard->print(String(arg[i]));
        delay(30);
      }
    }
  } 
  else if (ucmd == "WAIT") {
    delay(arg.toInt());
  } 
  else if (ucmd == "EXIT" || ucmd == "LOOP") {
    return;
  } 
  else {
    pressKeys(lines);
  }
  bleKeyboard->releaseAll();
}

char toLowerCase(char keyChar) {
  return (keyChar >= 'A' && keyChar <= 'Z') ? keyChar + ('a' - 'A') : keyChar;
}

void pressKeys(String keys) {
  int space_1 = keys.indexOf(" ");
  while (space_1 != -1) {
    String key = keys.substring(0, space_1);
    pressKey(key);
    keys = keys.substring(space_1 + 1);
    space_1 = keys.indexOf(" ");
  }
  pressKey(keys);
}

void pressKey(String b) {
  struct KeyMap {
    const char* name;
    uint8_t key;
  } keyMap[] = {
    {"ENTER", KEY_RETURN}, {"CTRL", KEY_LEFT_CTRL}, {"SHIFT", KEY_LEFT_SHIFT},
    {"ALT", KEY_LEFT_ALT}, {"GUI", KEY_LEFT_GUI}, {"UP", KEY_UP_ARROW},
    {"DOWN", KEY_DOWN_ARROW}, {"LEFT", KEY_LEFT_ARROW}, {"RIGHT", KEY_RIGHT_ARROW},
    {"DELETE", KEY_DELETE}, {"PAGEUP", KEY_PAGE_UP}, {"PAGEDOWN", KEY_PAGE_DOWN},
    {"HOME", KEY_HOME}, {"ESC", KEY_ESC}, {"INSERT", KEY_INSERT},
    {"TAB", KEY_TAB}, {"END", KEY_END}, {"CAPSLOCK", KEY_CAPS_LOCK},
    {"F1", KEY_F1}, {"F2", KEY_F2}, {"F3", KEY_F3}, {"F4", KEY_F4},
    {"F5", KEY_F5}, {"F6", KEY_F6}, {"F7", KEY_F7}, {"F8", KEY_F8},
    {"F9", KEY_F9}, {"F10", KEY_F10}, {"F11", KEY_F11}, {"F12", KEY_F12},
    {"SPACE", ' '}
  };
  if (b.length() == 1) {
    bleKeyboard->press(toLowerCase(b[0]));
    return;
  }
  for (auto& k : keyMap) {
    if (b.equalsIgnoreCase(k.name)) {
      bleKeyboard->press(k.key);
      return;
    }
  }
}

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
  keyboardName = prefs.getString("kbdName", defaultName);
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
      if (newName.length() > 0) {
        prefs.putString("kbdName", newName);
        Serial.print("[*] Keyboard name set to: ");
        Serial.println(newName);
        Serial.println("[*] Restarting ESP32...");
        ESP.restart();
      }
    }
    else if (command.equalsIgnoreCase("reset name")) {
      prefs.putString("kbdName", defaultName);
      Serial.println("[*] Keyboard name reset to default (BlueQuack)");
      Serial.println("[*] Restarting ESP32...");
      ESP.restart();
    }
    else if (command == "help") {
      showHelp();
    }
    else if (command == "list") {
      listDir(SD, "/", 0);
    }
  }
}
