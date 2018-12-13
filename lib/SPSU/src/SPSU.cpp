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

/**
   @brief "Description"
   @param "Param description"
   @pre "Pre-conditions"
   @post "Post-conditions"
   @return "Returns 0 if successful"
*/
bool SPSU::begin()
{
    pinMode(Shutdown, OUTPUT);
    pinMode(CurrentAdjust, OUTPUT);
    pinMode(CurrentSense, INPUT);
    pinMode(CurrentSense10, INPUT);
    pinMode(VoltageSense, INPUT);
    pinMode(VFB, INPUT);
    digitalWrite(Shutdown, LOW);
    analogWrite(CurrentAdjust, 0);
    if analogRead(VoltageSense)==0;
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
    LOG("Current: %u", current)
    return current;
}

/*********************************************************************
* Comment
*********************************************************************/
bool SPSU::setCurrent(float current)
{
    if(current>10)
        return EXIT_FAILURE

    int analogValue;

    analogValue = (int)(currentScalar*current*currentSenseResistance; // max voltage is 0.01
    analogWrite(CurrentAdjust,analogValue);

    // output voltage 0-5 needed voltage is 0-0.1
    // we want current to be 1A so we need voltage to be
    // v=IR, v=Current*0.01;
    // analogValue = v *30 this is the scalar
    return EXIT_SUCCESS
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
    LOG("Voltage: %u", voltage)
    return voltage;
}

/*********************************************************************
* Comment
*********************************************************************/
bool SPSU::setVoltage(float voltage)
{
    if(voltage>15)
        return EXIT_FAILURE

    int analogValue;

    //analogValue = (int)(currentScalar*current*currentSenseResistance; // max voltage is 0.01
    //analogWrite(CurrentAdjust,analogValue);

    // output voltage 0-5 needed voltage is 0-0.1
    // we want current to be 1A so we need voltage to be
    // v=IR, v=Current*0.01;
    // analogValue = v *30 this is the scalar
    return EXIT_SUCCESS

}
