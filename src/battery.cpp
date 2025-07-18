#include "battery.h"

// #define VBAT_Read 1
// #define ADC_Ctrl 37


// PWM settings
const int freq = 5000; // PWM frequency
const int resolution = 12; // PWM resolution (bits)
const int channel = 0; // PWM channel

void Battery::setup()
{

    // ledcSetup(channel, freq, resolution);
    // analogSetAttenuation(ADC_0db);


    // pinMode(CHARGE_STATUS_PIN, INPUT);
    // pinMode(BATTERY_VOLTAGE_PIN, INPUT);
    
//    analogReadResolution(12);
//    analogSetAttenuation(ADC_11db);


//    adcAttachPin(BATTERY_VOLTAGE_PIN);
//    analogReadResolution(12);
    mVoltage = readBatteryVoltage();
}

int Battery::getPercentage()
{    
    const float min = 3.0;
    const float max = 4.2;

    readBatteryVoltage();

    // float voltage = getVoltage();
    int percent = floor(((mVoltage - min) / (max - min)) * 100);

    // Serial.printf("RAW BAT: percent: %d%% volts: %.2f\n", percent, mVoltage);

    if (percent < 0)
        percent = 0;
    if (percent > 100)
        percent = 100;
    return percent;
}

bool Battery::isCharging()
{
    return false;
 //   return digitalRead(CHARGE_STATUS_PIN) == HIGH;
}


Battery::Battery()
{
    // return;
    // pinMode(ADC_Ctrl, OUTPUT);
    // pinMode(VBAT_Read, INPUT);
}

float Battery::getVoltage()
{
    readBatteryVoltage();
    return mVoltage;
}

float Battery::readBatteryVoltage()
{
    return 4.0f;
    // ADC resolution
    const int resolution = 12;
    const int adcMax = pow(2, resolution) - 1;
    const float adcMaxVoltage = 3.3f;
    // On-board voltage divider
    const int R1 = 100;
    const int R2 = 100;
    // Calibration measurements
    const float measuredVoltage = 4.2f;
    const float reportedVoltage = 4.2f;

    // const float reportedVoltage = 3.88;
    // const float reportedVoltage = 4.095;
    // Calibration factor
    const float factor = (adcMaxVoltage / adcMax) * ((R1 + R2) / (float)R2) * (measuredVoltage / reportedVoltage);

    if (millis() - lastRead > 5000)
    {
       // digitalWrite(ADC_Ctrl, HIGH);
      //  delay(100);
       // int analogValue = analogRead(BATTERY_VOLTAGE_PIN);
        uint32_t analogValue = analogReadMilliVolts(BATTERY_VOLTAGE_PIN); // Read the voltage in millivolts


        Serial.printf("[readBatteryVoltage] : %lu\n", analogValue);


       // digitalWrite(ADC_Ctrl, LOW);

        float floatVoltage = factor * analogValue * 100 / 5.45f;
        // uint16_t voltage = (int)(floatVoltage * 1000.0);

        // // Serial.print("[readBatteryVoltage] ADC : ");
        // // Serial.println(analogValue);
        // // Serial.print("[readBatteryVoltage] Float : ");
        // // Serial.println(floatVoltage, 3);
        // Serial.print("[readBatteryVoltage] milliVolts : ");
        // Serial.println(voltage);

        //  delay(1000);

        mVoltage = floatVoltage;
        lastRead = millis();
    }

    return mVoltage;
}