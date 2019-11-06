#include <OPC.h>
#include <Bridge.h>
#include <SPI.h>

// Declare the OPC objest
OPCSerial SPSU;
opcOperation digital_status_input[14];
opcOperation analog_status_input[6];

const int CurrentAdjustPin = 9; // Digital PWM
const int CurrentSensePin = A1; // Analog In
const int CurrentSense10Pin = A2; // Analog In
const int VoltageSensePin = A0; // Analog In
const int ShutdownPin = 11; // Digital PWM
const int SyncPin = 5; // Digital PWM
const int VFBPin = 10; // Digital PWM
const int ledPin = 13; // built in LED


// turn on/off built-in LED (pin13)
bool callback_led(const char *itemID, const opcOperation opcOP, const bool value){
  static bool ledValue = false;

  if (opcOP == opc_opwrite) {
    ledValue = value;

    if (ledValue)
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);
  }
  else
  return ledValue;
}

// turn off/on of the device
bool callback_turn_on(const char *itemID, const opcOperation opcOP, const bool value){
  static bool statusValue = false;

  if (opcOP == opc_opwrite) {
    statusValue = value;

    if (statusValue)
      digitalWrite(ShutdownPin, HIGH);
    else
      {
        analogWrite(CurrentAdjustPin, 0);
        analogWrite(VFBPin, 0);
        digitalWrite(ShutdownPin, LOW);
      }
  }
  else
  return statusValue;
}

// write value into CurrentAdjustPin
// plan: receive value in ampers and recalculate into 0-255
// then write the value into the CA pin
int callback_ca(const char *itemID, const opcOperation opcOP, const int value)
{
    static int caValue = 0;

    if (opcOP == opc_opwrite) {
        caValue = value;

        if (caValue)
          analogWrite(CurrentAdjustPin, caValue);
        else
          analogWrite(CurrentAdjustPin, 0);
    }
    else
    return caValue;
}

// Control Voltage
// plan: receive value in volts and recalculate into 0-255
// then wrute the value onto VFB pin
int callback_vfb_write(const char *itemID, const opcOperation opcOP, const int value)
{
  static int vfbValue = 0;

  if (opcOP == opc_opwrite) {
    vfbValue = value;

    if (vfbValue)
      analogWrite(VFBPin, vfbValue);
    else
      analogWrite(VFBPin, 0);
  }
  else
  return vfbValue;
}

// measure current in CurrentSensePin
// plan: recalculate the value into real current
int callbac_cs(const char *itemID, const opcOperation opcOP, const int value){
  return analogRead(CurrentSensePin); // 0-1023
}

// measure current in CurrentSense10Pin
// plan: recalculate the value into real current
int callbac_cs10(const char  *itemID, const opcOperation opcOP, const int value){
  return analogRead(CurrentSense10Pin); //0-1023
}

// measure voltage in VFBPin
// plan: recalculate the value into real voltage
int callback_vfb_read(const char *itemID, const opcOperation opcOP, const int value){
  return analogRead(VoltageSensePin); //0-1023
}



void setup() {
  byte k;

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(CurrentAdjustPin, OUTPUT);
  pinMode(CurrentSensePin, OUTPUT);
  pinMode(CurrentSense10Pin, OUTPUT);
  pinMode(VoltageSensePin, OUTPUT);
  pinMode(ShutdownPin, OUTPUT);
  pinMode(SyncPin, OUTPUT);
  pinMode(VFBPin, OUTPUT);

  for (k=0; k<14; k++) digital_status_input[k] = opc_opwrite;
  for (k=0; k<6; k++) analog_status_input[k] = opc_opwrite;

  SPSU.setup();

  SPSU.addItem("led", opc_readwrite, opc_bool, callback_led);
  SPSU.addItem("CurrentAdjust", opc_readwrite, opc_int, callback_ca);
  SPSU.addItem("CurrentSense", opc_read, opc_int, callback_cs);
  SPSU.addItem("CurrentSense10", opc_read, opc_int, callback_cs10);
  SPSU.addItem("VoltageSense", opc_read, opc_int, callback_vfb_read);
  SPSU.addItem("Shutdown", opc_readwrite, opc_int, callback_turn_on);
  //SPSU.addItem("SyncPin", opc_readwrite, opc_int, callback_analog);
  SPSU.addItem("VFB", opc_readwrite, opc_int, callback_vfb_write);
}

void loop() {
  SPSU.processOPCCommands();
}
