#include "Synth1.h"


// GUItool: begin automatically generated code
        AudioSynthWaveformDc     lfoenvelope;    //xy=88,1493
        AudioSynthWaveform       lfo;            //xy=176,1699
        AudioMixer4              mixer1;         //xy=219,1554
        AudioAnalyzePeak         peak1;          //xy=448,1417
        AudioSynthWaveform       voice8b;        //xy=684,2468
        AudioSynthNoiseWhite     voice8n;        //xy=684,2503
        AudioSynthWaveform       voice8a;        //xy=686,2430
        AudioSynthWaveform       voice4a;        //xy=705,1452
        AudioSynthWaveform       voice4b;        //xy=706,1490
        AudioSynthNoiseWhite     voice4n;        //xy=706,1525
        AudioSynthWaveform       voice5b;        //xy=707,1746
        AudioSynthNoiseWhite     voice5n;        //xy=707,1781
        AudioSynthWaveform       voice5a;        //xy=712,1703
        AudioSynthWaveform       voice7b;        //xy=716,2237
        AudioSynthNoiseWhite     voice7n;        //xy=716,2272
        AudioSynthWaveform       voice6b;        //xy=719,2000
        AudioSynthNoiseWhite     voice6n;        //xy=719,2035
        AudioSynthWaveform       voice6a;        //xy=721,1962
        AudioSynthWaveform       voice7a;        //xy=721,2194
        AudioSynthWaveform       voice3b;        //xy=727,1242
        AudioSynthNoiseWhite     voice3n;        //xy=727,1277
        AudioSynthWaveform       voice3a;        //xy=732,1199
        AudioSynthWaveform       voice1b;        //xy=757,776
        AudioSynthNoiseWhite     voice1n;        //xy=760,820
        AudioSynthWaveform       voice2b;        //xy=760,1010
        AudioSynthNoiseWhite     voice2n;        //xy=760,1045
        AudioSynthWaveform       voice1a;        //xy=762,733
        AudioSynthWaveform       voice2a;        //xy=762,972
        AudioSynthWaveformDc     voice8filterenv; //xy=812,2614
        AudioSynthWaveformDc     voice8env;      //xy=826,2553
        AudioMixer4              voice8mix;      //xy=829,2488
        AudioSynthWaveformDc     voice4filterenv; //xy=834,1636
        AudioSynthWaveformDc     voice5filterenv; //xy=835,1892
        AudioSynthWaveformDc     voice7filterenv; //xy=844,2383
        AudioSynthWaveformDc     voice4env;      //xy=848,1575
        AudioSynthWaveformDc     voice6filterenv; //xy=847,2146
        AudioSynthWaveformDc     voice5env;      //xy=849,1831
        AudioMixer4              voice4mix;      //xy=851,1510
        AudioMixer4              voice5mix;      //xy=852,1766
        AudioSynthWaveformDc     voice3filterenv; //xy=855,1388
        AudioSynthWaveformDc     voice7env;      //xy=858,2322
        AudioSynthWaveformDc     voice6env;      //xy=861,2085
        AudioMixer4              voice7mix;      //xy=861,2257
        AudioMixer4              voice6mix;      //xy=864,2020
        AudioSynthWaveformDc     voice3env;      //xy=869,1327
        AudioMixer4              voice3mix;      //xy=872,1262
        AudioSynthWaveformDc     voice1filterenv; //xy=886,912
        AudioSynthWaveformDc     voice2filterenv; //xy=888,1156
        AudioMixer4              voice1mix;      //xy=902,796
        AudioSynthWaveformDc     voice2env;      //xy=902,1095
        AudioSynthWaveformDc     voice1env;      //xy=903,861
        AudioMixer4              voice2mix;      //xy=905,1030
        AudioEffectMultiply      voice8multiply; //xy=993,2526
        AudioMixer4              voice8filtermodmixer; //xy=1003,2642
        AudioEffectMultiply      voice4multiply; //xy=1015,1548
        AudioEffectMultiply      voice5multiply; //xy=1016,1804
        AudioMixer4              voice4filtermodmixer; //xy=1025,1664
        AudioEffectMultiply      voice7multiply; //xy=1025,2295
        AudioEffectMultiply      voice6multiply; //xy=1028,2058
        AudioMixer4              voice5filtermodmixer; //xy=1033,1914
        AudioEffectMultiply      voice3multiply; //xy=1036,1300
        AudioMixer4              voice6filtermodmixer; //xy=1038,2174
        AudioMixer4              voice7filtermodmixer; //xy=1042,2405
        AudioMixer4              voice3filtermodmixer; //xy=1053,1410
        AudioEffectMultiply      voice1multiply; //xy=1066,834
        AudioEffectMultiply      voice2multiply; //xy=1069,1068
        AudioMixer4              voice2filtermodmixer; //xy=1079,1184
        AudioMixer4              voice1filtermodmixer; //xy=1083,944
        AudioFilterStateVariable voice8filter;   //xy=1176,2549
        AudioFilterStateVariable voice5filter;   //xy=1196,1848
        AudioFilterStateVariable voice4filter;   //xy=1198,1571
        AudioFilterStateVariable voice7filter;   //xy=1205,2339
        AudioFilterStateVariable voice6filter;   //xy=1211,2081
        AudioFilterStateVariable voice3filter;   //xy=1216,1344
        AudioFilterStateVariable voice2filter;   //xy=1252,1091
        AudioFilterStateVariable voice1filter;   //xy=1269,886
        AudioMixer4              last4premix;    //xy=1676,1821
        AudioMixer4              first4premix;   //xy=1677,1737
        AudioFilterStateVariable delayFilter;    //xy=2126,1931
        AudioMixer4              mainOutMixer;   //xy=2197,1814
        AudioEffectDelay         delay1;         //xy=2255,2126
        AudioOutputAnalogStereo  dacs1;          //xy=2408.5713844299316,1811.4286804199219
        AudioConnection          patchCord1(lfoenvelope, 0, mixer1, 0);
        AudioConnection          patchCord2(lfo, 0, voice1filtermodmixer, 1);
        AudioConnection          patchCord3(lfo, 0, voice2filtermodmixer, 1);
        AudioConnection          patchCord4(lfo, 0, voice3filtermodmixer, 1);
        AudioConnection          patchCord5(lfo, 0, voice4filtermodmixer, 1);
        AudioConnection          patchCord6(lfo, 0, voice5filtermodmixer, 1);
        AudioConnection          patchCord7(lfo, 0, voice6filtermodmixer, 1);
        AudioConnection          patchCord8(lfo, 0, voice7filtermodmixer, 1);
        AudioConnection          patchCord9(lfo, 0, voice8filtermodmixer, 1);
        AudioConnection          patchCord10(lfo, 0, mixer1, 1);
        AudioConnection          patchCord11(mixer1, peak1);
        AudioConnection          patchCord12(voice8b, 0, voice8mix, 1);
        AudioConnection          patchCord13(voice8n, 0, voice8mix, 2);
        AudioConnection          patchCord14(voice8a, 0, voice8mix, 0);
        AudioConnection          patchCord15(voice4a, 0, voice4mix, 0);
        AudioConnection          patchCord16(voice4b, 0, voice4mix, 1);
        AudioConnection          patchCord17(voice4n, 0, voice4mix, 2);
        AudioConnection          patchCord18(voice5b, 0, voice5mix, 1);
        AudioConnection          patchCord19(voice5n, 0, voice5mix, 2);
        AudioConnection          patchCord20(voice5a, 0, voice5mix, 0);
        AudioConnection          patchCord21(voice7b, 0, voice7mix, 1);
        AudioConnection          patchCord22(voice7n, 0, voice7mix, 2);
        AudioConnection          patchCord23(voice6b, 0, voice6mix, 1);
        AudioConnection          patchCord24(voice6n, 0, voice6mix, 2);
        AudioConnection          patchCord25(voice6a, 0, voice6mix, 0);
        AudioConnection          patchCord26(voice7a, 0, voice7mix, 0);
        AudioConnection          patchCord27(voice3b, 0, voice3mix, 1);
        AudioConnection          patchCord28(voice3n, 0, voice3mix, 2);
        AudioConnection          patchCord29(voice3a, 0, voice3mix, 0);
        AudioConnection          patchCord30(voice1b, 0, voice1mix, 1);
        AudioConnection          patchCord31(voice1n, 0, voice1mix, 2);
        AudioConnection          patchCord32(voice2b, 0, voice2mix, 1);
        AudioConnection          patchCord33(voice2n, 0, voice2mix, 3);
        AudioConnection          patchCord34(voice1a, 0, voice1mix, 0);
        AudioConnection          patchCord35(voice2a, 0, voice2mix, 0);
        AudioConnection          patchCord36(voice8filterenv, 0, voice8filtermodmixer, 0);
        AudioConnection          patchCord37(voice8env, 0, voice8multiply, 1);
        AudioConnection          patchCord38(voice8mix, 0, voice8multiply, 0);
        AudioConnection          patchCord39(voice4filterenv, 0, voice4filtermodmixer, 0);
        AudioConnection          patchCord40(voice5filterenv, 0, voice5filtermodmixer, 0);
        AudioConnection          patchCord41(voice7filterenv, 0, voice7filtermodmixer, 0);
        AudioConnection          patchCord42(voice4env, 0, voice4multiply, 1);
        AudioConnection          patchCord43(voice6filterenv, 0, voice6filtermodmixer, 0);
        AudioConnection          patchCord44(voice5env, 0, voice5multiply, 1);
        AudioConnection          patchCord45(voice4mix, 0, voice4multiply, 0);
        AudioConnection          patchCord46(voice5mix, 0, voice5multiply, 0);
        AudioConnection          patchCord47(voice3filterenv, 0, voice3filtermodmixer, 0);
        AudioConnection          patchCord48(voice7env, 0, voice7multiply, 1);
        AudioConnection          patchCord49(voice6env, 0, voice6multiply, 1);
        AudioConnection          patchCord50(voice7mix, 0, voice7multiply, 0);
        AudioConnection          patchCord51(voice6mix, 0, voice6multiply, 0);
        AudioConnection          patchCord52(voice3env, 0, voice3multiply, 1);
        AudioConnection          patchCord53(voice3mix, 0, voice3multiply, 0);
        AudioConnection          patchCord54(voice1filterenv, 0, voice1filtermodmixer, 0);
        AudioConnection          patchCord55(voice2filterenv, 0, voice2filtermodmixer, 0);
        AudioConnection          patchCord56(voice1mix, 0, voice1multiply, 0);
        AudioConnection          patchCord57(voice2env, 0, voice2multiply, 1);
        AudioConnection          patchCord58(voice1env, 0, voice1multiply, 1);
        AudioConnection          patchCord59(voice2mix, 0, voice2multiply, 0);
        AudioConnection          patchCord60(voice8multiply, 0, voice8filter, 0);
        AudioConnection          patchCord61(voice8filtermodmixer, 0, voice8filter, 1);
        AudioConnection          patchCord62(voice4multiply, 0, voice4filter, 0);
        AudioConnection          patchCord63(voice5multiply, 0, voice5filter, 0);
        AudioConnection          patchCord64(voice4filtermodmixer, 0, voice4filter, 1);
        AudioConnection          patchCord65(voice7multiply, 0, voice7filter, 0);
        AudioConnection          patchCord66(voice6multiply, 0, voice6filter, 0);
        AudioConnection          patchCord67(voice5filtermodmixer, 0, voice5filter, 1);
        AudioConnection          patchCord68(voice3multiply, 0, voice3filter, 0);
        AudioConnection          patchCord69(voice6filtermodmixer, 0, voice6filter, 1);
        AudioConnection          patchCord70(voice7filtermodmixer, 0, voice7filter, 1);
        AudioConnection          patchCord71(voice3filtermodmixer, 0, voice3filter, 1);
        AudioConnection          patchCord72(voice1multiply, 0, voice1filter, 0);
        AudioConnection          patchCord73(voice2multiply, 0, voice2filter, 0);
        AudioConnection          patchCord74(voice2filtermodmixer, 0, voice2filter, 1);
        AudioConnection          patchCord75(voice1filtermodmixer, 0, voice1filter, 1);
        AudioConnection          patchCord76(voice8filter, 0, last4premix, 3);
        AudioConnection          patchCord77(voice5filter, 0, last4premix, 0);
        AudioConnection          patchCord78(voice4filter, 0, first4premix, 3);
        AudioConnection          patchCord79(voice7filter, 0, last4premix, 2);
        AudioConnection          patchCord80(voice6filter, 0, last4premix, 1);
        AudioConnection          patchCord81(voice3filter, 0, first4premix, 2);
        AudioConnection          patchCord82(voice2filter, 0, first4premix, 1);
        AudioConnection          patchCord83(voice1filter, 0, first4premix, 0);
        AudioConnection          patchCord84(last4premix, 0, mainOutMixer, 1);
        AudioConnection          patchCord85(first4premix, 0, mainOutMixer, 0);
        AudioConnection          patchCord86(delayFilter, 0, mainOutMixer, 3);
        AudioConnection          patchCord87(mainOutMixer, delay1);
        AudioConnection          patchCord88(mainOutMixer, 0, dacs1, 0);
        AudioConnection          patchCord89(mainOutMixer, 0, dacs1, 1);
        AudioConnection          patchCord90(delay1, 0, delayFilter, 0);
        // GUItool: end automatically generated code


