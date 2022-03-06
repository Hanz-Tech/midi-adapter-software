/*!
 *  @file       clock.h
 *  Project     Pocket Operator MIDI Adapter
 *  @brief      Pocket Operator MIDI Adapter
 *  @author     Hanz Tech Inc
 *  @date       2022/03/06
 *  @license    MIT - Copyright (c) 2022 Hanz Tech Inc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */



#ifndef CLOCK_H
#define CLOCK_H
#include <Arduino.h>

#define MIN_BPM 60
#define MAX_BPM 240
#define CLICK_HIGH_DURATION 6
class Clock{
    public:
        Clock(uint8_t pin_sync_out);
        void setBPM(int bpm);
        void sendBPM(unsigned long curTime);
        void stop();
        void start();
        bool getStatus();
        int getBpm(){return _bpm;}

    private:
        int _pin_sync_out = 0;
        unsigned long _lastTrig = 0;
        bool _isLow = 0;
        int _pulseDuration = 0;
        int _bpm = 120;
        int _clickDuration = 0;
        bool _isStarted = false;

};


#endif
