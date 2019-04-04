#include <MIDI.h>        // access to serial (5 pin DIN) MIDI
#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)
#include "po_settings.h"
#ifndef MIDI_SETTINGS_H
#include "midi_settings.h"
#endif
#include "Synth1.h"
#include "clock.h"
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

#define PO_MIDI_CHANNEL 1 //MIDI channel to control the PO
#define SYNTH_MIDI_CHANNEL 2 //MIDI channel to control the built-in poly synth
#define DISABLE_TRANSPORT 1 //1 = Disable Tranport to Midi out, 0 = Enable Transport to midi_out
#define PO_CC_CONTROL 0 //0 = Disable PO CC Control, switch between differet modes
#define VOLCAFM_MIDI_CHANNEL_1 13
#define VOLCAFM_MIDI_CHANNEL_2 16
// Create the Serial MIDI portsm
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI1);

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

MIDIDevice * midilist[10] = {
  &midi01, &midi02, &midi03, &midi04
  };

// A variable to know how long the LED has been turned on
elapsedMillis ledOnMillis;
bool activity = false;
midi::MidiType mtype;
uint8_t op_mode = 0;
bool isWriteMode = false;
bool isPlaying = false;
Synth1 synth1 = Synth1();
typedef void (Synth1::*Synth1MemFn)(uint32_t midi_cc);
static Synth1MemFn synth_func_ptr[18] = {&Synth1::stub,&Synth1::changeVCO1Shape, &Synth1::changeVCO2Shape, &Synth1::changeDetune2,&Synth1::changeOct2,
                            &Synth1::changeLFOFreq,&Synth1::changeLFOMod,&Synth1::changeFilterFreq,&Synth1::changeFilterRes,
                        &Synth1::changeAttack,&Synth1::changeDecay,&Synth1::changeSustain,&Synth1::changeRelease,
                        &Synth1::changeDelayTime,&Synth1::changeDelayFeedback,&Synth1::changeMix,&Synth1::changeVolume,&Synth1::changePolyphony};

Clock clock = Clock(CLOCKSYNCPIN);

void sendToComputer(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable);
void triggerPONoteButton(int midiNote);
void releasePONoteButton(int midiNote);
void triggerPOControlNoteButton(uint8_t note, uint8_t op_mode);
void releasePOControlNoteButton(uint8_t note, uint8_t op_mode);
void changeSound(uint8_t sound);
void changeVolume(uint8_t vol);
void changePattern(uint8_t pattern);
void processMidi(uint8_t type,uint8_t channel , uint8_t data1, uint8_t data2, uint8_t * sys, bool isSendToComputer);
void startPlayback();
void stopPlayback();
void startOrStopPlayback();

void setup() {
  MIDI1.begin(MIDI_CHANNEL_OMNI);
  //Serial.begin(115200);
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
  //pinMode(CLOCKSYNCPIN,OUTPUT);

  pinMode(13, OUTPUT); // LED pin
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

  Serial.println("PO_MIDI_SHIELD");
  delay(10);
  myusb.begin();
  synth1.init();
}

void loop() {
  activity = false;




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
      processMidi(type, channel, data1, data2,sys,false);
    } else {
      // SysEx messages are special.  The message length is given in data1 & data2
      unsigned int SysExLength = data1 + data2 * 256;
      MIDI1.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
    }
    activity = true;
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
      processMidi(type, channel, data1, data2,sys,false);
    }
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

void sendToComputer(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable)
{
  if (type != midi::SystemExclusive) {
    usbMIDI.send(type, data1, data2, channel, cable);
  } else {
    unsigned int SysExLength = data1 + data2 * 256;
    usbMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
  }
}

void releasePONoteButton(uint8_t note){
  for (uint8_t i = 0 ; i < LEN(note_map) ; i++){
    if(note_map[i][0] == note){
      digitalWrite(note_map[i][1], HIGH);
    }
  }
}

