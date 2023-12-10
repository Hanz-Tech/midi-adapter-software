/*!
 *  @file       storage.cpp
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


#include "storage.h"
const char CONFIG_FILE[] = "config.cfg";
const int chipSelect = BUILTIN_SDCARD;
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))

bool loadSDConfig();
bool loadEepromConfig();

static bool _isValidMidiValue(int value) {
  return (value >= 0 && value <= 127) || value == 255;
}



static DynamicJsonDocument _cmdStats(64);
static DynamicJsonDocument _cur_po_config(2048);
static DynamicJsonDocument _eepromAddresses(2048);

Storage::Storage() {
  if (SD.begin(chipSelect)){
    Serial.println("card init");
    if(this->loadSDConfig()){
      digitalWrite(LED_PIN, HIGH);   // set the LED on
      delay(100);                  // wait for a second
      digitalWrite(LED_PIN, LOW);    // set the LED off
      delay(100);
      digitalWrite(LED_PIN, HIGH);   // set the LED on
      delay(100);                  // wait for a second
      digitalWrite(LED_PIN, LOW);    // set the LED off
      delay(100);
      digitalWrite(LED_PIN, HIGH);   // set the LED on
      delay(100);                  // wait for a second
      digitalWrite(LED_PIN, LOW);    // set the LED off
    }
  } else {
      _cur_po_config["midi_note_1"] = 68;
      _cur_po_config["midi_note_2"] = 69;
      _cur_po_config["midi_note_3"] = 70;
      _cur_po_config["midi_note_4"] = 71;
      _cur_po_config["midi_note_5"] = 72;
      _cur_po_config["midi_note_6"] = 73;
      _cur_po_config["midi_note_7"] = 74;
      _cur_po_config["midi_note_8"] = 75;
      _cur_po_config["midi_note_9"] = 60;
      _cur_po_config["midi_note_10"] = 61;
      _cur_po_config["midi_note_11"] = 62;
      _cur_po_config["midi_note_12"] = 63;
      _cur_po_config["midi_note_13"] = 64;
      _cur_po_config["midi_note_14"] = 65;
      _cur_po_config["midi_note_15"] = 66;
      _cur_po_config["midi_note_16"] = 67;
      _cur_po_config["midi_note_sound"] = 76;
      _cur_po_config["midi_note_pattern"] = 77;
      _cur_po_config["midi_note_bpm"] = 81;
      _cur_po_config["midi_note_special"] = 79;
      _cur_po_config["midi_note_fx"] = 80;
      _cur_po_config["midi_note_play"] = 78;
      _cur_po_config["midi_note_write"] = 82;
      _cur_po_config["po_midi_channel"] = 1;
      _cur_po_config["disable_transport"] = 1;
      _cur_po_config["po_cc_control"] = 0;
      _cur_po_config["volca_fm_velocity"] = 1;
      _cur_po_config["volca_fm_midi_ch_1"] = 13;
      _cur_po_config["volca_fm_midi_ch_2"] = 16;
      _cur_po_config["sync_out_enabled"] = 1;
      _cur_po_config["midi_ppqn"] = 24;
      _cur_po_config["midi_note_record_1"] = 48;
      _cur_po_config["midi_note_record_2"] = 10;
      _cur_po_config["midi_note_record_3"] = 11;
      _cur_po_config["midi_note_record_4"] = 12;
      _cur_po_config["midi_note_record_5"] = 13;
      _cur_po_config["midi_note_record_6"] = 14;
      _cur_po_config["midi_note_record_7"] = 15;
      _cur_po_config["midi_note_record_8"] = 16;
      _cur_po_config["midi_note_record_9"] = 17;
      _cur_po_config["midi_note_record_10"] = 18;
      _cur_po_config["midi_note_record_11"] = 19;
      _cur_po_config["midi_note_record_12"] = 20;
      _cur_po_config["midi_note_record_13"] = 21;
      _cur_po_config["midi_note_record_14"] = 22;
      _cur_po_config["midi_note_record_15"] = 23;
      _cur_po_config["midi_note_record_16"] = 24;
      _cur_po_config["looper_enabled"] = 1;
      _cur_po_config["looper_autoplay_after_record"] = 1;
      _cur_po_config["looper_transport_control_link"] = 0;
      _cur_po_config["midi_note_loop_start_stop"] = 49;
      _cur_po_config["midi_note_loop_clear"] = 50;
      _cur_po_config["looper_quantized"] = 1;
      _cur_po_config["ble_midi_enabled"] = 1;
      _cur_po_config["midi_cc_knob_9"] = 67;
      _cur_po_config["version"]= FIRMWARE_VERSION;
      _eepromAddresses["midi_note_1"] = 1;
      _eepromAddresses["midi_note_2"] = 2;
      _eepromAddresses["midi_note_3"] = 3;
      _eepromAddresses["midi_note_4"] = 4;
      _eepromAddresses["midi_note_5"] = 5;
      _eepromAddresses["midi_note_6"] = 6;
      _eepromAddresses["midi_note_7"] = 7;
      _eepromAddresses["midi_note_8"] = 8;
      _eepromAddresses["midi_note_9"] = 9;
      _eepromAddresses["midi_note_10"] = 10;
      _eepromAddresses["midi_note_11"] = 11;
      _eepromAddresses["midi_note_12"] = 12;
      _eepromAddresses["midi_note_13"] = 13;
      _eepromAddresses["midi_note_14"] = 14;
      _eepromAddresses["midi_note_15"] = 15;
      _eepromAddresses["midi_note_16"] = 16;
      _eepromAddresses["midi_note_sound"] = 17;
      _eepromAddresses["midi_note_pattern"] = 18;
      _eepromAddresses["midi_note_bpm"] = 19;
      _eepromAddresses["midi_note_special"] = 20;
      _eepromAddresses["midi_note_fx"] = 21;
      _eepromAddresses["midi_note_play"] = 22;
      _eepromAddresses["midi_note_write"] = 23;
      _eepromAddresses["po_midi_channel"] = 24;
      _eepromAddresses["disable_transport"] = 26;
      _eepromAddresses["po_cc_control"] = 27;
      _eepromAddresses["volca_fm_velocity"] = 28;
      _eepromAddresses["volca_fm_midi_ch_1"] = 29;
      _eepromAddresses["volca_fm_midi_ch_2"] = 30;
      _eepromAddresses["sync_out_enabled"] = 31;
      _eepromAddresses["midi_ppqn"] = 33;
      _eepromAddresses["midi_note_record_1"] = 34;
      _eepromAddresses["midi_note_record_2"] = 35;
      _eepromAddresses["midi_note_record_3"] = 36;
      _eepromAddresses["midi_note_record_4"] = 37;
      _eepromAddresses["midi_note_record_5"] = 38;
      _eepromAddresses["midi_note_record_6"] = 39;
      _eepromAddresses["midi_note_record_7"] = 40;
      _eepromAddresses["midi_note_record_8"] = 41;
      _eepromAddresses["midi_note_record_9"] = 42;
      _eepromAddresses["midi_note_record_10"] = 43;
      _eepromAddresses["midi_note_record_11"] = 44;
      _eepromAddresses["midi_note_record_12"] = 45;
      _eepromAddresses["midi_note_record_13"] = 46;
      _eepromAddresses["midi_note_record_14"] = 47;
      _eepromAddresses["midi_note_record_15"] = 48;
      _eepromAddresses["midi_note_record_16"] = 49;
      _eepromAddresses["looper_enabled"] = 50;
      _eepromAddresses["looper_autoplay_after_record"] = 51;
      _eepromAddresses["looper_transport_control_link"] = 52;
      _eepromAddresses["midi_note_loop_start_stop"] = 53;
      _eepromAddresses["midi_note_loop_clear"] = 54;
      _eepromAddresses["looper_quantized"] = 55;
      _eepromAddresses["ble_midi_enabled"] = 56;
      _eepromAddresses["midi_cc_knob_9"] = 57;

    this->loadEepromConfig();
    digitalWrite(LED_PIN, HIGH);   // set the LED on
    delay(100);                  // wait for a second
    digitalWrite(LED_PIN, LOW);    // set the LED off
    delay(100);
    digitalWrite(LED_PIN, HIGH);   // set the LED on
    delay(100);                  // wait for a second
    digitalWrite(LED_PIN, LOW);    // set the LED off
    delay(100);
    digitalWrite(LED_PIN, HIGH);   // set the LED on
    delay(100);                  // wait for a second
    digitalWrite(LED_PIN, LOW);    // set the LED off
  }
}

bool Storage::loadSDConfig(){
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
    // else if (cfg.nameIs("ble_midi_enabled")) {
    //   _esp32_enabled = cfg.getIntValue();
    // }
  }
  cfg.end();
  return true;
}

bool Storage::loadEepromConfig(){
  readEeprom(_cur_po_config);
  for(int i = 1 ; i < LEN(_midi_note_str); i++){
  _midi_note[i] = _cur_po_config[_midi_note_str[i]];
  _note_map[i-1][0] = _cur_po_config[_midi_note_str[i]];
  }
  for(int i = 1 ; i < LEN(_midi_note_record_str); i++){
    _midi_record_note[i] = _cur_po_config[_midi_note_record_str[i]];
    _record_note_map[i-1][0] = _cur_po_config[_midi_note_record_str[i]];
  }
  _midi_cc_knob[9] =  _cur_po_config["midi_cc_knob_9"];
  _looper_control_note[0] = _cur_po_config["midi_note_loop_start_stop"];
  _looper_control_note[1] = _cur_po_config["midi_note_loop_clear"];
  _po_midi_channel = _cur_po_config["po_midi_channel"];
  _disable_transport = _cur_po_config["disable_transport"];
  _po_cc_control = _cur_po_config["po_cc_control"];
  _volca_fm_velocity = _cur_po_config["volca_fm_velocity"];
  _volca_fm_midi_ch_1 = _cur_po_config["volca_fm_midi_ch_1"];
  _volca_fm_midi_ch_2 = _cur_po_config["volca_fm_midi_ch_2"];
  _sync_out_enabled = _cur_po_config["sync_out_enabled"];
  _midi_ppqn = _cur_po_config["midi_ppqn"];
  _looper_enabled = _cur_po_config["looper_enabled"];
  _looper_autoplay = _cur_po_config["looper_autoplay_after_record"];
  _looper_transport_control_link =_cur_po_config["looper_transport_control_link"];
  _looper_quantized = _cur_po_config["looper_quantized"];
  // _esp32_enabled = _cur_po_config["ble_midi_enabled"];
  return true;
}

bool Storage::readEeprom(DynamicJsonDocument& po_config){
    for (JsonPair kv : _eepromAddresses.as<JsonObject>()) {
      po_config[kv.key().c_str()] = EEPROM.read(kv.value().as<int>());
    }
    digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    return true;
}

bool Storage::writeEeprom(DynamicJsonDocument& json){
  for (JsonPair kv : json["data"].as<JsonObject>()) {
    if(_isValidMidiValue(kv.value().as<int>())){
      int address = _eepromAddresses[kv.key()];
      EEPROM.write(address, kv.value().as<int>());
    }
  }
  _cmdStats["status"] = "Success";
  _cmdStats["command"] = "SAVEALL";
  serializeJson(_cmdStats, Serial);
  loadEepromConfig();
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  return true;
}

bool Storage::checkforUpdate() {
    DynamicJsonDocument _serial_json(2048);
    DeserializationError error = deserializeJson(_serial_json, Serial);
  if (error) {
        _cmdStats["status"] = "deserializeJson() failed: ";
        _cmdStats["error"] = error.c_str();
        serializeJson(_cmdStats, Serial);
        return false;
  } else {
    String command = _serial_json["command"];
    if(command.equals("READALL")){
      serializeJson(_cur_po_config, Serial);
      return false;
    } else if (command.equals("SAVEALL")) {
      this->writeEeprom(_serial_json);
      return true;
    } else {    
      _cmdStats["status"] = "Unknown command";
      _cmdStats["command"] = _serial_json["command"];
      serializeJson(_cmdStats, Serial);
      return false;
    }
  }
  return false;
}
