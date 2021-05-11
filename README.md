

Buy it Here 

<a href="https://www.tindie.com/stores/hanztech/?ref=offsite_badges&utm_source=sellers_bobthesheep&utm_medium=badges&utm_campaign=badge_medium"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-mediums.png" alt="I sell on Tindie" width="150" height="78"></a>

[Etsy](https://www.etsy.com/ca/HanzTechInc/listing/979132858/pocket-operator-midi-adapter-v2)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Disclaimer

Copyright 2021 Hanz Tech Inc

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# Overview

In this repository you will find the firmware for the pocket operator midi adapter. Hardware stuff can be found [here](https://github.com/PO-MIDI-Adapter/midi-adapter-v2-hardware)

The code will only work on a **Teensy 4.1**

[![PO-MA](https://raw.githubusercontent.com/PO-MIDI-Adapter/midi-adapter-hardware/master/photos/title.jpg)](https://www.youtube.com/watch?v=iIQ18DAJAU0 "PO-MA")

## Main Features

### 1.Make any Pocket operator MIDI compatible
1. The adapter can act as a MIDI device and recveive MIDI signal via the micro USB port or MIDI IN port
2. The adapter can act as a USB host. It can power on and receive signal from one or more MIDI controllers directly
3. Specified MIDI signals are tranposed into GPIO output of the Teensy which we can used to "simulate" button press on the PO
3. MIDI Thru; all midi signal received are send to the MIDI out port
4. MIDI notes/channel/cc can be remaped to user's specs


### 2. MIDI Merging
1. Capable of hosting multiple USB MIDI controllers, receving MIDI IN and merging all signal together into a 5-DIN MIDI OUTPUT and a USB MIDI Output
2. Can acts as a MIDI compliant USB device

### 4. Volca FM velocity control
1. Transpose note velocity in to MIDI CC

**Please refer to the [wiki](https://github.com/PO-MIDI-Adapter/midi-adapter-software/wiki) for build and user instructions**

