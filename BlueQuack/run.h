/*
 * Run Header File
 * Author - WireBits
 */

#ifndef RUN_H
#define RUN_H

#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
#include <BleKeyboard.h>

extern BleKeyboard* bleKeyboard;
extern File scriptFile;

void runPayload(String path);

void scriptFileLines(String lines);
void executeBlock(const String &block);
void pressKeys(String keys);
void pressKey(String b);

#endif