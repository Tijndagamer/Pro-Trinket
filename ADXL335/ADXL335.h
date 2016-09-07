/*
 * ADXL335.h - A library to easily read a ADXL335 sensor.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license
 */

#ifndef ADXL335_h
#define ADXL335_h

#include "Arduino.h"

class ADXL335
{
    public:
        ADXL335(int xpin, int ypin, int zpin, float vref);
        float readX();
        float readY();
        float readZ();
    private:
        int _xpin;
        int _ypin;
        int _zpin;
        float _vref; // not sure if needed
        float _volts_per_unit;

        // Constants from the datasheet
        const float ZERO_G_VOLTAGE_XY = 1.6;
        const float ZERO_G_VOLTAGE_Z = 1.67;
        const float VOLTS_PER_G = 0.330;

        // Calibration values
        const float CALIBRATION_OFFSET_X = 0.0;
        const float CALIBRATION_OFFSET_Y = 0.0;
        const float CALIBRATION_OFFSET_Z = 0.0;

        // Methods        
        float readVoltage(int pin);
        float calculateAcceleration(int pin, float zero_g_voltage, float calibration_offset);        
};

#endif
