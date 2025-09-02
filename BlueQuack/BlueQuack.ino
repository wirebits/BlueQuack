/*
 * BlueQuack
 * A classic bluetooth-controlled USB Rubber Ducky clone built with ESP32 board.
 * Author - WireBits
*/

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <BleKeyboard.h>

char keyboard_name[] = "BlueQuack";
BleKeyboard bleKeyboard(keyboard_name, "Espressif", 100);

#define SD_CS 5
File scriptFile;

char toLowerCase(char keyChar) {
  return (keyChar >= 'A' && keyChar <= 'Z') ? keyChar + ('a' - 'A') : keyChar;
}

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();

  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }

  if (SD.cardType() == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.println("SD card ready.");
  listDir(SD, "/", 0);

  Serial.println("Waiting for serial commands...");
  Serial.println("Example: payload 1");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("payload ")) {
      String num = command.substring(8);
      String filename = "/payload" + num + ".txt";
      Serial.print("Executing: ");
      Serial.println(filename);

      if (SD.exists(filename)) {
        runPayload(filename);
      } else {
        Serial.println("File not found.");
      }
    }
  }
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root || !root.isDirectory()) {
    Serial.println("Failed to open directory");
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

void runPayload(String path) {
  File scriptFile = SD.open(path);
  if (!scriptFile) {
    Serial.println("Failed to open payload file");
    return;
  }

  String line = "";
  while (scriptFile.available()) {
    char m = scriptFile.read();
    if (m == '\n') {
      scriptFileLines(line);
      line = "";
    } else if ((int)m != 13) {
      line += m;
    }
  }
  if (line.length() > 0) scriptFileLines(line);
  scriptFile.close();
}

void scriptFileLines(String lines) {
  int space_1 = lines.indexOf(" ");
  String cmd = (space_1 == -1) ? lines : lines.substring(0, space_1);
  String arg = (space_1 == -1) ? "" : lines.substring(space_1 + 1);

  if (cmd == "TYPE") {
    bleKeyboard.print(arg);
  } else if (cmd == "WAIT") {
    delay(arg.toInt());
  } else {
    pressKeys(lines);
  }
  bleKeyboard.releaseAll();
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
    bleKeyboard.press(toLowerCase(b[0]));
    return;
  }

  for (auto& k : keyMap) {
    if (b.equals(k.name)) {
      bleKeyboard.press(k.key);
      return;
    }
  }
}