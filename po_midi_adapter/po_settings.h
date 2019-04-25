#ifndef PO_SETTINGS_H
#define PO_SETTINGS_H

//Teensy GPIO mapping to PO button
#define PO_BUTTON_1 5
#define PO_BUTTON_2 6
#define PO_BUTTON_3 19
#define PO_BUTTON_4 18
#define PO_BUTTON_5 10
#define PO_BUTTON_6 11
#define PO_BUTTON_7 14
#define PO_BUTTON_8 15
#define PO_BUTTON_9 25
#define PO_BUTTON_10 12
#define PO_BUTTON_11 39
#define PO_BUTTON_12 38
#define PO_BUTTON_13 30
#define PO_BUTTON_14 32
#define PO_BUTTON_15 34
#define PO_BUTTON_16 33
#define PO_BUTTON_SOUND 2
#define PO_BUTTON_PATTERN 3
#define PO_BUTTON_WRITE 35
#define PO_BUTTON_PLAY 36
#define PO_BUTTON_FX 16
#define PO_BUTTON_BPM 23
#define PO_BUTTON_SPECIAL 17
#define PO_POT_A 22
#define PO_POT_B 21
#define CLOCKSYNCPIN A6

//Midi channel and other options
#define PO_MIDI_CHANNEL 1 //MIDI channel to control the PO
#define SYNTH_MIDI_CHANNEL 2 //MIDI channel to control the built-in poly synth
#define DISABLE_TRANSPORT 1 //1 = Disable Tranport to Midi out, 0 = Enable Transport to midi_out
#define PO_CC_CONTROL 0 //0 = Disable PO CC Control, switch between differet modes
#define VOLCA_FM_VELOCITY 1
#define VOLCAFM_MIDI_CHANNEL_1 13
#define VOLCAFM_MIDI_CHANNEL_2 16

//Different Mode of the op, only used if PO_CC_CONTROL=True
#define PERF_MODE 0
#define NORMAL_MODE 1
#define FX_MODE 2
#define RECORD_MODE 3
#define WRITE_MODE 4

#define KNOB_DELAY 15

//Midi Notes, these are used to trigger button 1-16 and sound,pattern.bpm....
uint8_t midi_note[24] = { //These are midi notes value
  0,
  68,
  69,
  70,
  71,
  72,
  73,
  74,
  75,
  60,
  61,
  62,
  63,
  64,
  65,
  66,
  67,
  76,
  77,
  78,
  79,
  80,
  81,
  82,
};

const char *midi_note_str[24] = {
  "0",
  "midi_note_1",
  "midi_note_2",
  "midi_note_3",
  "midi_note_4",
  "midi_note_5",
  "midi_note_6",
  "midi_note_7",
  "midi_note_8",
  "midi_note_9",
  "midi_note_10",
  "midi_note_11",
  "midi_note_12",
  "midi_note_13",
  "midi_note_14",
  "midi_note_15",
  "midi_note_16",
  "midi_note_sound",
  "midi_note_pattern",
  "midi_note_bpm",
  "midi_note_special",
  "midi_note_fx",
  "midi_note_play",
  "midi_note_write",
};


uint8_t midi_cc_knob[17] = {
  0,
  1,  //Synth : vco1 shape
  2,  //Synth : vco2 shape
  3,  //Synth : Detune vco2
  4,  //Synth : vco 2 octave
  5,  //Synth : LFO Freq
  6,  //Synth : LFO Mod
  7,  //Synth : Filter Freq
  8,  //Synth : Filter Res
  9,   //PO : mode, mode 0 : normal , mode 1 : fx, mode 2 : record , mode 3 : write   //Synth : Attack
  10,  //PO : sound 1-16    //Synth : Decay
  11,  //PO : pattern 1-16  //Synth : Sustain
  12,  //PO : volume 1-16   //Synth : Released
  13,  //Synth : Delay time
  14,  //Synth : Delay feedback
  15,  //Synth : Mix
  16   //Synth : Volume
};

const char *midi_cc_knob_str[17] = {
  "0",
  "midi_cc_knob_1",
  "midi_cc_knob_2",
  "midi_cc_knob_3",
  "midi_cc_knob_4",
  "midi_cc_knob_5",
  "midi_cc_knob_6",
  "midi_cc_knob_7",
  "midi_cc_knob_8",
  "midi_cc_knob_9",
  "midi_cc_knob_10",
  "midi_cc_knob_11",
  "midi_cc_knob_12",
  "midi_cc_knob_13",
  "midi_cc_knob_14",
  "midi_cc_knob_15",
  "midi_cc_knob_16"
};

uint8_t note_map[23][2] = {
  {midi_note[1],PO_BUTTON_1},
  {midi_note[2],PO_BUTTON_2},
  {midi_note[3],PO_BUTTON_3},
  {midi_note[4],PO_BUTTON_4},
  {midi_note[5],PO_BUTTON_5},
  {midi_note[6],PO_BUTTON_6},
  {midi_note[7],PO_BUTTON_7},
  {midi_note[8],PO_BUTTON_8},
  {midi_note[9],PO_BUTTON_9},
  {midi_note[10],PO_BUTTON_10},
  {midi_note[11],PO_BUTTON_11},
  {midi_note[12],PO_BUTTON_12},
  {midi_note[13],PO_BUTTON_13},
  {midi_note[14],PO_BUTTON_14},
  {midi_note[15],PO_BUTTON_15},
  {midi_note[16],PO_BUTTON_16},
  {midi_note[17],PO_BUTTON_SOUND},
  {midi_note[18],PO_BUTTON_PATTERN},
  {midi_note[19],PO_BUTTON_BPM},
  {midi_note[20],PO_BUTTON_SPECIAL},
  {midi_note[21],PO_BUTTON_FX},
  {midi_note[22],PO_BUTTON_PLAY},
  {midi_note[23],PO_BUTTON_WRITE},
};

uint8_t transport_note_map[7][2] ={
  {midi_note[9],PO_BUTTON_SOUND},
  {midi_note[10],PO_BUTTON_PATTERN},
  {midi_note[11],PO_BUTTON_BPM},
  {midi_note[1],PO_BUTTON_SPECIAL},
  {midi_note[2],PO_BUTTON_FX},
  {midi_note[3],PO_BUTTON_PLAY},
  {midi_note[4],PO_BUTTON_WRITE}
};

#endif
