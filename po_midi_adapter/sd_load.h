#ifndef SD_LOAD_H
#define SD_LOAD_H
#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
#include <SDConfigFile.h>
#include "po_settings.h"
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))
class SD_Load{
    private:
        int _po_midi_channel = 1;
        int _synth_midi_channel = 2;
        int _disable_transport = 1; //1 == disable transport, 0 == enabled transport
        int _po_cc_control = 0; //0 == disable , 1 ==enable
        int _volca_fm_velocity = 1; // 1 == enable, 0 == disable
        int _volca_fm_midi_ch_1 = 13;
        int _volca_fm_midi_ch_2 = 16;
        int _sync_out_enabled = 1;
        int _midi_ppqn = 24;

        //Midi Notes, these are used to trigger button 1-16 and sound,pattern.bpm....
        uint8_t _midi_note[24] = { //These are midi notes value
        0,
        68,
        69,
        70,
        71,
        72,
        73,
        74,
        75,
        60,
        61,
        62,
        63,
        64,
        65,
        66,
        67,
        76,
        77,
        78,
        79,
        80,
        81,
        82,
        };

        uint8_t _midi_cc_knob[17] = {
        0,
        1,  //Synth : vco1 shape
        2,  //Synth : vco2 shape
        3,  //Synth : Detune vco2
        4,  //Synth : vco 2 octave
        5,  //Synth : LFO Freq
        6,  //Synth : LFO Mod
        7,  //Synth : Filter Freq
        8,  //Synth : Filter Res
        9,   //PO : mode, mode 0 : normal , mode 1 : fx, mode 2 : record , mode 3 : write   //Synth : Attack
        10,  //PO : sound 1-16    //Synth : Decay
        11,  //PO : pattern 1-16  //Synth : Sustain
        12,  //PO : volume 1-16   //Synth : Released
        13,  //Synth : Delay time
        14,  //Synth : Delay feedback
        15,  //Synth : Mix
        16   //Synth : Volume
        };

        uint8_t _note_map[23][2] = {
        {_midi_note[1],PO_BUTTON_1},
        {_midi_note[2],PO_BUTTON_2},
        {_midi_note[3],PO_BUTTON_3},
        {_midi_note[4],PO_BUTTON_4},
        {_midi_note[5],PO_BUTTON_5},
        {_midi_note[6],PO_BUTTON_6},
        {_midi_note[7],PO_BUTTON_7},
        {_midi_note[8],PO_BUTTON_8},
        {_midi_note[9],PO_BUTTON_9},
        {_midi_note[10],PO_BUTTON_10},
        {_midi_note[11],PO_BUTTON_11},
        {_midi_note[12],PO_BUTTON_12},
        {_midi_note[13],PO_BUTTON_13},
        {_midi_note[14],PO_BUTTON_14},
        {_midi_note[15],PO_BUTTON_15},
        {_midi_note[16],PO_BUTTON_16},
        {_midi_note[17],PO_BUTTON_SOUND},
        {_midi_note[18],PO_BUTTON_PATTERN},
        {_midi_note[19],PO_BUTTON_BPM},
        {_midi_note[20],PO_BUTTON_SPECIAL},
        {_midi_note[21],PO_BUTTON_FX},
        {_midi_note[22],PO_BUTTON_PLAY},
        {_midi_note[23],PO_BUTTON_WRITE},
        };

        uint8_t _transport_note_map[7][2] ={
        {_midi_note[9],PO_BUTTON_SOUND},
        {_midi_note[10],PO_BUTTON_PATTERN},
        {_midi_note[11],PO_BUTTON_BPM},
        {_midi_note[1],PO_BUTTON_SPECIAL},
        {_midi_note[2],PO_BUTTON_FX},
        {_midi_note[3],PO_BUTTON_PLAY},
        {_midi_note[4],PO_BUTTON_WRITE}
        };
        bool loadSDConfig();
    public:
        SD_Load();
        int get_po_midi_channel(){ return _po_midi_channel; }
        int get_synth_midi_channel(){ return _synth_midi_channel; }
        int get_disable_transport(){ return _disable_transport; }
        int get_po_cc_control(){ return _po_cc_control; }
        int get_volca_fm_velocity(){ return _volca_fm_velocity; }
        int get_volca_fm_midi_ch_1(){ return _volca_fm_midi_ch_1; }
        int get_volca_fm_midi_ch_2(){ return _volca_fm_midi_ch_2; }
        int get_sync_out_enabled(){ return _sync_out_enabled; }
        int get_midi_ppqn(){ return _midi_ppqn; }
        void get_note_map( uint8_t note_map[23][2]) { note_map = _note_map; }
        void get_transport_note_map(uint8_t transport_note_map[7][2]){ transport_note_map = _transport_note_map;}
        void get_midi_cc_knob(uint8_t midi_cc_knob[17]) { midi_cc_knob = _midi_cc_knob; }
};

#endif