/**
 * @Author: Steven Welch <welchsteven>
 * @Date:   2018-12-10T12:13:15-07:00
 * @Email:  WelchSteven@gmail.com
 * @Project: SPSU
 * @Filename: SPSU.h
 * @Last modified by:   steven
 * @Last modified time: 2018-12-12T13:44:40-07:00
 */

#ifndef SPSU_H
# define SPSU_H

#define ENABLE_LOG4ARDUINO
#include <log4arduino.h>

 #include "Arduino.h"

#define CurrentAdjust 9
#define CurrentSense A1
#define CurrentSense10 A2
#define VoltageSense A0
#define ShutdownPin 11
#define Sync 5
#define VFB 10

/** SPSU Class
 * @class SPSU
 */
class SPSU {
private:
    //float setCurrent = 0;
    //float setVoltage = 0;
    const float Reference = 1.024;
    const float currentSenseResistance = 0.01;

    const float currentScalar = 30;
    const float voltageScalar = 16; /*! voltageScalar is the scaling factor for voltage divider on votlage sense
     \f$ V_{out} = V^{in} * \frac{R_{2}}{R_{1}+R_{2}} \f$ */

public:
    bool begin();
    float getCurrent();
    bool setCurrent(float current);
    float getVoltage();
    bool setVoltage(float voltage);
    bool shutdown();
    bool startUp();

protected:

};
#endif