void triggerPONoteButton(uint8_t note){
  for (uint8_t i = 0 ; i < LEN(note_map) ; i++){
    if(note_map[i][0] == note){
      if(note_map[i][1] == PO_BUTTON_PLAY){
        isPlaying = !isPlaying;
      }
      digitalWrite(note_map[i][1], LOW);
    }
  }
}

void triggerPOControlNoteButton(uint8_t note, uint8_t op_mode){
  if(op_mode == NORMAL_MODE){
    //Serial.println("normal mode");
    for (uint8_t i = 0 ; i < LEN(transport_note_map) ; i++){
      if(transport_note_map[i][0] == note){
        if(transport_note_map[i][1] == PO_BUTTON_PLAY){
          isPlaying = !isPlaying;
        }
        digitalWrite(transport_note_map[i][1], LOW);
      }
    }
  }
  else{
    for (uint8_t i = 0 ; i < LEN(note_map) ; i++){
      if(note_map[i][0] == note){
        digitalWrite(note_map[i][1], LOW);
      }
    }
  }
}

void releasePOControlNoteButton(uint8_t note, uint8_t op_mode){
  if(op_mode == NORMAL_MODE){
    for (uint8_t i = 0 ; i < LEN(transport_note_map) ; i++){
      if(transport_note_map[i][0] == note){
        digitalWrite(transport_note_map[i][1], HIGH);
      }
    }
  }
  else{
    for (uint8_t i = 0 ; i < LEN(note_map) ; i++){
      if(note_map[i][0] == note){
        digitalWrite(note_map[i][1], HIGH);
      }
    }
  }
}

void changeVolume(uint8_t vol){
  digitalWrite(PO_BUTTON_BPM, LOW);
  delay(KNOB_DELAY);
  digitalWrite(note_map[vol][1], LOW);
  delay(KNOB_DELAY);
  digitalWrite(note_map[vol][1], HIGH);
  delay(KNOB_DELAY);
  digitalWrite(PO_BUTTON_BPM, HIGH);
}

void changeSound(uint8_t sound){
  digitalWrite(PO_BUTTON_SOUND, LOW);
  delay(KNOB_DELAY);
  digitalWrite(note_map[sound][1], LOW);
  delay(KNOB_DELAY);
  digitalWrite(note_map[sound][1], HIGH);
  delay(KNOB_DELAY);
  digitalWrite(PO_BUTTON_SOUND, HIGH);
}

void changePattern(uint8_t pattern){
  digitalWrite(PO_BUTTON_PATTERN, LOW);
  delay(KNOB_DELAY);
  digitalWrite(note_map[pattern][1], LOW);
  delay(KNOB_DELAY);
  digitalWrite(note_map[pattern][1], HIGH);
  delay(KNOB_DELAY);
  digitalWrite(PO_BUTTON_PATTERN, HIGH);
}

