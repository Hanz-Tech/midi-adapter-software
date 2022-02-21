#include <Control_Surface.h>
#include <MIDI_Interfaces/BluetoothMIDI_Interface.hpp>


BluetoothMIDI_Interface MIDI_BLE;
HardwareSerialMIDI_Interface MIDI_SERIAL = Serial;

#define FIRMWARE_VERSION "2.3.5"

MIDI_PipeFactory<2> pipes;

void setup() {
  Serial.begin(115200);
  Serial.println("PO-MA");
  Serial.println("Firmware Version");
  Serial.println(FIRMWARE_VERSION);
  
  MIDI_BLE >> pipes >> MIDI_SERIAL; // all incoming midi from BLE is sent to Serial
  MIDI_BLE << pipes << MIDI_SERIAL; // all incoming midi from Serial is sent to BLE

  MIDI_SERIAL.begin();
  MIDI_BLE.begin();
}

void loop() {
  MIDI_BLE.update();
  MIDI_SERIAL.update();
}
