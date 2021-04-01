#include <MIDI.h>        // access to serial (5 pin DIN) MIDI
#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)
#include "po_settings.h"
#include "clock.h"
#include <Arduino.h>
#include "po_control.h"
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))

#define FIRMWARE_VERSION "2.3.0-beta"

// Create the Serial MIDI portsm
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial7, MIDI2);

// Create the ports for USB devices plugged into Teensy's 2nd USB port (via hubs)
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
USBHub hub4(myusb);
MIDIDevice midi01(myusb);
MIDIDevice midi02(myusb);
MIDIDevice midi03(myusb);
MIDIDevice midi04(myusb);

int hostMIDIDevicNumber = 4;
MIDIDevice * midilist[4] = {
  &midi01, &midi02, &midi03, &midi04
  };

// A variable to know how long the LED has been turned on
elapsedMillis ledOnMillis;

bool activity = false;
midi::MidiType mtype;
Clock *clk;
PO_Control *po_control;

unsigned long prev_midi_clock_time = 0;
volatile unsigned long curr_midi_clock_time = 0;

float delta = 0;
void sendToUSBHost(byte type, byte data1, byte data2, byte channel);
void sendToComputer(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable);
void processMidi(uint8_t type,uint8_t channel , uint8_t data1, uint8_t data2,const uint8_t *sys, bool isSendToComputer, bool isSendToUSBHost);
void processMidiClock();
void printMIDI(byte type, byte data1, byte data2, byte channel);

void setup() {
  MIDI1.begin(MIDI_CHANNEL_OMNI);
  MIDI2.begin(MIDI_CHANNEL_OMNI);
  pinMode(PO_BUTTON_1, OUTPUT);
  pinMode(PO_BUTTON_2, OUTPUT);
  pinMode(PO_BUTTON_3, OUTPUT);
  pinMode(PO_BUTTON_4, OUTPUT);
  pinMode(PO_BUTTON_5, OUTPUT);
  pinMode(PO_BUTTON_6, OUTPUT);
  pinMode(PO_BUTTON_7, OUTPUT);
  pinMode(PO_BUTTON_8, OUTPUT);
  pinMode(PO_BUTTON_9, OUTPUT);
  pinMode(PO_BUTTON_10, OUTPUT);
  pinMode(PO_BUTTON_11, OUTPUT);
  pinMode(PO_BUTTON_12, OUTPUT);
  pinMode(PO_BUTTON_13, OUTPUT);
  pinMode(PO_BUTTON_14, OUTPUT);
  pinMode(PO_BUTTON_15, OUTPUT);
  pinMode(PO_BUTTON_16, OUTPUT);
  pinMode(PO_BUTTON_SOUND,OUTPUT);
  pinMode(PO_BUTTON_FX,OUTPUT);
  pinMode(PO_BUTTON_PATTERN,OUTPUT);
  pinMode(PO_BUTTON_PLAY,OUTPUT);
  pinMode(PO_BUTTON_WRITE,OUTPUT);
  pinMode(PO_BUTTON_BPM,OUTPUT);
  pinMode(PO_BUTTON_SPECIAL,OUTPUT);
  

  pinMode(13, OUTPUT); // LED pin
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);

  digitalWrite(PO_BUTTON_1, HIGH);
  digitalWrite(PO_BUTTON_2, HIGH);
  digitalWrite(PO_BUTTON_3, HIGH);
  digitalWrite(PO_BUTTON_4, HIGH);
  digitalWrite(PO_BUTTON_5, HIGH);
  digitalWrite(PO_BUTTON_6, HIGH);
  digitalWrite(PO_BUTTON_7, HIGH);
  digitalWrite(PO_BUTTON_8, HIGH);
  digitalWrite(PO_BUTTON_9, HIGH);
  digitalWrite(PO_BUTTON_10, HIGH);
  digitalWrite(PO_BUTTON_11, HIGH);
  digitalWrite(PO_BUTTON_12, HIGH);
  digitalWrite(PO_BUTTON_13, HIGH);
  digitalWrite(PO_BUTTON_14, HIGH);
  digitalWrite(PO_BUTTON_15, HIGH);
  digitalWrite(PO_BUTTON_16, HIGH);
  digitalWrite(PO_BUTTON_SOUND, HIGH);
  digitalWrite(PO_BUTTON_FX, HIGH);
  digitalWrite(PO_BUTTON_PATTERN, HIGH);
  digitalWrite(PO_BUTTON_PLAY, HIGH);
  digitalWrite(PO_BUTTON_WRITE, HIGH);
  digitalWrite(PO_BUTTON_BPM, HIGH);
  digitalWrite(PO_BUTTON_SPECIAL, HIGH);
  // Wait 1.5 seconds before turning on USB Host.  If connected USB devices
  // use too much power, Teensy at least completes USB enumeration, which
  // makes isolating the power issue easier.
  delay(1500);

  po_control = new PO_Control();
  delay(10);
  myusb.begin();
  if(po_control->get_sync_out_enabled()){
    pinMode(CLOCKSYNCPIN,OUTPUT);
    clk = new Clock(CLOCKSYNCPIN);
  }

  Serial.begin(115200);
  Serial.println("PO-MA");
  Serial.println("Firmware Version");
  Serial.println(FIRMWARE_VERSION);
}

