#ifndef PO_SETTINGS_H
#define PO_SETTINGS_H

//Teensy GPIO mapping to PO button
#define PO_BUTTON_1 5
#define PO_BUTTON_2 6
#define PO_BUTTON_3 18
#define PO_BUTTON_4 19
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
#define PO_BUTTON_PATTERN 0
#define PO_BUTTON_WRITE 35
#define PO_BUTTON_PLAY 36
#define PO_BUTTON_FX 16
#define PO_BUTTON_BPM 23
#define PO_BUTTON_SPECIAL 17
#define PO_POT_A 22
#define PO_POT_B 21
#define CLOCKSYNCPIN 37

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


#endif
