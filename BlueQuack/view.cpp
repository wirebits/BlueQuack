/*
 * View CPP File
 * Author - WireBits
 */

#include "view.h"

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