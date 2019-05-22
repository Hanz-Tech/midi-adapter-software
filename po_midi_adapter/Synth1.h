//Based on https://github.com/otem/teensypolysynth

#ifndef SYNTH1_H
#define SYNTH1_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>




class Synth1{
    public:
        Synth1();
        ~Synth1();
        void init();
        void playNote(uint8_t midi_note, uint8_t velocity);
        void playPolyAftertouch(uint8_t midi_note, uint8_t velocity);
        void playMonoAftertouch(uint8_t velocity);
        void stopNote(uint8_t midi_note);
        void changeVCO1Shape(uint32_t cc_value);
        void changeVCO2Shape(uint32_t cc_value);
        void changeDetune2(uint32_t cc_value);
        void changeOct2(uint32_t cc_value);
        void changeLFOFreq(uint32_t cc_value);
        void changeLFOMod(uint32_t cc_value);
        void changeFilterFreq(uint32_t cc_value);
        void changeFilterRes(uint32_t cc_value);
        void changeAttack(uint32_t cc_value);
        void changeDecay(uint32_t cc_value);
        void changeSustain(uint32_t cc_value);
        void changeRelease(uint32_t cc_value);
        void changeDelayTime(uint32_t cc_value);
        void changeDelayFeedback(uint32_t cc_value);
        void changeVolume(uint32_t cc_value);
        void stub(uint32_t note){};
        void changeMix(uint32_t cc_value);
        void changePolyphony(uint32_t cc_value);
    private:
        //synth
        float mainVolume;
        int tempLineOutLevel;
        float vcoOneLevel;
        float vcoTwoLevel;
        int vcoOneOct;
        float vcoTwoOct;
        float octArray[6] = {0.25,0.5,1,2,4,8};
        float deTune;
        int waveShapeOneIndex;
        int waveShapeTwoIndex;
        int lfoWaveShapeIndex;
        int octOneIndex;
        int octTwoIndex;
        //WaveShapes
        short waveShapes[4] = {
            WAVEFORM_SINE,
            WAVEFORM_SAWTOOTH,
            WAVEFORM_SQUARE,
            WAVEFORM_PULSE,
        };
        bool voiceBPulse;
        float tempDetuneMod;
        float deTuneLfo;
        //LFO WaveShapes
        short lfoWaveShapes[5] = {
            WAVEFORM_SINE,
            WAVEFORM_SAWTOOTH,
            WAVEFORM_SAWTOOTH_REVERSE,
            WAVEFORM_SQUARE,
            WAVEFORM_SAMPLE_HOLD,
        };
        //ADSR
        int attackTime = 1;
        int decayTime = 1;
        float sustainLevel = 1;
        int releaseTime = 1;
        //Filter ADSR
        int attackTimeFilter = 0;
        int decayTimeFilter = 0;
        float sustainLevelFilter = 0;
        int releaseTimeFilter = 0;

        bool polyphony = true;
        uint8_t noteTrigFlag[8] = {0,0,0,0,0,0,0,0};
        long attackWait[8];
        float midi_freq[128] = {
          8.175798915643707,
          8.661957218027252,
          9.177023997418987,
          9.722718241315029,
          10.300861153527185,
          10.913382232281371,
          11.562325709738575,
          12.249857374429665,
          12.978271799373285,
          13.75,
          14.56761754744031,
          15.433853164253879,
          16.351597831287414,
          17.323914436054505,
          18.354047994837973,
          19.445436482630058,
          20.60172230705437,
          21.826764464562743,
          23.12465141947715,
          24.49971474885933,
          25.95654359874657,
          27.5,
          29.13523509488062,
          30.867706328507758,
          32.70319566257483,
          34.64782887210901,
          36.70809598967595,
          38.890872965260115,
          41.20344461410874,
          43.653528929125486,
          46.2493028389543,
          48.99942949771866,
          51.91308719749314,
          55.0,
          58.27047018976124,
          61.7354126570155,
          65.40639132514966,
          69.29565774421802,
          73.41619197935188,
          77.78174593052023,
          82.4068892282175,
          87.30705785825097,
          92.4986056779086,
          97.99885899543733,
          103.82617439498628,
          110.0,
          116.54094037952248,
          123.470825314031,
          130.8127826502993,
          138.59131548843604,
          146.83238395870376,
          155.56349186104046,
          164.813778456435,
          174.61411571650194,
          184.9972113558172,
          195.99771799087466,
          207.65234878997256,
          220.0,
          233.0818807590449,
          246.94165062806212,
          261.6255653005986,
          277.1826309768721,
          293.66476791740763,
          311.1269837220809,
          329.62755691286986,
          349.22823143300394,
          369.9944227116344,
          391.9954359817492,
          415.3046975799452,
          440.0,
          466.1637615180898,
          493.88330125612424,
          523.2511306011972,
          554.3652619537442,
          587.3295358348153,
          622.2539674441618,
          659.2551138257397,
          698.4564628660079,
          739.9888454232688,
          783.9908719634984,
          830.6093951598904,
          880.0,
          932.3275230361796,
          987.7666025122485,
          1046.5022612023945,
          1108.7305239074883,
          1174.6590716696305,
          1244.5079348883237,
          1318.5102276514795,
          1396.9129257320158,
          1479.9776908465376,
          1567.9817439269968,
          1661.2187903197807,
          1760.0,
          1864.6550460723593,
          1975.533205024497,
          2093.004522404789,
          2217.4610478149766,
          2349.318143339261,
          2489.0158697766474,
          2637.020455302959,
          2793.8258514640315,
          2959.955381693075,
          3135.9634878539937,
          3322.4375806395615,
          3520.0,
          3729.3100921447212,
          3951.0664100489917,
          4186.009044809578,
          4434.922095629955,
          4698.636286678519,
          4978.031739553295,
          5274.040910605921,
          5587.65170292806,
          5919.91076338615,
          6271.926975707992,
          6644.875161279119,
          7040.0,
          7458.6201842894425,
          7902.132820097983,
          8372.018089619156,
          8869.84419125991,
          9397.272573357039,
          9956.06347910659,
          10548.081821211843,
          11175.30340585612,
          11839.8215267723,
          12543.853951415984
        };

};



#endif
