#include <SD.h>
#include <SDConfigFile.h>
#include <SPI.h>
#include <MIDI.h>        // access to serial (5 pin DIN) MIDI
#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)
#include "po_settings.h"
#include "Synth1.h"
#include "clock.h"
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

#define FIRMWARE_VERSION "2.0.0"

// Create the Serial MIDI portsm
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI1);

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
Synth1 synth1;
int synth_enabled = 1;
Clock *clk;
typedef void (Synth1::*Synth1MemFn)(uint32_t midi_cc);
static Synth1MemFn synth_func_ptr[18] = {&Synth1::stub,&Synth1::changeVCO1Shape, &Synth1::changeVCO2Shape, &Synth1::changeDetune2,&Synth1::changeOct2,
                            &Synth1::changeLFOFreq,&Synth1::changeLFOMod,&Synth1::changeFilterFreq,&Synth1::changeFilterRes,
                        &Synth1::changeAttack,&Synth1::changeDecay,&Synth1::changeSustain,&Synth1::changeRelease,
                        &Synth1::changeDelayTime,&Synth1::changeDelayFeedback,&Synth1::changeMix,&Synth1::changeVolume,&Synth1::changePolyphony};

const char CONFIG_FILE[] = "config.cfg";
const int chipSelect = BUILTIN_SDCARD;

int po_midi_channel = 1;
int synth_midi_channel = 2;
int disable_transport = 1; //1 == disable transport, 0 == enabled transport
int po_cc_control = 0; //0 == disable , 1 ==enable
int volca_fm_velocity = 1; // 1 == enable, 0 == disable
int volca_fm_midi_ch_1 = 13;
int volca_fm_midi_ch_2 = 16;

int sync_out_enabled = 1;
int midi_ppqn = 24;
unsigned long prev_midi_clock_time = 0;
volatile unsigned long curr_midi_clock_time = 0;
bool isThreadRunning = false;

float delta = 0;
void loadDefaultConfig();
bool loadSDConfig();
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
void processMidiClock();

void setup() {
  MIDI1.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
  Serial.println("PO-MA");
  Serial.println("Firmware Version");
  Serial.println(FIRMWARE_VERSION);
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

  //Try to load config from SD if present
  if (SD.begin(chipSelect)){
    //Serial.println("card init");
    if(loadSDConfig()){
        digitalWrite(13, HIGH);   // set the LED on
        delay(100);                  // wait for a second
        digitalWrite(13, LOW);    // set the LED off
        delay(100);
        digitalWrite(13, HIGH);   // set the LED on
        delay(100);                  // wait for a second
        digitalWrite(13, LOW);    // set the LED off
        delay(100);
        digitalWrite(13, HIGH);   // set the LED on
        delay(100);                  // wait for a second
        digitalWrite(13, LOW);    // set the LED off
    }
  }

  //Serial.println("PO_MIDI_SHIELD");
  delay(10);
  myusb.begin();
  if(sync_out_enabled){
    pinMode(CLOCKSYNCPIN,OUTPUT);
    clk = new Clock(CLOCKSYNCPIN);
  }
  if(synth_enabled){
    synth1 = Synth1();
    synth1.init();
  }
}

