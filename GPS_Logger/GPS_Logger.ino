/*
 * Logs GPS data (or other serial data) to an SD card.
 * Made by MrTijn/Tijndagamer
 * Copyright (c) 2016
 * Released under the MIT license
 */

#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

const int rxPin = 8;
const int txPin = 9;
const int warningLEDPin = 3;
const int successLEDPin = 4;
const int batteryMonitorPin = 1; // Analog pin for monitoring the battery input
const float inputVoltage = 3.3;
const float batteryMinVoltage = 2.30;
float voltsPerUnit;
SoftwareSerial inputSerial(rxPin, txPin);
File log_file;

void setup() {
    // First only setup necessary components to perform a battery check
    // Serial
    Serial.begin(9600);

    // Pins
    pinMode(warningLEDPin, OUTPUT);
    pinMode(batteryMonitorPin, INPUT);

    // Perform actual check
    voltsPerUnit = inputVoltage / 1024.0;
    Serial.println("Battery setup: ");
    if (!checkBattery()) {
        Serial.println("ERROR");
        blinkLED(warningLEDPin);
    } else {
        Serial.println("OK");
    }

    // Setup everything else
    // Serial
    inputSerial.begin(9600);

    // Pins
    pinMode(successLEDPin, OUTPUT);

    // SD init
    Serial.print("SD setup: ");
    if(!SD.begin(10)) {
        Serial.println("ERROR");
        digitalWrite(warningLEDPin, HIGH);
        return;
    }
    Serial.println("OK");
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

// Returns true if the connected batteries have sufficient charge left
bool checkBattery() {
    int analogValue = analogRead(batteryMonitorPin);
    float voltage = analogValue * voltsPerUnit;
    Serial.print("Battery voltage: ");
    Serial.println(voltage);
    if (voltage >= batteryMinVoltage) {
        return true;
    } else {
        return false;
    }
}

void blinkLED(int pin) {
    while (true) {
        digitalWrite(pin, HIGH);
        delay(250);
        digitalWrite(pin, LOW);
        delay(250);
    }
}
