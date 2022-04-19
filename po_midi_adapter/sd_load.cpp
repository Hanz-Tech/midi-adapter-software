/*!
 *  @file       sd_load.cpp
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


#include "sd_load.h"
const char CONFIG_FILE[] = "config.cfg";
const int chipSelect = BUILTIN_SDCARD;
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))

bool loadSDConfig();



SD_Load::SD_Load(){
  if (SD.begin(chipSelect)){
    //Serial.println("card init");
    if(this->loadSDConfig()){
      digitalWrite(13, HIGH);   // set the LED on
      delay(100);                  // wait for a second
      digitalWrite(13, LOW);    // set the LED off
      delay(100);
      digitalWrite(13, HIGH);   // set the LED on
      delay(100);                  // wait for a second
      digitalWrite(13, LOW);    // set the LED off
      delay(100);
      digitalWrite(13, HIGH);   // set the LED on
      delay(100);                  // wait for a second
      digitalWrite(13, LOW);    // set the LED off
    }
  }
}

bool SD_Load::loadSDConfig(){
  SDConfigFile cfg;
  const uint8_t CONFIG_LINE_LENGTH = 127;
  if(!cfg.begin(CONFIG_FILE, CONFIG_LINE_LENGTH)){
    Serial.println("cfg failed");
    return false;
  }
  while (cfg.readNextSetting()){
    for(int i = 1 ; i < LEN(_midi_note_str); i++){
      if(cfg.nameIs(_midi_note_str[i])){
        _midi_note[i] = cfg.getIntValue();
        _note_map[i-1][0] = cfg.getIntValue();
        //Serial.println("note found");
        //Serial.println(midi_note[i]);
        break;
      }
    }
    for(int i = 1 ; i < LEN(_midi_note_record_str); i++){
      if(cfg.nameIs(_midi_note_record_str[i])){
        _midi_record_note[i] = cfg.getIntValue();
        _record_note_map[i-1][0] = cfg.getIntValue();
        break;
      }
    }
    for(int i = 0 ; i < LEN(_midi_cc_knob_str); i++){
      if(cfg.nameIs(_midi_cc_knob_str[i])){
        _midi_cc_knob[i] = cfg.getIntValue();
        //Serial.println("cc found");
        break;
      }
    }

    for(int i = 0 ; i < LEN(_looper_control_note); i++){
      if(cfg.nameIs(_looper_control_note_str[i])){
        _looper_control_note[i] = cfg.getIntValue();
        break;
      }
    }
    if(cfg.nameIs("po_midi_channel")){
      _po_midi_channel = cfg.getIntValue();
    }
    else if(cfg.nameIs("synth_midi_channel")){
      _synth_midi_channel = cfg.getIntValue();
    }
    else if(cfg.nameIs("disable_transport")){
      _disable_transport = cfg.getIntValue();
    }
    else if(cfg.nameIs("po_cc_control")){
      _po_cc_control = cfg.getIntValue();
    }
    else if(cfg.nameIs("volca_fm_velocity")){
      _volca_fm_velocity = cfg.getIntValue();
    }
    else if(cfg.nameIs("volca_fm_midi_ch_1")){
      _volca_fm_midi_ch_1 = cfg.getIntValue();
    }
    else if(cfg.nameIs("volca_fm_midi_ch_2")){
      _volca_fm_midi_ch_2 = cfg.getIntValue();
    }
    else if(cfg.nameIs("sync_out_enabled")){
      _sync_out_enabled = cfg.getIntValue();
    }
    else if(cfg.nameIs("midi_ppqn")){
      _midi_ppqn = cfg.getIntValue();
    }
    else if(cfg.nameIs("looper_enabled")){
      _looper_enabled = cfg.getIntValue();
    }
    else if (cfg.nameIs("looper_autoplay_after_record")){
      _looper_autoplay = cfg.getIntValue();
    }
    else if (cfg.nameIs("looper_transport_control_link")){
      _looper_transport_control_link = cfg.getIntValue();
    }
    else if (cfg.nameIs("looper_quantized")){
      _looper_quantized = cfg.getIntValue();
    } 
    else if (cfg.nameIs("ble_midi_enabled")) {
      _esp32_enabled = cfg.getIntValue();
    }
  }
  cfg.end();
  return true;
}