void loop() {
  if(po_control->get_is_looping() && !po_control->get_is_recording()){
    po_control->run_looper();
  }
  activity = false;
  if(po_control->get_sync_out_enabled()){
    clk->sendBPM(millis());
  }
  // Next read messages arriving from the (up to) 10 USB devices plugged into the USB Host port
  for (int port=0; port < 4; port++) {
    if (midilist[port]->read()) {
      uint8_t type =       midilist[port]->getType();
      uint8_t data1 =      midilist[port]->getData1();
      uint8_t data2 =      midilist[port]->getData2();
      uint8_t channel =    midilist[port]->getChannel();
      const uint8_t *sys = midilist[port]->getSysExArray();
      activity = true;
      if (type == 0xF8){ // midi clock
        processMidiClock();
        mtype = (midi::MidiType)type;
        MIDI1.send(mtype, data1, data2, channel);  
        MIDI2.send(mtype, data1, data2, channel);
        sendToComputer(mtype, data1, data2, channel, sys, 0);
      }
      else{
        processMidi(type, channel, data1, data2,sys,true,false);
      }
    }
  }

  if (usbMIDI.read()) {
    // get the USB MIDI message, defined by these 5 numbers (except SysEX)
    byte type = usbMIDI.getType();
    byte channel = usbMIDI.getChannel();
    byte data1 = usbMIDI.getData1();
    byte data2 = usbMIDI.getData2();
    const uint8_t *sys = usbMIDI.getSysExArray();
    //byte cable = usbMIDI.getCable();

    // forward this message to the Serial MIDI OUT ports
    if (type != usbMIDI.SystemExclusive) {
      // Normal messages, first we must convert usbMIDI's type (an ordinary
      // byte) to the MIDI library's special MidiType.
      if (type == 0xF8){ // midi clock
        processMidiClock();
        mtype = (midi::MidiType)type;
        MIDI1.send(mtype, data1, data2, channel);
        MIDI2.send(mtype, data1, data2, channel);
        sendToUSBHost(mtype, data1, data2, channel);
      }
      else{
        processMidi(type, channel, data1, data2,sys,false,true);
      }
    } else {
      // SysEx messages are special.  The message length is given in data1 & data2
      unsigned int SysExLength = data1 + data2 * 256;
      MIDI1.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
      MIDI2.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
    }
    activity = true;
  }
  // blink the LED when any activity has happened
  if (activity) {
    digitalWriteFast(13, HIGH); // LED on
    ledOnMillis = 0;
  }
  if (ledOnMillis > 15) {
    digitalWriteFast(13, LOW);  // LED off
  }

  if (MIDI1.read()) {
    // get the Serial IN MIDI message, defined by these 5 numbers (except SysEX)
    byte type = MIDI1.getType();
    byte channel = MIDI1.getChannel();
    byte data1 = MIDI1.getData1();
    byte data2 = MIDI1.getData2();
    const uint8_t *sys = MIDI1.getSysExArray();
    //byte cable = usbMIDI.getCable();

    // forward this message to the Serial MIDI OUT ports
    if (type != usbMIDI.SystemExclusive) {
      // Normal messages, first we must convert usbMIDI's type (an ordinary
      // byte) to the MIDI library's special MidiType.
      if (type == 0xF8){ // midi clock
        processMidiClock();
        mtype = (midi::MidiType)type;
        MIDI1.send(mtype, data1, data2, channel);
        MIDI2.send(mtype, data1, data2, channel);
        sendToComputer(mtype, data1, data2, channel, sys, 0);
        sendToUSBHost(mtype, data1, data2, channel);
      }
      else{
        processMidi(type, channel, data1, data2,sys,true,true);
      }
    } else {
      // SysEx messages are special.  The message length is given in data1 & data2
      unsigned int SysExLength = data1 + data2 * 256;
      MIDI1.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
      MIDI2.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
    }
    activity = true;
  }

  if (MIDI2.read()) {
    // get the Serial IN MIDI message, defined by these 5 numbers (except SysEX)
    byte type = MIDI2.getType();
    byte channel = MIDI2.getChannel();
    byte data1 = MIDI2.getData1();
    byte data2 = MIDI2.getData2();
    const uint8_t *sys = MIDI2.getSysExArray();
    //byte cable = usbMIDI.getCable();

    // forward this message to the Serial MIDI OUT ports
    if (type != usbMIDI.SystemExclusive) {
      // Normal messages, first we must convert usbMIDI's type (an ordinary
      // byte) to the MIDI library's special MidiType.
      if (type == 0xF8){ // midi clock
        processMidiClock();
        mtype = (midi::MidiType)type;
        MIDI1.send(mtype, data1, data2, channel);
        MIDI2.send(mtype, data1, data2, channel);
        sendToComputer(mtype, data1, data2, channel, sys, 0);
        sendToUSBHost(mtype, data1, data2, channel);
      }
      else{
        processMidi(type, channel, data1, data2,sys,true,true);
      }
    } else {
      // SysEx messages are special.  The message length is given in data1 & data2
      unsigned int SysExLength = data1 + data2 * 256;
      MIDI1.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
      MIDI2.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
    }
    activity = true;
  }

  // blink the LED when any activity has happened
  if (activity) {
    digitalWriteFast(13, HIGH); // LED on
    ledOnMillis = 0;
  }
  if (ledOnMillis > 15) {
    digitalWriteFast(13, LOW);  // LED off
  }
}

