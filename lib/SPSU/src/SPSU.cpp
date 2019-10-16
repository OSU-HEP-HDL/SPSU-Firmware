/**
 * @Author: Steven Welch <welchsteven>
 * @Date:   2018-08-13T19:08:48-06:00
 * @Email:  WelchSteven@gmail.com
 * @Project: SPSU
 * @Filename: SPSU.cpp
 * @Last modified by:   steven
 * @Last modified time: 2018-12-12T14:11:47-07:00
 */



#include "SPSU.h"
#include <OPC.h>

/**
   @brief "Description"
   @param "Param description"
   @pre "Pre-conditions"
   @post "Post-conditions"
   @return "Returns 0 if successful"
*/
bool SPSU::begin()
{
    pinMode(ShutdownPin, OUTPUT);
    pinMode(CurrentAdjust, OUTPUT);
    pinMode(CurrentSense, INPUT);
    pinMode(CurrentSense10, INPUT);
    pinMode(VoltageSense, INPUT);
    pinMode(VFB, INPUT);
    digitalWrite(ShutdownPin, LOW);
    analogWrite(CurrentAdjust, 0);
    if (analogRead(VoltageSense)==0)
        return EXIT_SUCCESS;
    else return EXIT_FAILURE;
}
bool SPSU::shutdown()
{
    digitalWrite(ShutdownPin, LOW);
    analogWrite(CurrentAdjust, 0);
    if (analogRead(VoltageSense)==0)
        return EXIT_SUCCESS;
    else return EXIT_FAILURE;
}

bool SPSU::startUp()
{
    digitalWrite(ShutdownPin, HIGH);
    analogWrite(CurrentAdjust, 0);
    if (analogRead(VoltageSense)==0)
        return EXIT_SUCCESS;
    else return EXIT_FAILURE;
}

/**
   @brief "Description"
   @param "Param description"
   @pre "Pre-conditions"
   @post "Post-conditions"
   @return "Returns 0 if successful"
*/
float SPSU::getCurrent()
{
    float sensorValue;
    float voltage;
    float current;
    sensorValue = analogRead(CurrentSense);
    voltage  = sensorValue * (Reference / 1023.0);
    current = voltage / currentSenseResistance;
    LOG("Current: %u", current);
    return current;
}

/*********************************************************************
* Comment
*********************************************************************/
bool SPSU::setCurrent(float current)
{
    if(current>8) // Don't burn chips
        return EXIT_FAILURE;

        int analogValue; // CurrentAdjust value to be written into DigitalPin9 ("CurrentAdjust")

        // I = k * (V_max/255) * CurrentAdjust * (R26/(R25+R26)) / R27
        // k - adjustment coefficient, there is 11% difference between the expected and measured currents
        // k actually depends on current. Reffer to https://indico.cern.ch/event/796792/ OSU_HW_Egor slodes
        // V_max = 5V
        // CurrentAdjust = 0-255 (int)
        // R25 = 300k, R26 = 10k, R27 = 0.01
        // Thus CurrentAdjust = I * R27 / ( (V_max/255) * (R26/(R25+R26)) )

        double V_max = 5.;
        double r25 = 300000, r26 = 10000, r27 = .01;
        double k;
        if (current <= 0.25)                  k = 1;
        if (current > 0.25 && current <= 0.5) k = 0.97;
        if (current > 0.7  && current <= 1.0) k = 0.93;
        if (current > 1.0  && current <= 1.5) k = 0.91;
        if (current > 1.5  && current <= 2.9) k = 0.9;
        if (current > 2.9)                    k = 0.89;

        analogValue = (current * r27) / ( (V_max/255) * (r26/(r25+r26)) * k );

        // And now write the analogValue to set requisted current
        analogWrite(CurrentAdjust, analogValue);
        return EXIT_SUCCESS;
}

/*********************************************************************
* Comment
*********************************************************************/
float SPSU::getVoltage()
{
    float sensorValue;
    float voltage;
    sensorValue = analogRead(VoltageSense);
    voltage  = sensorValue * (Reference / 1023.0);
    LOG("Voltage: %u", voltage);
    return voltage;
}

/*********************************************************************
* Comment
*********************************************************************/
bool SPSU::setVoltage(float voltage)
{
    if(voltage>15)
        return EXIT_FAILURE;

    int analogValue;

    //analogValue = (int)(currentScalar*current*currentSenseResistance; // max voltage is 0.01
    //analogWrite(CurrentAdjust,analogValue);

    // output voltage 0-5 needed voltage is 0-0.1
    // we want current to be 1A so we need voltage to be
    // v=IR, v=Current*0.01;
    // analogValue = v *30 this is the scalar
    return EXIT_SUCCESS;

}
