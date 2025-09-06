/*
 * View Header File
 * Author - WireBits
 */

#ifndef VIEW_H
#define VIEW_H

#include <Arduino.h>
#include <FS.h>
#include <SD.h>

void viewFile(String path);

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

#endif