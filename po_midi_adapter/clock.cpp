#include "clock.h"

Clock::Clock(uint8_t sync_pin){
    pin_sync_out = sync_pin;
}

void Clock::updateTempo() {
  millis_per_step = millis() - last_step;
}

void Clock::advance() {
  last_step = millis();;
  step = (step + 1) % steps;
  if((step * sync_out_ppqn * 2 / sync_in_ppqn) & 1) {
    analogWrite(pin_sync_out, 0);
  } else {
    analogWrite(pin_sync_out, 255); //3v
  }
}