void processMidi(uint8_t type,uint8_t channel , uint8_t data1, uint8_t data2,const uint8_t *sys, bool isSendToComputer){
  // if (type == 0xF8){ // midi clock
  //   MIDI1.send(mtype, data1, data2, channel);
  //   // clock.updateTempo();
  //   // clock.advance();
  // }
  if (type == 0xFA || type == 0xFB || type == 0xFC){ //process transport msgs
    if(!DISABLE_TRANSPORT){
      MIDI1.send(mtype, data1, data2, channel);
    }
    if(type == 0xFA){
      if(!isPlaying){
        startOrStopPlayback();
        isPlaying = !isPlaying;
      }
    }
    else if(type == 0xFC){
      if(isPlaying){
        startOrStopPlayback();
        isPlaying = !isPlaying;
      }
    }
  } 
  else {
    if(isSendToComputer){
      sendToComputer(type, data1, data2, channel, sys, 0);
    }
    if((channel == VOLCAFM_MIDI_CHANNEL_1 || channel == VOLCAFM_MIDI_CHANNEL_2) && type == midi::NoteOn){ //To enable keyboard velocity for VolcaFM
      uint8_t type = 176; //0xB0
      mtype = (midi::MidiType)type;
      MIDI1.send(mtype, 41, data2, channel);
    }
    mtype = (midi::MidiType)type;
    MIDI1.send(mtype, data1, data2, channel);

  }
  switch (channel){
    case PO_MIDI_CHANNEL:
        if (type == midi::ControlChange && PO_CC_CONTROL){
          switch(data1){
            case MIDI_KNOB_9_CC: //mode
              op_mode = data2;
              switch(data2){
                case PERF_MODE: /*fall through*/
                case NORMAL_MODE:
                  digitalWrite(PO_BUTTON_SPECIAL,HIGH);
                  digitalWrite(PO_BUTTON_FX,HIGH);
                  if(isWriteMode){
                    digitalWrite(PO_BUTTON_WRITE,LOW);
                    delay(20);
                    digitalWrite(PO_BUTTON_WRITE,HIGH);
                    isWriteMode = false;
                  }
                  break;
                case FX_MODE:
                  digitalWrite(PO_BUTTON_FX,LOW);
                  digitalWrite(PO_BUTTON_SPECIAL,HIGH);
                  if(isWriteMode){
                    digitalWrite(PO_BUTTON_WRITE,LOW);
                    delay(20);
                    digitalWrite(PO_BUTTON_WRITE,HIGH);
                    isWriteMode = false;
                  }
                  break;
                case RECORD_MODE:
                  digitalWrite(PO_BUTTON_FX,HIGH);
                  digitalWrite(PO_BUTTON_SPECIAL,LOW);
                  if(isWriteMode){
                    digitalWrite(PO_BUTTON_WRITE,LOW);
                    delay(20);
                    digitalWrite(PO_BUTTON_WRITE,HIGH);
                    isWriteMode = false;
                  }
                  break;
                case WRITE_MODE:
                  digitalWrite(PO_BUTTON_FX,HIGH);
                  digitalWrite(PO_BUTTON_SPECIAL,HIGH);
                  if(!isWriteMode){
                    digitalWrite(PO_BUTTON_WRITE,LOW);
                    delay(20);
                    digitalWrite(PO_BUTTON_WRITE,HIGH);
                    isWriteMode = true;
                  }
                  break;
              }
              break;
            case MIDI_KNOB_10_CC: //sound
              changeSound(data2);
              break;
            case MIDI_KNOB_11_CC: //pattern
              changePattern(data2);
              break;
            case MIDI_KNOB_12_CC:
              changeVolume(data2);
              break;
          }
        }
        else if (type ==  midi::NoteOn){
            if(op_mode > PERF_MODE){
              triggerPOControlNoteButton(data1,op_mode);
            }
            else{
              triggerPONoteButton(data1);
            }
        }
        else if(type == midi::NoteOff){
            if(op_mode > PERF_MODE){
              releasePOControlNoteButton(data1,op_mode);
            }
            else{
              releasePONoteButton(data1);
            }
        }
        break;
    case SYNTH_MIDI_CHANNEL:
      //Serial.println(type);
      if(type == midi::NoteOn){
        Serial.println("play synth");
        synth1.playNote(data1,data2);
      }
      else if (type == midi::AfterTouchPoly){
        synth1.playPolyAftertouch(data1,data2);
      }
      else if (type == 208){
        Serial.println("af touch");
        synth1.playMonoAftertouch(data1);
      }
      else if(type == midi::NoteOff){
        //Serial.println("stop synth");
        synth1.stopNote(data1);
      }
      else if(type == midi::ControlChange && data1 < 17){
        //Serial.println(data2);
        CALL_MEMBER_FN(synth1, synth_func_ptr[data1]) (data2*8);
      }
      break;
  }
}

void startOrStopPlayback(){
  for (uint8_t i = 0 ; i < LEN(transport_note_map) ; i++){
    if(transport_note_map[i][1] == PO_BUTTON_PLAY){
      digitalWrite(transport_note_map[i][1], LOW);
      delay(20);
      digitalWrite(transport_note_map[i][1], HIGH);
    }
  }
}