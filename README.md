[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Disclaimer

Copyright 2019 PO-MA

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# Overview

In this repository you will find the firmware for the pocket operator midi adapter. Hardware stuff can be found [here](https://github.com/PO-MIDI-Adapter/midi-adapter-hardware)

The code will only work on a **Teensy 3.6**

[![PO-MA](https://raw.githubusercontent.com/PO-MIDI-Adapter/midi-adapter-hardware/master/photos/title.jpg)](https://www.youtube.com/watch?v=iIQ18DAJAU0 "PO-MA")

## Main Features

### 1.Make any Pocket operator MIDI compatible
1. The adapter can act as a MIDI device and recveive MIDI signal via the micro USB port
2. The adapter can act as a USB host. It can power on and receive signal from one or more MIDI controllers directly
3. Specified MIDI signals are tranposed into GPIO output of the Teensy which we can used to "simulate" button press on the PO
3. MIDI Thru; all midi signal received are send to the MIDI out port
4. MIDI notes/channel/cc can be remaped to user's specs

### 2. Internal synth engine with dedicated sound output
1. Programmed using the Teensy Audio Library
2. 16 Midi controllable parameters
3. Runs on seperate MIDI channel

### 4. Volca FM velocity control
1. Transpose note velocity in to MIDI CC
## Flow Diagram

Here's the signal flow digram for the setup used in the previous video

![Flow](https://raw.githubusercontent.com/PO-MIDI-Adapter/midi-adapter-sofware/master/flow.png)

**Please refer to the [wiki](https://github.com/PO-MIDI-Adapter/midi-adapter-software/wiki) for user instructions**
