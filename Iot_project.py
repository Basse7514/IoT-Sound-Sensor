import sounddevice as sd
import numpy as np
import serial
import time
import random

SERIAL_PORT = "COM7"
BAUD_RATE   = 115200

SAMPLE_RATE = 44100
BLOCK_SIZE  = 1024
THRESHOLD   = 0.08       
SILENCE_THRESHOLD = 0.02 
COOLDOWN    = 0.15

last_beat_time = 0
last_sound_time = time.time()
led_on = False

print("Opening serial...")
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
time.sleep(3)

def send_color(r, g, b):
    line = f"{r},{g},{b}\n"
    try:
        ser.write(line.encode('utf-8'))
    except Exception as e:
        print("Serial error:", e)

def audio_callback(indata, frames, time_info, status):
    global last_beat_time, last_sound_time, led_on

    volume = np.linalg.norm(indata) / np.sqrt(len(indata))
    now = time.time()

    # -----------------------------
    # 1) Beat Detection → LED ON
    # -----------------------------
    if volume > THRESHOLD and (now - last_beat_time) > COOLDOWN:
        last_beat_time = now
        last_sound_time = now
        led_on = True

        r = random.randint(80, 255)
        g = random.randint(80, 255)
        b = random.randint(80, 255)

        dominant = random.choice(['r', 'g', 'b'])
        if dominant == 'r':   r = 255
        elif dominant == 'g': g = 255
        else:                 b = 255

        print(f"Beat! Volume={volume:.3f} -> RGB={r},{g},{b}")
        send_color(r, g, b)

    # -----------------------------
    # 2) Silence Detection → LED OFF
    # -----------------------------
    if volume < SILENCE_THRESHOLD:
    
        if led_on and (now - last_sound_time) > 0.2:
            print("Silence → LED OFF")
            send_color(0, 0, 0)
            led_on = False

def main():
    print("Listening from laptop mic... Ctrl+C to stop.")
    with sd.InputStream(
        channels=1,
        callback=audio_callback,
        samplerate=SAMPLE_RATE,
        blocksize=BLOCK_SIZE):
        while True:
            time.sleep(0.1)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        send_color(0,0,0) 
        ser.close()
