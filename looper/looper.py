import mido
import sys, signal
import time
teensy_out = 'Teensy MIDI 2'
teensy_in = 'Teensy MIDI 1'
beatstep_in = 'Arturia BeatStep Pro 2'
beatstep_out = 'Arturia BeatStep Pro 3'
print(mido.get_input_names())
print(mido.get_output_names())
out_port = mido.open_output(teensy_out)
# beatstep_out_port = mido.open_output(beatstep_out)
midi_note_po_record = 79
midi_note_po_play = 81
midi_note_po_button_1 = 68
midi_note_po_button_2 = 69
midi_note_po_button_12 = 63
midi_note_po_sound = 76

midi_cc_record_1 = 25
midi_cc_record_2 = 28
midi_cc_change_sound= 24
midi_cc_play = 26
midi_cc_start = 27

current_sound = 1

def record(po_button,message):
    if message['value'] != 0:
        print('record')
        msg = mido.Message('note_on', note=midi_note_po_record)
        msg2 = mido.Message('note_on', note=po_button)
        out_port.send(msg)
        time.sleep(0.05)
        out_port.send(msg2)
    else:
        print('stop record')
        msg = mido.Message('note_off', note=midi_note_po_record)
        msg2 = mido.Message('note_off', note=po_button)
        out_port.send(msg)
        out_port.send(msg2)

def change_sound():
    global current_sound
    
    msg_on_1 = mido.Message('note_on', note=midi_note_po_sound)
    msg_off_1 = mido.Message('note_off', note=midi_note_po_sound)
    if(current_sound == 1):
        print('change to 2')
        msg_on_2 = mido.Message('note_on', note=midi_note_po_button_2)
        msg_off_2 = mido.Message('note_off', note=midi_note_po_button_2)
        current_sound = 2
    elif(current_sound == 2):
        print('change to 1')
        msg_on_2 = mido.Message('note_on', note=midi_note_po_button_1)
        msg_off_2 = mido.Message('note_off', note=midi_note_po_button_1)
        current_sound = 1    
    print(current_sound)
    out_port.send(msg_on_1)
    time.sleep(0.05)
    out_port.send(msg_on_2)
    out_port.send(msg_off_1)
    time.sleep(0.05)
    out_port.send(msg_off_2)



def process_MIDI_message(message):
    if message['type'] != 'clock':
        print(message)
    if message['type'] == 'control_change':
        if  message['control'] == midi_cc_start:
            if message['value'] != 0:
                print('start')
                msg = mido.Message('start')
                out_port.send(msg)
        elif message['control'] == midi_cc_record_1:
            record(midi_note_po_button_1,message)
        elif message['control'] == midi_cc_record_2:
            record(midi_note_po_button_2,message)
        elif message['control'] == midi_cc_play:
                msg_on = mido.Message('note_on', note=midi_note_po_play)
                msg_off = mido.Message('note_off', note=midi_note_po_play)
                out_port.send(msg_on)
                time.sleep(0.05)
                out_port.send(msg_off)
        elif message['control'] == midi_cc_change_sound:
            change_sound()
        else:
            print('reset')
            msg = mido.Message('stop')
            out_port.send(msg)

try:
    with mido.open_input(teensy_in) as port:
        print('Using {}'.format(port))
        while True:
            for message in port.iter_pending():
                process_MIDI_message(message.dict())
except KeyboardInterrupt:
    sys.exit(0)


