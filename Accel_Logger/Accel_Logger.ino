/*
 * Logs accelerometer data to an SD card.
 * Made by MrTijn
 * Copyright (c) 2016
 * Released under the MIT license
 */

#include <SPI.h>
#include <SD.h>
#include <ADXL335.h>

File log_file;

ADXL335 adxl335(A0, A1, A2, 3.3);
const int chipSelect = 10;

void setup() {
    Serial.begin(9600);
    Serial.println("init sd"); 
    if(!SD.begin(10)) {
        Serial.println("init failed");
        return;
    }
    Serial.println("init succes");
    log_file = SD.open("accel.log", FILE_WRITE);
    log_file.println("Starting log");
    log_file.close();
}

void loop() {
    Serial.println("Writing data...");
    log_file = SD.open("accel.log", FILE_WRITE);
    log_file.print(adxl335.readX());
    log_file.print("\t");
    log_file.print(adxl335.readY());
    log_file.print("\t");
    log_file.print(adxl335.readZ());
    log_file.print("\t");
    log_file.println();
    log_file.close();
    Serial.println("Sleeping...");
    delay(1000);
}
