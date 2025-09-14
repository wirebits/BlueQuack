/*
 * Settings CPP File
 * Author - WireBits
 */

#include "settings.h"

String getKeyboardName() {
    return prefs.getString("kbdName", defaultName);
}

void setKeyboardName(const String& newName) {
    if (newName.length() > 0) {
        prefs.putString("kbdName", newName);
        Serial.print("[*] Keyboard name set to: ");
        Serial.println(newName);
        Serial.println("[*] Restarting ESP32...");
        ESP.restart();
    } else {
        Serial.println("[!] Invalid name. No changes made.");
    }
}

void resetKeyboardName() {
    prefs.putString("kbdName", defaultName);
    Serial.print("[*] Keyboard name reset to default (");
    Serial.print(defaultName);
    Serial.println(")");
    Serial.println("[*] Restarting ESP32...");
    ESP.restart();

}