#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))


Synth1::Synth1(){}

Synth1::~Synth1(){}

void Synth1::init(){
    AudioMemory(400);
      //mix
    first4premix.gain(0, .25);
    first4premix.gain(1, .25);
    first4premix.gain(2, .25);
    first4premix.gain(3, .25);
    last4premix.gain(0, .25);
    last4premix.gain(1, .25);
    last4premix.gain(2, .25);
    last4premix.gain(3, .25);

    //Voice 1
    voice1a.begin(.3,440,WAVEFORM_SQUARE);
    voice1b.begin(.3,440,WAVEFORM_SAWTOOTH);
    //Voice 2
    voice2a.begin(.3,440,WAVEFORM_SQUARE);
    voice2b.begin(.3,440,WAVEFORM_SAWTOOTH);
    //Voice 3
    voice3a.begin(.3,440,WAVEFORM_SQUARE);
    voice3b.begin(.3,440,WAVEFORM_SAWTOOTH);
    //Voice 4
    voice4a.begin(.3,440,WAVEFORM_SQUARE);
    voice4b.begin(.3,440,WAVEFORM_SAWTOOTH);
    //Voice 5
    voice5a.begin(.3,440,WAVEFORM_SQUARE);
    voice5b.begin(.3,440,WAVEFORM_SAWTOOTH);
    //Voice 6
    voice6a.begin(.3,440,WAVEFORM_SQUARE);
    voice6b.begin(.3,440,WAVEFORM_SAWTOOTH);
    //Voice 7
    voice7a.begin(.3,440,WAVEFORM_SQUARE);
    voice7b.begin(.3,440,WAVEFORM_SAWTOOTH);
    //Voice 8
    voice8a.begin(.3,440,WAVEFORM_SQUARE);
    voice8b.begin(.3,440,WAVEFORM_SAWTOOTH);

    delayFilter.frequency(3000);
    delayFilter.resonance(1);
    delay1.delay(0,0);
    mainOutMixer.gain(3,0);

    //LFO
    lfo.begin(1,3,WAVEFORM_SINE);

    vcoOneOct = 1;
    vcoTwoOct = 1;
    deTune = 1;
    deTuneLfo = 1;
    mainOutMixer.gain(0,1);
    mainOutMixer.gain(1,1);
    lfoenvelope.amplitude(1);
    voiceBPulse = false;

    //dacs1.analogReference(INTERNAL);
}
void Synth1::playNote(uint8_t note, uint8_t velocity){
    float vel = log(float(velocity)) / log(float(127));
    if(!polyphony){
        voice1a.frequency(midi_freq[note]*vcoOneOct);
        voice1b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
        voice1env.amplitude(vel,attackTime);
        voice1filterenv.amplitude(vel,attackTimeFilter);
        attackWait[0] = millis();
        noteTrigFlag[0] = note;
    }
    else{
        for(int i = 0; i < LEN(noteTrigFlag) ; i++){
            if((noteTrigFlag[i]) == 0){
                switch(i){
                    case 0:
                        voice1a.frequency(midi_freq[note]*vcoOneOct);
                        voice1b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
                        voice1env.amplitude(vel,attackTime);
                        voice1filterenv.amplitude(vel,attackTimeFilter);
                        attackWait[i] = millis();
                        noteTrigFlag[i] = note;
                        return;
                    case 1:
                        voice2a.frequency(midi_freq[note]*vcoOneOct);
                        voice2b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
                        voice2env.amplitude(vel,attackTime);
                        voice2filterenv.amplitude(vel,attackTimeFilter);
                        attackWait[i] = millis();
                        noteTrigFlag[i] = note;
                        return;
                    case 2:
                        voice3a.frequency(midi_freq[note]*vcoOneOct);
                        voice3b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
                        voice3env.amplitude(vel,attackTime);
                        voice3filterenv.amplitude(vel,attackTimeFilter);
                        attackWait[i] = millis();
                        noteTrigFlag[i] = note;
                        return;
                    case 3:
                        voice3a.frequency(midi_freq[note]*vcoOneOct);
                        voice3b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
                        voice3env.amplitude(vel,attackTime);
                        voice3filterenv.amplitude(vel,attackTimeFilter);
                        attackWait[i] = millis();
                        noteTrigFlag[i] = note;
                        return;
                    case 4:
                        voice4a.frequency(midi_freq[note]*vcoOneOct);
                        voice4b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
                        voice4env.amplitude(vel,attackTime);
                        voice4filterenv.amplitude(vel,attackTimeFilter);
                        attackWait[i] = millis();
                        noteTrigFlag[i] = note;
                        return;
                    case 5:
                        voice5a.frequency(midi_freq[note]*vcoOneOct);
                        voice5b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
                        voice5env.amplitude(vel,attackTime);
                        voice5filterenv.amplitude(vel,attackTimeFilter);
                        attackWait[i] = millis();
                        noteTrigFlag[i] = note;
                        return;
                    case 6:
                        voice6a.frequency(midi_freq[note]*vcoOneOct);
                        voice6b.frequency(((midi_freq[note]*vcoTwoOct) * deTune) * deTuneLfo);
                        voice6env.amplitude(vel,attackTime);
                        voice6filterenv.amplitude(vel,attackTimeFilter);
                        attackWait[i] = millis();
                        noteTrigFlag[i] = note;
                        return;
                }
            }
        }
    }
}

