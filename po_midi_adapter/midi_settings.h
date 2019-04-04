#ifndef MIDI_SETTINGS_H
#define MIDI_SETTINGS_H

//Midi Notes, these are used to trigger button 1-16 and sound,pattern.bpm....
#define MIDI_NOTE_1 60
#define MIDI_NOTE_2 61
#define MIDI_NOTE_3 62
#define MIDI_NOTE_4 63
#define MIDI_NOTE_5 64
#define MIDI_NOTE_6 65
#define MIDI_NOTE_7 66
#define MIDI_NOTE_8 67
#define MIDI_NOTE_9 68
#define MIDI_NOTE_10 69
#define MIDI_NOTE_11 70
#define MIDI_NOTE_12 71
#define MIDI_NOTE_13 72
#define MIDI_NOTE_14 73
#define MIDI_NOTE_15 74
#define MIDI_NOTE_16 75

#define MIDI_NOTE_17 76
#define MIDI_NOTE_18 77
#define MIDI_NOTE_19 78
#define MIDI_NOTE_20 79
#define MIDI_NOTE_21 80
#define MIDI_NOTE_22 81
#define MIDI_NOTE_23 82


#define MIDI_KNOB_1_CC 1 
                         //Synth : vco1 shape

#define MIDI_KNOB_2_CC 2 
                        //Synth : vco2 shape

#define MIDI_KNOB_3_CC 3 
                         //Synth : Detune vco2

#define MIDI_KNOB_4_CC 4 
                         //Synth : vco 2 octave

#define MIDI_KNOB_5_CC 5 //Synth : LFO Freq
#define MIDI_KNOB_6_CC 6 //Synth : LFO Mod
#define MIDI_KNOB_7_CC 7 //Synth : Filter Freq

#define MIDI_KNOB_8_CC 8 //Synth : Filter Res

#define MIDI_KNOB_9_CC 9 //Synth : Attack , 
						 //PO : mode 0 :perf , mode 1 : normal , mode 2 : fx, mode 3 : record , mode 4 : write

#define MIDI_KNOB_10_CC 10 //Synth : Decay
						   //PO : sound 1-16
								
#define MIDI_KNOB_11_CC 11 //Synth : Sustain
						   //PO : pattern 1-16

#define MIDI_KNOB_12_CC 12 //Synth : Released
						   //PO : volume 1-16

#define MIDI_KNOB_13_CC 13 //Synth : Delay time
#define MIDI_KNOB_14_CC 14 //Synth : Delay feedback
#define MIDI_KNOB_15_CC 15 //Synth : Mix vco1/vco2
#define MIDI_KNOB_16_CC 16 //Synth : Volume


#define KNOB_DELAY 15




#endif
