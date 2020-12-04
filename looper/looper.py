import mido
import sys, signal
import time
teensy_out = 'Teensy MIDI 1'
teensy_in = 'Teensy MIDI 0'
out_port = mido.open_output(teensy_out)

midi_note_record = 79
midi_note_button_12 = 63

def signal_handler(signal, frame):
    print("\nprogram exiting gracefully")
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def process_MIDI_message(message):
    print(message)
    if message['type'] == 'control_change' and message['control'] == 82:
        if message['value'] == 127:
            print('record')
            msg = mido.Message('note_on', note=midi_note_record)
            msg2 = mido.Message('note_on', note=midi_note_button_12)
            out_port.send(msg)
            out_port.send(msg2)
        else:
            print('stop record')
            msg = mido.Message('note_off', note=midi_note_record)
            msg2 = mido.Message('note_off', note=midi_note_button_12)
            out_port.send(msg)
            out_port.send(msg2)
try:
    with mido.open_input(teensy_in) as port:
        print('Using {}'.format(port))
        while True:
            for message in port.iter_pending():
                process_MIDI_message(message.dict())
except KeyboardInterrupt:
    sys.exit(0)

