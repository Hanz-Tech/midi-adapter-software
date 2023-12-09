/*!
 *  @file       storage.h
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

#ifndef STORAGE_H
#define STORAGE_H
#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
#include <SDConfigFile.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include "po_settings.h"
#include "global.h"
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))
class Storage{
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
      int _looper_enabled = 1;
      int _looper_autoplay = 1;
      int _looper_transport_control_link = 1;
      int _looper_quantized = 0;
      int _esp32_enabled = 1;
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
      const char *_midi_note_str[24] = {
          "0",
          "midi_note_1",
          "midi_note_2",
          "midi_note_3",
          "midi_note_4",
          "midi_note_5",
          "midi_note_6",
          "midi_note_7",
          "midi_note_8",
          "midi_note_9",
          "midi_note_10",
          "midi_note_11",
          "midi_note_12",
          "midi_note_13",
          "midi_note_14",
          "midi_note_15",
          "midi_note_16",
          "midi_note_sound",
          "midi_note_pattern",
          "midi_note_bpm",
          "midi_note_special",
          "midi_note_fx",
          "midi_note_play",
          "midi_note_write",
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
      
      //Midi Notes, these are used for one button record
      const char *_midi_note_record_str[17] = {
          "0",
          "midi_note_record_1",
          "midi_note_record_2",
          "midi_note_record_3",
          "midi_note_record_4",
          "midi_note_record_5",
          "midi_note_record_6",
          "midi_note_record_7",
          "midi_note_record_8",
          "midi_note_record_9",
          "midi_note_record_10",
          "midi_note_record_11",
          "midi_note_record_12",
          "midi_note_record_13",
          "midi_note_record_14",
          "midi_note_record_15",
          "midi_note_record_16",
      };
      uint8_t _midi_record_note[17] = {
          0,
          38,
          39,
          40,
          41,
          42,
          43,
          44,
          45,
          46,
          47,
          48,
          49,
          50,
          51,
          52,
          53,
      };
      uint8_t _record_note_map[16][2] = {
        {_midi_record_note[1],PO_BUTTON_1},
        {_midi_record_note[2],PO_BUTTON_2},
        {_midi_record_note[3],PO_BUTTON_3},
        {_midi_record_note[4],PO_BUTTON_4},
        {_midi_record_note[5],PO_BUTTON_5},
        {_midi_record_note[6],PO_BUTTON_6},
        {_midi_record_note[7],PO_BUTTON_7},
        {_midi_record_note[8],PO_BUTTON_8},
        {_midi_record_note[9],PO_BUTTON_9},
        {_midi_record_note[10],PO_BUTTON_10},
        {_midi_record_note[11],PO_BUTTON_11},
        {_midi_record_note[12],PO_BUTTON_12},
        {_midi_record_note[13],PO_BUTTON_13},
        {_midi_record_note[14],PO_BUTTON_14},
        {_midi_record_note[15],PO_BUTTON_15},
        {_midi_record_note[16],PO_BUTTON_16}
      };

      //Midi Notes, these are used for switching modes
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
      const char *_midi_cc_knob_str[17] = {
          "0",
          "midi_cc_knob_1",
          "midi_cc_knob_2",
          "midi_cc_knob_3",
          "midi_cc_knob_4",
          "midi_cc_knob_5",
          "midi_cc_knob_6",
          "midi_cc_knob_7",
          "midi_cc_knob_8",
          "midi_cc_knob_9",
          "midi_cc_knob_10",
          "midi_cc_knob_11",
          "midi_cc_knob_12",
          "midi_cc_knob_13",
          "midi_cc_knob_14",
          "midi_cc_knob_15",
          "midi_cc_knob_16"
      };
      
      //Midi notes for transport functions
      uint8_t _transport_note_map[7][2] = {
      {_midi_note[9],PO_BUTTON_SOUND},
      {_midi_note[10],PO_BUTTON_PATTERN},
      {_midi_note[11],PO_BUTTON_BPM},
      {_midi_note[1],PO_BUTTON_SPECIAL},
      {_midi_note[2],PO_BUTTON_FX},
      {_midi_note[3],PO_BUTTON_PLAY},
      {_midi_note[4],PO_BUTTON_WRITE}
      };

      uint8_t _looper_control_note[2] = {
        49, //start-stop
        51, //clear
      };

      const char *_looper_control_note_str[2] = {
        "midi_note_loop_start_stop",
        "midi_note_loop_clear"
      };
      bool loadSDConfig();
      bool loadEepromConfig();
      bool readEeprom(DynamicJsonDocument& po_config);
      bool writeEeprom(DynamicJsonDocument& json);
      void printArray( uint8_t a[][ 2 ] ) {
        // loop through array's rows
        for ( int i = 0; i < 16; ++i ) {
            // loop through columns of current row
            for ( int j = 0; j < 2; ++j )
              Serial.print (a[ i ][ j ] );
              Serial.print ("\r" ) ; // start new line of output
        } 
      // end outer for
      } 
    public:
      Storage();
      int get_po_midi_channel(){ return _po_midi_channel; }
      int get_synth_midi_channel(){ return _synth_midi_channel; }
      int get_disable_transport(){ return _disable_transport; }
      int get_po_cc_control(){ return _po_cc_control; }
      int get_volca_fm_velocity(){ return _volca_fm_velocity; }
      int get_volca_fm_midi_ch_1(){ return _volca_fm_midi_ch_1; }
      int get_volca_fm_midi_ch_2(){ return _volca_fm_midi_ch_2; }
      int get_sync_out_enabled(){ return _sync_out_enabled; }
      int get_midi_ppqn(){ return _midi_ppqn; }
      int get_is_looper_enabled(){ return _looper_enabled; }
      int get_is_looper_autoplay(){ return _looper_autoplay; }
      int get_looper_transport_control_link(){ return _looper_transport_control_link; }
      int get_is_looper_quantized(){ return _looper_quantized; }
      int get_is_esp32_enabled() { return _esp32_enabled; }
      
      void get_note_map(uint8_t note_map[23][2]) { 
        for (int i = 0; i < 23; i++){
          for (int j = 0; j < 2; j++){
            note_map[i][j] = _note_map[i][j];
          }
        }
      }
      void get_record_note_map(uint8_t record_note_map[16][2]) { 
        for (int i = 0; i < 16; i++){
          for (int j = 0; j < 2; j++){
            record_note_map[i][j] = _record_note_map[i][j];
          }
        }
      }
      void get_looper_control(uint8_t looper_control_note[2]){
        for (int i = 0; i < 2 ; i++){
          looper_control_note[i]  = _looper_control_note[i];
        }
      }

      void get_transport_note_map(uint8_t transport_note_map[7][2]){
          for (int i = 0; i < 7; i++){
            for (int j = 0; j < 2; j++){
              transport_note_map[i][j] = _transport_note_map[i][j];
            }
          }
        }
      void get_midi_cc_knob(uint8_t midi_cc_knob[17]) {
        for(int i = 0; i < 17; i++){
          midi_cc_knob[i] = _midi_cc_knob[i];
        }
      }
      bool checkforUpdate();

};

#endif
