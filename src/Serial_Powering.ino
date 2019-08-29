/**
 * @Author: Steven Welch <welchsteven>
 * @Date:   2016-04-12T14:45:41-06:00
 * @Email:  WelchSteven@gmail.com
 * @Project: SPSU
 * @Filename: Serial_Powering.ino
 * @Last modified by:   steven
 * @Last modified time: 2018-12-12T14:15:47-07:00
 */

#include "log4arduino.h"
#include "/lib/SPSU/src/SPSU.h"
SPSU PowerSupply;
void setup() {
    // Initilize the pins and set safe conditions



    // put your setuap code here, to run once:
    Serial.begin(9600);
    while (!Serial)
    {
        // do nothing
    } ;

    //LOG_INIT(&Serial);
    Serial.println("SPSU");
    Serial.println(PowerSupply.begin());
}
void loop() {
        Serial.println(PowerSupply.getVoltage());
        //PowerSupply.setCurrent(0.05);
        //analogWrite(CurrentAdjust,100);
        Serial.println(PowerSupply.setCurrent(1)); // current in amps
        analogWrite(VFB,180);
        PowerSupply.startUp();

        delay(1000);
}
