#include "clock.h"


static int getBPMOrPulseLength(int fromValue) {
  return ceil(float(30000) / fromValue);
}

Clock::Clock(uint8_t pin_sync_out){
    _pin_sync_out = pin_sync_out;
    analogWrite(_pin_sync_out,0);
}

void Clock::setBPM(int newBpm) {
  _bpm = newBpm;
  if(newBpm >= MIN_BPM && newBpm <= MAX_BPM){
    _pulseDuration = getBPMOrPulseLength(_bpm);
  }
}

void Clock::sendBPM(unsigned long curTime) {
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

