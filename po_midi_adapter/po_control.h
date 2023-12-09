#ifndef PO_CONTROL_H
#define PO_CONTROL_H
#include <Arduino.h>
#include "storage.h"
#include <MIDI.h>        // access to serial (5 pin DIN) MIDI

class PO_Control{
    private:
      uint8_t _record_note_map[16][2];
      uint8_t _note_map[23][2];
      uint8_t _midi_cc_knob[17];
      uint8_t _transport_note_map[7][2];
      uint8_t _looper_control[2];
      bool _is_playing = false;
      bool _is_write_mode = false;
      int _po_midi_channel = 1;
      uint8_t _op_mode = 0;
      int _disable_transport = 1; //1 == disable transport, 0 == enabled transport
      int _po_cc_control = 0; //0 == disable , 1 ==enable
      int _volca_fm_velocity = 1; // 1 == enable, 0 == disable
      int _volca_fm_midi_ch_1 = 13;
      int _volca_fm_midi_ch_2 = 16;
      int _is_one_button_record = 1;
      bool _is_recording = false;
      bool _is_looping = false;
      unsigned long _loop_start_time = 0;
      unsigned long _loop_stop_time = 0;
      unsigned long _loop_interval_time = 0;
      elapsedMillis _looper_trigger_millis;
      int _current_loop_track = -1;
      bool _is_loop_triggered = false;
      int _current_record_track = -1;
      int _looper_transport_control_link = 0;
      int _is_looper_quantized = 0;
      unsigned long _current_loop_time = 0;
      unsigned long _previous_loop_time = 0;
      int _sync_out_enabled = 1;
      int _midi_ppqn = 24;
      unsigned long _prev_midi_clock_time = 0;
      volatile unsigned long _curr_midi_clock_time = 0;
      

      Storage *_config;

      void changeSound(uint8_t sound);
      void changeVolume(uint8_t vol);
      void changePattern(uint8_t pattern);

      void triggerPONoteButton(uint8_t note);
      void releasePONoteButton(uint8_t note);
      void triggerPOControlNoteButton(uint8_t note);
      void releasePOControlNoteButton(uint8_t note);

      void triggerPONoteRecord(uint8_t note);
      void releasePONoteRecord(int bpm);

      void checkForLooperControl(uint8_t data1);
    public:
      PO_Control();

      void startOrStopPlayback();
      void execute(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2, int bpm);

      int get_po_midi_channel(){ return _po_midi_channel; }
      int get_disable_transport(){ return _disable_transport; }
      int get_po_cc_control(){ return _po_cc_control; }
      int get_volca_fm_velocity(){ return _volca_fm_velocity; }
      int get_volca_fm_midi_ch_1(){ return _volca_fm_midi_ch_1; }
      int get_volca_fm_midi_ch_2(){ return _volca_fm_midi_ch_2; }
      int get_sync_out_enabled(){ return _sync_out_enabled; }
      int get_midi_ppqn(){ return _midi_ppqn; }
      bool get_is_playing() { return _is_playing; }
      bool get_is_looping() { return _is_looping; }
      bool get_is_recording() { return _is_recording;} 
      bool get_looper_transport_control_link() { return _looper_transport_control_link;}
      void set_is_playing(bool is_playing) { _is_playing = is_playing; }
      void start_stop_looper();
      void start_looper();
      void stop_looper();
      void clear_looper();
      void run_looper();
      void checkForConfigUpdate();
};

#endif
