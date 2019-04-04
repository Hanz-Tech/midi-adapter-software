#ifndef CLOCK_H
#define CLOCK_H
#include <Arduino.h>

class Clock{
    public:
        Clock(uint8_t sync_pin);
        void advance();
        void updateTempo();

    private:
        int pin_sync_out = 0;
        int sync_in_ppqn = 24;
        int sync_out_ppqn = 1;
        int sync_out_qn_align = 16;

        int steps = sync_in_ppqn * sync_out_qn_align / sync_out_ppqn / 2;

        int start_step = steps - 1;
        int step = start_step - 1;
        int running = 0;

        enum State
        {
        UsbClock,
        SyncInClock,
        InternalClock,
        Idle
        } state = Idle;
        long last_step = millis();
        long millis_per_step = 0;

};


#endif