void loop() {
  activity = false;
  if(sync_out_enabled){
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
      }
      else{
        processMidi(type, channel, data1, data2,sys,false);
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
      }
      else{
        processMidi(type, channel, data1, data2,sys,false);
      }
    } else {
      // SysEx messages are special.  The message length is given in data1 & data2
      unsigned int SysExLength = data1 + data2 * 256;
      MIDI1.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
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
      }
      else{
        processMidi(type, channel, data1, data2,sys,false);
      }
    } else {
      // SysEx messages are special.  The message length is given in data1 & data2
      unsigned int SysExLength = data1 + data2 * 256;
      MIDI1.sendSysEx(SysExLength, usbMIDI.getSysExArray(), true);
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


void processMidiClock(){
  curr_midi_clock_time = micros();
  delta = 60000 / ( ( (float) ((curr_midi_clock_time - prev_midi_clock_time) / float(1000) )) * midi_ppqn);
  clk->setBPM((int)(floor)(delta));
  Serial.println((int)(floor)(delta));
  prev_midi_clock_time = curr_midi_clock_time;
}

void processMidi(uint8_t type,uint8_t channel , uint8_t data1, uint8_t data2,const uint8_t *sys, bool isSendToComputer){
  mtype = (midi::MidiType)type;
  if (type == 0xFA || type == 0xFB || type == 0xFC){ //process transport msgs
    if(!disable_transport){
      MIDI1.send(mtype, data1, data2, channel);
    }
    if(type == 0xFA){
      if(!isPlaying){
        startOrStopPlayback();
        clk->start();
        isPlaying = !isPlaying;
      }
    }
    else if(type == 0xFC){
      if(isPlaying){
        startOrStopPlayback();
        clk->stop();
        isPlaying = !isPlaying;
      }
    }
  } 
  else {
    if(isSendToComputer){
      sendToComputer(type, data1, data2, channel, sys, 0);
    }
    if((channel == volca_fm_midi_ch_1 || channel == volca_fm_midi_ch_2) && type == midi::NoteOn && volca_fm_velocity == 1){ //To enable keyboard velocity for VolcaFM
      MIDI1.send((midi::MidiType)176, 41, data2, channel); //0xB0
    }
    MIDI1.send(mtype, data1, data2, channel);
  }

  if(channel == po_midi_channel){
      if (type == midi::ControlChange && po_cc_control){
        if(data1 == midi_cc_knob[9]){ //mode
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
        }
        else if(data1 == midi_cc_knob[10]){ //sounds
          changeSound(data2);
        }
        else if(data1 == midi_cc_knob[11]){
          changePattern(data2);
        }
        else if(data1 == midi_cc_knob[12]){
          changeVolume(data2);
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
  }
  else if(channel == synth_midi_channel && synth_enabled){
    //Serial.println(type);
    if(type == midi::NoteOn){
      //Serial.println("play synth");
      synth1.playNote(data1,data2);
    }
    else if (type == midi::AfterTouchPoly){
      synth1.playPolyAftertouch(data1,data2);
    }
    else if (type == 208){
      //Serial.println("af touch");
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

bool loadSDConfig(){
  SDConfigFile cfg;
  const uint8_t CONFIG_LINE_LENGTH = 127;
  if(!cfg.begin(CONFIG_FILE, CONFIG_LINE_LENGTH)){
    Serial.println("cfg failed");
    return false;
  }
  while (cfg.readNextSetting()){
    for(int i = 1 ; i < LEN(midi_note_str); i++){
      if(cfg.nameIs(midi_note_str[i])){
        midi_note[i] = cfg.getIntValue();
        note_map[i-1][0] = cfg.getIntValue();
        //Serial.println("note found");
        //Serial.println(midi_note[i]);
        break;
      }
    }
    for(int i = 0 ; i < LEN(midi_cc_knob_str); i++){
      if(cfg.nameIs(midi_cc_knob_str[i])){
        midi_cc_knob[i] = cfg.getIntValue();
        //Serial.println("cc found");
        break;
      }
    }
    if(cfg.nameIs("po_midi_channel")){
      po_midi_channel = cfg.getIntValue();
    }
    else if(cfg.nameIs("synth_midi_channel")){
      synth_midi_channel = cfg.getIntValue();
    }
    else if(cfg.nameIs("disable_transport")){
      disable_transport = cfg.getIntValue();
    }
    else if(cfg.nameIs("po_cc_control")){
      po_cc_control = cfg.getIntValue();
    }
    else if(cfg.nameIs("volca_fm_velocity")){
      volca_fm_velocity = cfg.getIntValue();
    }
    else if(cfg.nameIs("volca_fm_midi_ch_1")){
      volca_fm_midi_ch_1 = cfg.getIntValue();
    }
    else if(cfg.nameIs("volca_fm_midi_ch_2")){
      volca_fm_midi_ch_2 = cfg.getIntValue();
    }
    else if(cfg.nameIs("sync_out_enabled")){
      sync_out_enabled = cfg.getIntValue();
    }
    else if(cfg.nameIs("midi_ppqn")){
      midi_ppqn = cfg.getIntValue();
    }
    else if(cfg.nameIs("synth_enabled")){
      synth_enabled = cfg.getIntValue();
    }
  }
  cfg.end();
  return true;
}
