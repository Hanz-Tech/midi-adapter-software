#include "po_control.h"

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
    printArray(_record_note_map);
}

void PO_Control::releasePONoteButton(uint8_t note){
  for (uint8_t i = 0 ; i < LEN(_note_map) ; i++){
    if(_note_map[i][0] == note){
      digitalWrite(_note_map[i][1], HIGH);
    }
  }
}

void PO_Control::triggerPONoteRecord(uint8_t note){
    for (uint8_t i = 0 ; i < LEN(_record_note_map) ; i++){
        Serial.println(_record_note_map[i][0]);
        if (_record_note_map[i][0] == note){
            digitalWrite(PO_BUTTON_SPECIAL, LOW);
            delay(50);
            digitalWrite(_record_note_map[i][1], LOW);
            delay(50);
            digitalWrite(_record_note_map[i][1], HIGH);
            _is_recording = true;
        }
    }
}

void PO_Control::releasePONoteRecord(){
    digitalWrite(PO_BUTTON_SPECIAL, HIGH);
    _is_recording = false;
}

void PO_Control::triggerPONoteButton(uint8_t note){
  for (uint8_t i = 0 ; i < LEN(_note_map) ; i++){
    Serial.println(_note_map[i][0]);
    if(_note_map[i][0] == note){
      if(_note_map[i][1] == PO_BUTTON_PLAY){
        _is_playing = !_is_playing;
      }
      digitalWrite(_note_map[i][1], LOW);
      Serial.println(_note_map[i][1]);
    }
  }
}

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

void PO_Control::changeVolume(uint8_t vol){
  digitalWrite(PO_BUTTON_BPM, LOW);
  delay(KNOB_DELAY);
  digitalWrite(_note_map[vol][1], LOW);
  delay(KNOB_DELAY);
  digitalWrite(_note_map[vol][1], HIGH);
  delay(KNOB_DELAY);
  digitalWrite(PO_BUTTON_BPM, HIGH);
}

void PO_Control::changeSound(uint8_t sound){
  digitalWrite(PO_BUTTON_SOUND, LOW);
  delay(KNOB_DELAY);
  digitalWrite(_note_map[sound][1], LOW);
  delay(KNOB_DELAY);
  digitalWrite(_note_map[sound][1], HIGH);
  delay(KNOB_DELAY);
  digitalWrite(PO_BUTTON_SOUND, HIGH);
}

void PO_Control::changePattern(uint8_t pattern){
  digitalWrite(PO_BUTTON_PATTERN, LOW);
  delay(KNOB_DELAY);
  digitalWrite(_note_map[pattern][1], LOW);
  delay(KNOB_DELAY);
  digitalWrite(_note_map[pattern][1], HIGH);
  delay(KNOB_DELAY);
  digitalWrite(PO_BUTTON_PATTERN, HIGH);
}

void PO_Control::startOrStopPlayback(){
  for (uint8_t i = 0 ; i < LEN(_transport_note_map) ; i++){
    if(_transport_note_map[i][1] == PO_BUTTON_PLAY){
      digitalWrite(_transport_note_map[i][1], LOW);
      delay(20);
      digitalWrite(_transport_note_map[i][1], HIGH);
    }
  }
}

void PO_Control::execute(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2){
  if(channel == this->get_po_midi_channel()){
    if (type == midi::ControlChange && this->get_po_cc_control()){
      if(data1 == _midi_cc_knob[9]){ //mode
      _op_mode = data2;
        switch(data2){
          case PERF_MODE: /*fall through*/
          case NORMAL_MODE:
            digitalWrite(PO_BUTTON_SPECIAL,HIGH);
            digitalWrite(PO_BUTTON_FX,HIGH);
            if(_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(20);
              digitalWrite(PO_BUTTON_WRITE,HIGH);
              _is_write_mode = false;
            }
            break;
          case FX_MODE:
            digitalWrite(PO_BUTTON_FX,LOW);
            digitalWrite(PO_BUTTON_SPECIAL,HIGH);
            if(_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(20);
              digitalWrite(PO_BUTTON_WRITE,HIGH);
              _is_write_mode = false;
            }
            break;
          case RECORD_MODE:
            digitalWrite(PO_BUTTON_FX,HIGH);
            digitalWrite(PO_BUTTON_SPECIAL,LOW);
            if(_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(20);
              digitalWrite(PO_BUTTON_WRITE,HIGH);
              _is_write_mode = false;
            }
            break;
          case WRITE_MODE:
            digitalWrite(PO_BUTTON_FX,HIGH);
            digitalWrite(PO_BUTTON_SPECIAL,HIGH);
            if(!_is_write_mode){
              digitalWrite(PO_BUTTON_WRITE,LOW);
              delay(20);
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
    } else if (type ==  midi::NoteOn){
      if(_op_mode > PERF_MODE){
        if (!_is_recording)
          this->triggerPOControlNoteButton(data1);
      } else{
        Serial.println("execute");
        if (!_is_recording){
          this->triggerPONoteRecord(data1);
          if(!_is_recording){
            this->triggerPONoteButton(data1);
            Serial.println("play");
          }
        } else {
          this->releasePONoteRecord();
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
    }
  }
}