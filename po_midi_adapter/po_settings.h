#ifndef PO_SETTINGS_H
#define PO_SETTINGS_H

//Teensy GPIO mapping to PO button
#define PO_BUTTON_1 16
#define PO_BUTTON_2 17
#define PO_BUTTON_3 27
#define PO_BUTTON_4 30
#define PO_BUTTON_5 18
#define PO_BUTTON_6 19
#define PO_BUTTON_7 24
#define PO_BUTTON_8 25
#define PO_BUTTON_9 22
#define PO_BUTTON_10 21
#define PO_BUTTON_11 20
#define PO_BUTTON_12 11
#define PO_BUTTON_13 23
#define PO_BUTTON_14 5
#define PO_BUTTON_15 6
#define PO_BUTTON_16 10
#define PO_BUTTON_SOUND 39
#define PO_BUTTON_PATTERN 40
#define PO_BUTTON_WRITE 9
#define PO_BUTTON_PLAY 12
#define PO_BUTTON_FX 26
#define PO_BUTTON_BPM 41
#define PO_BUTTON_SPECIAL 31
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
