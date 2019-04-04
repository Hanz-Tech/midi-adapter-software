[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Overview

In this repository you will find the firmware for the po midi adapter.  It is only meant a **Teensy 3.6**

# Uploading code
1. Download or clone the repo

2. You will need to first download and install [Arduino IDE](https://www.arduino.cc/en/main/software). Then download [Teensyduino](https://www.pjrc.com/teensy/td_download.html) and install on your computer in the same location where the Arduino IDE was installed.
 
3. Open Arduino IDE and open the .ino file.

4. Under Tools->Boards choose Teensy 3.6

5. Under Tools->USB Type choose Serial + MIDI16

6. With the Teensy plugged in,click upload to upload

The compiler might complain about an issue for conflicting library for the SD card, in this case you can delete the Arduino version found in `arduino/libraries/sd` 

# Modes of operation

## Pocket Operator Control

  Midi channel can be changed by `PO_MIDI_CHANNEL`
  
  All the buttons on the PO are triggerd by Midi notes. I didn't want to use MIDI CC because it doesn't tell us when the pads is   released.
  
  There are two modes of operation, mode one is for controller with more than 16 pads/keys and mode 2 for controller with 16 pads/keys +  at least 3 knob.  The modes can be switched by `PO_CC_CONTROL`.

  1. When `PO_CC_CONTROL` is 0, the adapter is in mode 1, this means all 23 buttons on the PO are assigned to sperate midi notes. See     below for more specification on midi assignemnt
  2. In Mode 2 (`PO_CC_CONTROL` is 1), there is MIDI_KNOB_1_CC which can switch the behavior of the midi keys/pads.
  
    1. MIDI_KNOB_1_CC is 0  -> The midi pads/keys are assigned to the 1-16 buttons on the PO
    2. MIDI_KNOB_1_CC is 1 -> The midi pads/keys are assigned to the play,write,sound,bpm,pattern,fx,special
    3. MIDI_KNOB_1_CC is 2 -> The FX button is pressed, The midi pads/keys are assigned to 1-16 buttons
    4. MIDI_KNOB1_CC is 3 -> The special(top right) buttons is pressed. midi pads/keys are assigned to 1-16 buttons
    5. MIDI_KNOB1_CC is 4 -> The write buttons is pressed. midi pads/keys are assigned to 1-16 buttons. Switching to another mode from        this mode will pressed the write button again, turning the light off.
    
    In mode 2, sound pattern and volume are also controlled by MIDI CC
    1. MIDI_KNOB_9_CC -> Sounds 1-16
    2.MIDI_KNOB_10_CC -> Pattern 1-16
    3.MIDI_KNOB_11_CC -> Volume 1-16
    
## Synth Engine Control
  The synth engine operates on its own MIDI channel `SYNTH_MIDI_CHANNEL`. The synth is largely inspired by [Teensy Polysynth](https://github.com/otem/teensypolysynth). There are 16 parameters that can be controlled via midi CC.
  
 1. MIDI_KNOB_1_CC : vco1 shape
 2. MIDI_KNOB_2_CC : vco2 shape
 3. MIDI_KNOB_3_CC : Detune vco2
 4. MIDI_KNOB_4_CC : vco 2 octave
 5. MIDI_KNOB_5_CC : LFO Freq
 6. MIDI_KNOB_6_CC : LFO Mod
 7. MIDI_KNOB_7_CC : Filter Freq
 8. MIDI_KNOB_8_CC : Filter Res
 9. MIDI_KNOB_9_CC : Attack
 10. MIDI_KNOB_10_CC  : Decay					
 11. MIDI_KNOB_11_CC  : Sustain
 12. MIDI_KNOB_12_CC  : Released
 13. MIDI_KNOB_13_CC  : Delay time
 14. MIDI_KNOB_14_CC  : Delay feedback
 15. MIDI_KNOB_15_CC  : Mix vco1/vco2
 16. MIDI_KNOB_16_CC  : Volume
 

# Modifying MIDI assignment 

MIDI assignment can be found in `midi_settings.h` where you can change the midi notes as well as the midi cc. By default, the assignement are as follows

## MIDI to PO Button
1. MIDI_NOTE_1 -> PO_BUTTON_9
2. MIDI_NOTE_2 -> PO_BUTTON_10
3. MIDI_NOTE_3 -> PO_BUTTON_11
4. MIDI_NOTE_4 -> PO_BUTTON_12
5. MIDI_NOTE_5 -> PO_BUTTON_13
6. MIDI_NOTE_6 -> PO_BUTTON_14
7. MIDI_NOTE_7 -> PO_BUTTON_15
8. MIDI_NOTE_8 -> PO_BUTTON_16
9. MIDI_NOTE_9 -> PO_BUTTON_1
10. MIDI_NOTE_10 -> PO_BUTTON_2
11. MIDI_NOTE_11 -> PO_BUTTON_3
12. MIDI_NOTE_12 -> PO_BUTTON_4
13. MIDI_NOTE_13 -> PO_BUTTON_5
14. MIDI_NOTE_14 -> PO_BUTTON_6
15. MIDI_NOTE_15 -> PO_BUTTON_7
16. MIDI_NOTE_16 -> PO_BUTTON_8
17. MIDI_NOTE_17 -> PO_BUTTON_SOUND
18. MIDI_NOTE_18 -> PO_BUTTON_PATTERN
19. MIDI_NOTE_19 -> PO_BUTT1. M
20. MIDI_NOTE_20 -> PO_BUTTON_SPECIAL
21. MIDI_NOTE_21 -> PO_BUTTON_FX
22. MIDI_NOTE_22 -> PO_BUTTON_PLAY
23. MIDI_NOTE_23 -> PO_BUTTON_WRITE

## MIDI notes 

1. MIDI_NOTE_1 : 60
2. MIDI_NOTE_2 : 61
3. MIDI_NOTE_3 : 62
4. MIDI_NOTE_4 : 63
5. MIDI_NOTE_5 : 64
6. MIDI_NOTE_6 : 65
7. MIDI_NOTE_7 : 66
8. MIDI_NOTE_8 : 67
9. MIDI_NOTE_9 : 68
10. MIDI_NOTE_10 : 69
11. MIDI_NOTE_11 : 70
12. MIDI_NOTE_12 : 71
13. MIDI_NOTE_13 : 72
14. MIDI_NOTE_14 : 73
15. MIDI_NOTE_15 : 74
16. MIDI_NOTE_16 : 75

17. MIDI_NOTE_17 : 76
18. MIDI_NOTE_18 : 77
19. MIDI_NOTE_19 : 78
20. MIDI_NOTE_20 : 79
21. MIDI_NOTE_21 : 80
22. MIDI_NOTE_22 : 81
23. MIDI_NOTE_23 : 82

## MIDI CC

1. MIDI_KNOB_1_CC : 1
2. MIDI_KNOB_2_CC : 2
3. MIDI_KNOB_3_CC : 3
4. MIDI_KNOB_4_CC : 4
5. MIDI_KNOB_5_CC : 5
6. MIDI_KNOB_6_CC : 6
7. MIDI_KNOB_7_CC : 7
8. MIDI_KNOB_8_CC : 8
9. MIDI_KNOB_9_CC : 9
10. MIDI_KNOB_10_CC : 10
11. MIDI_KNOB_11_CC : 11
12. MIDI_KNOB_12_CC : 12
13. MIDI_KNOB_13_CC : 13
14. MIDI_KNOB_14_CC : 14
15. MIDI_KNOB_15_CC : 15
16. MIDI_KNOB_16_CC : 16
