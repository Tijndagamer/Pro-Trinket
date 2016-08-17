/*
 * Simple program to read the data from an ADXL335.
 * It also calculates the actual voltage (based on the given reference voltage)
 * and calculates the acceleration based on this voltage.
 * 
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license.
 */

const float ANALOG_REFERENCE_VOLTAGE = 3.3;
const int xpin = A0;
const int ypin = A1;
const int zpin = A2;

const float zero_g_voltage_x_and_y = 1.6;
const float zero_g_voltage_z = 1.67;
const float volts_per_g = 0.330;

const float calibration_offset_x_y = -0.045;
const float calibration_offset_z = -0.05;

float volts_per_unit;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting ADXL335 reader...");
  volts_per_unit = ANALOG_REFERENCE_VOLTAGE / 1024;
  Serial.print("Volts/unit: ");
  Serial.println(volts_per_unit);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
}

void loop() {
  // print the sensor values:
  Serial.print(calculateAcceleration(xpin));
  Serial.print("\t");
  Serial.print(calculateAcceleration(ypin));
  Serial.print("\t");
  Serial.print(calculateAcceleration(zpin));
  Serial.println();

  delay(500);
}

float readVoltage(int pin) {
  int rawVoltage = analogRead(pin);
  float voltage = rawVoltage * volts_per_unit;
  return voltage;
}

float calculateAcceleration(int pin) {
  float zero_g_voltage, calibration_offset;
  if (pin == zpin) { 
    zero_g_voltage = zero_g_voltage_z;
    calibration_offset = calibration_offset_z;
  }
  else {
    zero_g_voltage = zero_g_voltage_x_and_y;
    calibration_offset = calibration_offset_x_y;
  }
  float voltage = readVoltage(pin);
  
  float adjusted_voltage = voltage - zero_g_voltage;
  // Calculate acceleration in g
  float acceleration = (adjusted_voltage / volts_per_g);
  return acceleration + calibration_offset;
}

