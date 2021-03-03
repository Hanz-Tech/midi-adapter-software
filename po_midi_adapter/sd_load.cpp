#include "sd_load.h"
const char CONFIG_FILE[] = "config.cfg";
const int chipSelect = BUILTIN_SDCARD;
#define LEN(arr) ((uint8_t) (sizeof (arr) / sizeof (arr)[0]))

bool loadSDConfig();

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

SD_load::SD_load(){
  if (SD.begin(chipSelect)){
    //Serial.println("card init");
    if(loadSDConfig()){
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

bool SD_load::loadSDConfig(){
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
    for(int i = 0 ; i < LEN(_midi_cc_knob_str); i++){
      if(cfg.nameIs(_midi_cc_knob_str[i])){
        _midi_cc_knob[i] = cfg.getIntValue();
        //Serial.println("cc found");
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
  }
  cfg.end();
  return true;
}