void sendToUSBHost(byte type, byte data1, byte data2, byte channel){
  for (int i = 0 ; i < hostMIDIDevicNumber ; i++){
    midilist[i]->send(type, data1, data2, channel);
  }
}

void sendToComputer(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable)
{
  if (type != midi::SystemExclusive) {
    usbMIDI.send(type, data1, data2, channel, cable);
  } else {
    unsigned int SysExLength = data1 + data2 * 256;
    usbMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
  }
}

void processMidiClock(){
  curr_midi_clock_time = micros();
  delta = 60000 / ( ( (float) ((curr_midi_clock_time - prev_midi_clock_time) / float(1000) )) * po_control->get_midi_ppqn());
  clk->setBPM((int)(floor)(delta));
  Serial.println((int)(floor)(delta));
  prev_midi_clock_time = curr_midi_clock_time;
}

void processMidi(uint8_t type,uint8_t channel , uint8_t data1, uint8_t data2,const uint8_t *sys, bool isSendToComputer, bool isSendToUSBHost){
  // printMIDI(type, data1, data2, channel );
  mtype = (midi::MidiType)type;
  if (type == 0xFA || type == 0xFB || type == 0xFC){ //process transport msgs
    MIDI1.send(mtype, data1, data2, channel);
    MIDI2.send(mtype, data1, data2, channel);
    if(isSendToComputer){
      sendToComputer(type, data1, data2, channel, sys, 0);
    }
    if(isSendToUSBHost){
      sendToUSBHost(mtype, data1, data2, channel);
    }
    if(type == 0xFA && !po_control->get_disable_transport()){
      if(!po_control->get_is_playing()){
        po_control->startOrStopPlayback();
        clk->start();
        if (po_control->get_looper_transport_control_link()){
          po_control->start_looper();
        }
        po_control->set_is_playing(!po_control->get_is_playing());
      }
    } else if(type == 0xFC && !po_control->get_disable_transport()){
      if(po_control->get_is_playing()){
        po_control->startOrStopPlayback();
        clk->stop();
        if (po_control->get_looper_transport_control_link()){
          po_control->stop_looper();
        }
        po_control->set_is_playing(!po_control->get_is_playing());
      }
    }
  } else {
    if(isSendToComputer){
      sendToComputer(type, data1, data2, channel, sys, 0);
    }
    if(isSendToUSBHost){
//      sendToUSBHost(mtype, data1, data2, channel);
    }
    if((channel == po_control->get_volca_fm_midi_ch_1() || channel == po_control->get_volca_fm_midi_ch_2()) && type == midi::NoteOn && po_control->get_volca_fm_velocity() == 1){ //To enable keyboard velocity for VolcaFM
      MIDI1.send((midi::MidiType)176, 41, data2, channel); //0xB0
      MIDI2.send((midi::MidiType)176, 41, data2, channel); //0xB0
    }
    MIDI1.send(mtype, data1, data2, channel);
    MIDI2.send(mtype, data1, data2, channel);
    sendToUSBHost(mtype, data1, data2, channel);
  }
  po_control->execute(type, channel, data1, data2);
}

void printMIDI(byte type, byte data1, byte data2, byte channel ){
  Serial.println(" ");
  Serial.println(type);
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(channel);
  Serial.println(" ");
}