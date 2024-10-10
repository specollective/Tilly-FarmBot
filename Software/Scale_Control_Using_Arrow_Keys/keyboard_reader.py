import serial
import time
import keyboard

# Set up the serial connection (make sure the port matches your Arduino's port)
ser = serial.Serial('COM6', 9600)
time.sleep(2)  # Wait for the connection to establish
# ser.write(Serial Connection Established)

def send_command(command):
    ser.write(command.encode())

try:
    while True:
        if keyboard.is_pressed('up'):
            send_command('w')
        elif keyboard.is_pressed('down'):
            send_command('s')
        elif keyboard.is_pressed('left'):
            send_command('a')
        elif keyboard.is_pressed('right'):
            send_command('d')
        elif keyboard.is_pressed('esc'):
            send_command('x')  # Stop all motors
            break
        time.sleep(0.1)

finally:
    ser.close()
