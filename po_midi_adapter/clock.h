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
