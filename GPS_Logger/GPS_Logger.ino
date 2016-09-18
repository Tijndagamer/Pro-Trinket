/*
 * Logs GPS data (or other serial data) to an SD card.
 * Made by MrTijn/Tijndagamer
 * Copyright (c) 2016
 * Released under the MIT license
 */

#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

File log_file;
const int rxPin = 8;
const int txPin = 9;
const int warningLEDPin = 3;
const int successLEDPin = 4;
SoftwareSerial inputSerial(rxPin, txPin);

void setup() {
    Serial.begin(9600);
    inputSerial.begin(9600);
    pinMode(warningLEDPin, OUTPUT);
    pinMode(successLEDPin, OUTPUT);
    if(!SD.begin(10)) {
        Serial.println("SD init failed.");
        digitalWrite(warningLEDPin, HIGH);
        return;
    }
    Serial.println("SD init succes");
    digitalWrite(successLEDPin, HIGH);
    log_file = SD.open("gps.log", FILE_WRITE);
    log_file.println("Starting GPS log...");
    log_file.close();
}

void loop() {
    if (inputSerial.available()) {
        log_file = SD.open("gps.log", FILE_WRITE);
        if (log_file) {
            String buffer = inputSerial.readStringUntil('\n');
            log_file.print(buffer);
            //Serial.println(buffer);
            log_file.close();
        } else {
            Serial.println("File error.");
            digitalWrite(warningLEDPin, HIGH);
            digitalWrite(successLEDPin, LOW);
        }
    }
}
