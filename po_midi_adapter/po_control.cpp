/*!
 *  @file       po_control.cpp
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



#include "po_control.h"

#define BUTTON_PRESS_DELAY_MS 20
#define KNOB_DELAY_MS 20

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

PO_Control::PO_Control(){
  _config = new SD_Load();
  _po_midi_channel = _config->get_po_midi_channel();
  _disable_transport = _config->get_disable_transport(); //1 == disable transport, 0 == enabled transport
  _po_cc_control = _config->get_po_cc_control(); //0 == disable , 1 ==enable
  _volca_fm_velocity = _config->get_volca_fm_velocity(); // 1 == enable, 0 == disable
  _volca_fm_midi_ch_1 = _config->get_volca_fm_midi_ch_1();
  _volca_fm_midi_ch_2 = _config->get_volca_fm_midi_ch_2();
  _sync_out_enabled = _config->get_sync_out_enabled();
  _midi_ppqn = _config->get_midi_ppqn();
  _config->get_note_map(_note_map);
  _config->get_transport_note_map(_transport_note_map);
  _config->get_midi_cc_knob(_midi_cc_knob);
  _config->get_record_note_map(_record_note_map);
  _config->get_looper_control(_looper_control);
  _looper_transport_control_link = _config->get_looper_transport_control_link();
  _is_looper_quantized = _config->get_is_looper_quantized();
  _esp32_enabled = _config->get_is_esp32_enabled();
}


//-------------- Power ESP32(BLE MIDI) -------------
void PO_Control::powerOnEsp32(){
  if (_esp32_enabled == 1) {
    digitalWrite(ESP32_ENABLE, HIGH);
  } else {
    digitalWrite(ESP32_ENABLE, LOW);
  }
}

// -------------- Trigger Notes -------------
void PO_Control::releasePONoteButton(uint8_t note){
  for (uint8_t i = 0 ; i < LEN(_note_map) ; i++){
    if(_note_map[i][0] == note){
      digitalWrite(_note_map[i][1], HIGH);
    }
  }
}

void PO_Control::triggerPONoteButton(uint8_t note){
  for (uint8_t i = 0 ; i < LEN(_note_map) ; i++){
    if(_note_map[i][0] == note){
      if(_note_map[i][1] == PO_BUTTON_PLAY){
        _is_playing = !_is_playing;
      }
      digitalWrite(_note_map[i][1], LOW);
    }
  }
}

// --------------- Trigger Record ---------------
void PO_Control::triggerPONoteRecord(uint8_t note){
  for (uint8_t i = 0 ; i < LEN(_record_note_map) ; i++){
    if (_record_note_map[i][0] == note){
      digitalWriteFast(PO_BUTTON_SPECIAL, LOW);
      delay(15);
      digitalWriteFast(_record_note_map[i][1], LOW);
      _loop_start_time = millis();
      _is_looping = false;
      _is_recording = true;
      _current_record_track = i;
      if (i < 8){
        _current_loop_track = i;
      }
    }
  }
}

void PO_Control::releasePONoteRecord(int bpm){
  if(_is_looper_quantized){
    float ms_per_beat = 60000 / float(bpm);
    int number_of_beats = ( millis() - _loop_start_time ) / ms_per_beat;
    _loop_interval_time = number_of_beats * ms_per_beat;
  } else {
    _loop_interval_time = millis() - _loop_start_time;
  }
  digitalWriteFast(_record_note_map[_current_record_track][1], HIGH);
  digitalWriteFast(PO_BUTTON_SPECIAL, HIGH);
  if(_current_loop_track >= 0 && _current_loop_track < 8 && _config->get_is_looper_enabled()){ //don't use looper on drum track
    if(_config->get_is_looper_autoplay()){
      delay(150);
      this->run_looper();
      _is_looping = true;
    }
  }
  _is_recording = false;
  _loop_start_time = 0;
}


// --------------- Looper Control ---------------
void PO_Control::clear_looper(){
  if(_current_loop_track > -1){
    _is_looping = false;
    _previous_loop_time = 0;
    _current_loop_track = -1;
    _current_record_track = -1;
    _loop_interval_time = 0;
    _loop_start_time = 0;
    digitalWriteFast(PO_BUTTON_SOUND, LOW);
    delay(100);
    digitalWriteFast(_record_note_map[_current_loop_track][1], LOW);
    delay(100);
    digitalWriteFast(_record_note_map[_current_loop_track][1], HIGH);
    delay(100);
    digitalWriteFast(PO_BUTTON_SOUND, HIGH);
    delay(100);
    digitalWriteFast(PO_BUTTON_SPECIAL, LOW);
    delay(100);
    digitalWriteFast(PO_BUTTON_SOUND, LOW);
    delay(100);
    digitalWriteFast(PO_BUTTON_SOUND, HIGH);
    delay(100);
    digitalWriteFast(PO_BUTTON_SPECIAL, HIGH);
  }
}

void PO_Control::start_stop_looper(){
  if(_current_loop_track >= 0 && _current_loop_track < 8 && _config->get_is_looper_enabled()){
    if(_is_looping){
      _is_looping = false;
      _previous_loop_time = 0;
    } else {
      _is_looping = true;
    }
  }
}

void PO_Control::start_looper(){
  if(_current_loop_track >= 0 && _current_loop_track < 8 && _config->get_is_looper_enabled()){
    _is_looping = true;
  }
}

void PO_Control::stop_looper(){
  if(_current_loop_track >= 0 && _current_loop_track < 8 && _config->get_is_looper_enabled()){
      _is_looping = false;
      _previous_loop_time = 0;
  }
}

void PO_Control::checkForLooperControl(uint8_t data1){
  if (data1 == _looper_control[0]){
    start_stop_looper();
  } else if (data1 == _looper_control[1]){
    clear_looper();
  }
}

void PO_Control::run_looper(){
  // Serial.println(millis() - _previous_loop_time);
  _current_loop_time = millis();
  if(_current_loop_time - _previous_loop_time >= _loop_interval_time){
    _previous_loop_time = _current_loop_time;
    _is_loop_triggered = false;
    _looper_trigger_millis = 0;
    digitalWriteFast(_note_map[4][1], LOW);
  } else if (_looper_trigger_millis >= 50 && !_is_loop_triggered){
    digitalWriteFast(_note_map[4][1], HIGH);
    digitalWriteFast(13, HIGH);
    delay(2);
    digitalWriteFast(13, LOW);
    _is_loop_triggered = true;
  }
}


// --------------- Midi CC for PO Control
void PO_Control::triggerPOControlNoteButton(uint8_t note){
  if(_op_mode == NORMAL_MODE){
    //Serial.println("normal mode");
    for (uint8_t i = 0 ; i < LEN(_transport_note_map) ; i++){
      if(_transport_note_map[i][0] == note){
        if(_transport_note_map[i][1] == PO_BUTTON_PLAY){
          _is_playing = !_is_playing;
        }
        digitalWrite(_transport_note_map[i][1], LOW);
      }
    }
  }
  else{
    for (uint8_t i = 0 ; i < LEN(_note_map) ; i++){
      if(_note_map[i][0] == note){
        digitalWrite(_note_map[i][1], LOW);
      }
    }
  }
}

void PO_Control::releasePOControlNoteButton(uint8_t note){
  if(_op_mode == NORMAL_MODE){
    for (uint8_t i = 0 ; i < LEN(_transport_note_map) ; i++){
      if(_transport_note_map[i][0] == note){
        digitalWrite(_transport_note_map[i][1], HIGH);
      }
    }
  } else{
    for (uint8_t i = 0 ; i < LEN(_note_map) ; i++){
      if(_note_map[i][0] == note){
        digitalWrite(_note_map[i][1], HIGH);
      }
    }
  }
}

// ----------------Sub functions ------------
void PO_Control::changeVolume(uint8_t vol){
  digitalWrite(PO_BUTTON_BPM, LOW);
  delay(KNOB_DELAY_MS);
  digitalWrite(_note_map[vol][1], LOW);
  delay(KNOB_DELAY_MS);
  digitalWrite(_note_map[vol][1], HIGH);
  delay(KNOB_DELAY_MS);
  digitalWrite(PO_BUTTON_BPM, HIGH);
}

void PO_Control::changeSound(uint8_t sound){
  digitalWrite(PO_BUTTON_SOUND, LOW);
  delay(KNOB_DELAY_MS);
  digitalWrite(_note_map[sound][1], LOW);
  delay(KNOB_DELAY_MS);
  digitalWrite(_note_map[sound][1], HIGH);
  delay(KNOB_DELAY_MS);
  digitalWrite(PO_BUTTON_SOUND, HIGH);
}

void PO_Control::changePattern(uint8_t pattern){
  digitalWrite(PO_BUTTON_PATTERN, LOW);
  delay(KNOB_DELAY_MS);
  digitalWrite(_note_map[pattern][1], LOW);
  delay(KNOB_DELAY_MS);
  digitalWrite(_note_map[pattern][1], HIGH);
  delay(KNOB_DELAY_MS);
  digitalWrite(PO_BUTTON_PATTERN, HIGH);
}

void PO_Control::startOrStopPlayback(){
  for (uint8_t i = 0 ; i < LEN(_transport_note_map) ; i++){
    if(_transport_note_map[i][1] == PO_BUTTON_PLAY){
      digitalWriteFast(_transport_note_map[i][1], LOW);
      delay(BUTTON_PRESS_DELAY_MS);
      digitalWriteFast(_transport_note_map[i][1], HIGH);
    }
  }
}

void PO_Control::execute(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2, int bpm){
  if(channel == this->get_po_midi_channel()){
    if (type ==  midi::NoteOn){
      if(_op_mode > PERF_MODE){
        if (!_is_recording)
          this->triggerPOControlNoteButton(data1);
      } else{
        if (!_is_recording){
          this->checkForLooperControl(data1);
          this->triggerPONoteRecord(data1);
          if(!_is_recording){
            this->triggerPONoteButton(data1);
          }
        } else {
          this->releasePONoteRecord(bpm);
        }
      }
    } else if(type == midi::NoteOff){
      if(_op_mode > PERF_MODE){
        if (!_is_recording)
          this->releasePOControlNoteButton(data1);
      } else{
        if (!_is_recording)
          this->releasePONoteButton(data1);
      }
    } else if (type == midi::ControlChange && this->get_po_cc_control()){
      if(data1 == _midi_cc_knob[9]){ //mode
      _op_mode = data2;
        switch(data2){
          case PERF_MODE: /*fall through*/
          case NORMAL_MODE:
            digitalWrite(PO_BUTTON_SPECIAL,HIGH);
            digitalWrite(PO_BUTTON_FX,HIGH);
            if(_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(BUTTON_PRESS_DELAY_MS);
              digitalWrite(PO_BUTTON_WRITE,HIGH);
              _is_write_mode = false;
            }
            break;
          case FX_MODE:
            digitalWrite(PO_BUTTON_FX,LOW);
            digitalWrite(PO_BUTTON_SPECIAL,HIGH);
            if(_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(BUTTON_PRESS_DELAY_MS);
              digitalWrite(PO_BUTTON_WRITE,HIGH);
              _is_write_mode = false;
            }
            break;
          case RECORD_MODE:
            digitalWrite(PO_BUTTON_FX,HIGH);
            digitalWrite(PO_BUTTON_SPECIAL,LOW);
            if(_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(BUTTON_PRESS_DELAY_MS);
              digitalWrite(PO_BUTTON_WRITE,HIGH);
              _is_write_mode = false;
            }
            break;
          case WRITE_MODE:
            digitalWrite(PO_BUTTON_FX,HIGH);
            digitalWrite(PO_BUTTON_SPECIAL,HIGH);
            if(!_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(BUTTON_PRESS_DELAY_MS);
              digitalWrite(PO_BUTTON_WRITE,HIGH);
              _is_write_mode = true;
            }
            break;
        }
      } else if(data1 == _midi_cc_knob[10]){ //sounds
        this->changeSound(data2);
      } else if(data1 == _midi_cc_knob[11]){
        this->changePattern(data2);
      } else if(data1 == _midi_cc_knob[12]){
        this->changeVolume(data2);
      }
    }
  }
}