void Synth1::playMonoAftertouch(uint8_t velocity){
    if(!polyphony){
        if(millis() - attackWait[0] > attackTime){
            voice1env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[0] > attackTimeFilter){
            voice1filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }
    }
    else{
        for(int i = 0; i < LEN(noteTrigFlag) ; i++){
            if((noteTrigFlag[i]) != 0){
                Serial.println("af");
                switch(i){
                    case 0:
                        if(millis() - attackWait[i] > attackTime){
                            voice1env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice1filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    break;
                    case 1:
                        if(millis() - attackWait[i] > attackTime){
                            voice2env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice2filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    break;
                    case 2:
                        if(millis() - attackWait[i] > attackTime){
                            voice3env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice3filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    break;
                    case 3:
                        if(millis() - attackWait[i] > attackTime){
                            voice4env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice4filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    break;
                    case 4:
                        if(millis() - attackWait[i] > attackTime){
                            voice5env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice5filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    break;
                    case 6:
                        if(millis() - attackWait[i] > attackTime){
                            voice7env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice7filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    break;
                }
            }
        }
    }
}

void Synth1::playPolyAftertouch(uint8_t midi_note, uint8_t velocity){
    if(!polyphony){
        if(millis() - attackWait[0] > attackTime){
            voice1env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[0] > attackTimeFilter){
            voice1filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }
    }
    else{
        for(int i = 0; i < LEN(noteTrigFlag) ; i++){
            if((noteTrigFlag[i]) == midi_note){
                switch(i){
                    case 0:
                        if(millis() - attackWait[i] > attackTime){
                            voice1env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice1filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    return;
                    case 1:
                        if(millis() - attackWait[i] > attackTime){
                            voice2env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice2filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    return;
                    case 2:
                        if(millis() - attackWait[i] > attackTime){
                            voice3env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice3filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    return;
                    case 3:
                        if(millis() - attackWait[i] > attackTime){
                            voice4env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice4filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    return;
                    case 4:
                        if(millis() - attackWait[i] > attackTime){
                            voice5env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice5filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    return;
                    case 6:
                        if(millis() - attackWait[i] > attackTime){
                            voice7env.amplitude(sustainLevel,decayTime);
                        }
                        if(millis() - attackWait[i] > attackTimeFilter){
                            voice7filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
                        }
                    return;
                }
            }
        }
    }
}

void Synth1::stopNote(uint8_t note){
for(int i = 0; i < LEN(noteTrigFlag) ; i++){
        if((noteTrigFlag[i]) == note){
            noteTrigFlag[i] = 0;
            switch(i){
                case 0:
                    voice1env.amplitude(0,releaseTime);
                    voice1filterenv.amplitude(-1, releaseTimeFilter);
                    return;
                case 1:
                    voice2env.amplitude(0,releaseTime);
                    voice2filterenv.amplitude(-1, releaseTimeFilter);
                    return;
                case 2:
                    voice3env.amplitude(0,releaseTime);
                    voice3filterenv.amplitude(-1, releaseTimeFilter);
                    return;
                case 3:
                    voice4env.amplitude(0,releaseTime);
                    voice4filterenv.amplitude(-1, releaseTimeFilter);
                    return;
                case 4:
                    voice5env.amplitude(0,releaseTime);
                    voice5filterenv.amplitude(-1, releaseTimeFilter);
                    return;
                case 5:
                    voice6env.amplitude(0,releaseTime);
                    voice6filterenv.amplitude(-1, releaseTimeFilter);
                    return;
                case 6:
                    voice7env.amplitude(0,releaseTime);
                    voice7filterenv.amplitude(-1, releaseTimeFilter);
                    return;
            }
        }
    }
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Synth1::changeVCO1Shape(uint32_t cc_value){
    waveShapeOneIndex = cc_value/255;
    if(waveShapeOneIndex < 4){
        voice1a.begin(waveShapes[waveShapeOneIndex]);
        voice2a.begin(waveShapes[waveShapeOneIndex]);
        voice3a.begin(waveShapes[waveShapeOneIndex]);
        voice4a.begin(waveShapes[waveShapeOneIndex]);
        voice5a.begin(waveShapes[waveShapeOneIndex]);
        voice6a.begin(waveShapes[waveShapeOneIndex]);
        voice7a.begin(waveShapes[waveShapeOneIndex]);
        voice8a.begin(waveShapes[waveShapeOneIndex]);
    }
}
void Synth1::changeVCO2Shape(uint32_t cc_value){
    waveShapeOneIndex = cc_value/255;
    if(waveShapeOneIndex < 4){
        if(waveShapeTwoIndex == 3){
        voiceBPulse = true;
        }else{
        voiceBPulse = false;
        }
        voice1b.begin(waveShapes[waveShapeOneIndex]);
        voice2b.begin(waveShapes[waveShapeOneIndex]);
        voice3b.begin(waveShapes[waveShapeOneIndex]);
        voice4b.begin(waveShapes[waveShapeOneIndex]);
        voice5b.begin(waveShapes[waveShapeOneIndex]);
        voice6b.begin(waveShapes[waveShapeOneIndex]);
        voice7b.begin(waveShapes[waveShapeOneIndex]);
        voice8b.begin(waveShapes[waveShapeOneIndex]);
    }
}
void Synth1::changeDetune2(uint32_t cc_value){
    //detune
    deTune = mapfloat(cc_value, 0, 1023, .875, 1.125);
}
void Synth1::changeOct2(uint32_t cc_value){
    octTwoIndex = (cc_value/float(204))+1;
    if(octTwoIndex < 6){
        vcoTwoOct = octArray[octTwoIndex];
    }
}
void Synth1::changeLFOFreq(uint32_t cc_value){
    lfo.frequency(cc_value/50);
}
void Synth1::changeLFOMod(uint32_t cc_value){
    voice1filtermodmixer.gain(1, cc_value/float(512));
    voice2filtermodmixer.gain(1, cc_value/float(512));
    voice3filtermodmixer.gain(1, cc_value/float(512));
    voice4filtermodmixer.gain(1, cc_value/float(512));
    voice5filtermodmixer.gain(1, cc_value/float(512));
    voice6filtermodmixer.gain(1, cc_value/float(512));
    voice7filtermodmixer.gain(1, cc_value/float(512));
    voice8filtermodmixer.gain(1, cc_value/float(512));
    lfo.amplitude(cc_value/3);
}
void Synth1::changeFilterFreq(uint32_t cc_value){
    voice1filter.frequency(cc_value * float(2.5));
    voice2filter.frequency(cc_value * float(2.5));
    voice3filter.frequency(cc_value * float(2.5));
    voice4filter.frequency(cc_value * float(2.5));
    voice5filter.frequency(cc_value * float(2.5));
    voice6filter.frequency(cc_value * float(2.5));
    voice7filter.frequency(cc_value * float(2.5));
    voice8filter.frequency(cc_value * float(2.5));
}
void Synth1::changeFilterRes(uint32_t cc_value){
    voice1filter.resonance((cc_value/float(204))+.9);
    voice2filter.resonance((cc_value/float(204))+.9);
    voice3filter.resonance((cc_value/float(204))+.9);
    voice4filter.resonance((cc_value/float(204))+.9);
    voice5filter.resonance((cc_value/float(204))+.9);
    voice6filter.resonance((cc_value/float(204))+.9);
    voice7filter.resonance((cc_value/float(204))+.9);
    voice8filter.resonance((cc_value/float(204))+.9);
}
void Synth1::changeAttack(uint32_t cc_value){
    attackTime = cc_value*2;
}
void Synth1::changeDecay(uint32_t cc_value){
    decayTime = cc_value * 2;
}
void Synth1::changeSustain(uint32_t cc_value){
    sustainLevel = cc_value/1023;
}
void Synth1::changeRelease(uint32_t cc_value){
    releaseTime = cc_value*2;
}
void Synth1::changeDelayTime(uint32_t cc_value){
    delay1.delay(0, cc_value/float(2.4));
}
void Synth1::changeDelayFeedback(uint32_t cc_value){
    mainOutMixer.gain(3,cc_value/float(1023));
}
void Synth1::changeVolume(uint32_t cc_value){
    mainVolume = mapfloat(cc_value, 0, 1023, 0, 16);
    mainOutMixer.gain(0,mainVolume);
    mainOutMixer.gain(1,mainVolume);
}

void Synth1::changeMix(uint32_t cc_value){
    vcoOneLevel = (cc_value)/float(1023);
    vcoTwoLevel = 1 - (cc_value)/float(1023);
    voice1mix.gain(1,vcoOneLevel);
    voice1mix.gain(0,vcoTwoLevel);
    voice2mix.gain(1,vcoOneLevel);
    voice2mix.gain(0,vcoTwoLevel);
    voice3mix.gain(1,vcoOneLevel);
    voice3mix.gain(0,vcoTwoLevel);
    voice4mix.gain(1,vcoOneLevel);
    voice4mix.gain(0,vcoTwoLevel);
    voice5mix.gain(1,vcoOneLevel);
    voice5mix.gain(0,vcoTwoLevel);
    voice6mix.gain(1,vcoOneLevel);
    voice6mix.gain(0,vcoTwoLevel);
    voice7mix.gain(1,vcoOneLevel);
    voice7mix.gain(0,vcoTwoLevel);
    voice8mix.gain(1,vcoOneLevel);
    voice8mix.gain(0,vcoTwoLevel);
}

void Synth1::changePolyphony(uint32_t cc_value){
    if (cc_value == 0){
        polyphony = false;
    }
    else{
        polyphony = true;
    }
}
