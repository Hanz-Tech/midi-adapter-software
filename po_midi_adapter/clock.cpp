/*!
 *  @file       clock.cpp
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




#include "clock.h"


static int getBPMOrPulseLength(int fromValue) {
  return ceil(float(30000) / fromValue);
}

Clock::Clock(uint8_t pin_sync_out){
    _pin_sync_out = pin_sync_out;
    digitalWrite(_pin_sync_out, LOW);
}

void Clock::stop(){
  _isStarted = false;
}

void Clock::start(){
  _isStarted = true;
}

void Clock::setBPM(int newBpm) {
  _bpm = newBpm;
  if(newBpm >= MIN_BPM && newBpm <= MAX_BPM){
    _pulseDuration = getBPMOrPulseLength(_bpm);
  }
}

void Clock::sendBPM(unsigned long curTime) {
  if(_isStarted){
    if (_isLow) {
        // see if we need to go high
        _clickDuration = curTime - _lastTrig;
  
        if (_clickDuration >= _pulseDuration) {
          //go high
          _isLow = false;
          _lastTrig = curTime;
        }
    } else {
      // go low if we need to stop clicking
      _isLow = (curTime >= _lastTrig + CLICK_HIGH_DURATION);
    }
    analogWrite(_pin_sync_out, _isLow ? 0 : 255);
  }
  else{
    digitalWrite(_pin_sync_out, LOW);
  }
}

bool Clock::getStatus() {
  return _isStarted;
}
