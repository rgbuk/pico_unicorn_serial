#Client for rgb.uk to drive a Pico Unicorn via Serial over USB

from serial import *
import time
import urllib.request

com_port = "/dev/ttyACM0"
colour_session = ""


def set_pixel(sx, sy, sr, sg, sb):
    print("Writing to Pico")
    ser.write('{:03d} {:03d} {:03d} {:03d} {:03d}'.format(sx, sy, sr, sg, sb).encode())
    print("Pico Responded: {}".format(ser.readline().decode()))


def get_colour(session_id):
    fp = urllib.request.urlopen("https://rgb.uk/session/{}".format(session_id))
    colour_bytes = fp.read()
    colour_tuple = colour_bytes.decode("utf8").strip()
    fp.close()
    colour_data = colour_tuple.split(",")
    return int(colour_data[0]), int(colour_data[1]), int(colour_data[2])


print("Connecting to COM port: {}".format(com_port))

ser = Serial(
    port=com_port,
    baudrate=115200,
    parity=PARITY_NONE,
    stopbits=STOPBITS_ONE,
    bytesize=EIGHTBITS,
    timeout=0)

print("Sleep to ensure COM port is ready")
time.sleep(2)

previous_colour = (0, 0, 0)

print("Entering polling loop to rgb.uk with session: {}".format(colour_session))

while True:
    try:
        r, g, b = get_colour(colour_session)
        if (r, g, b) != previous_colour:
            for y in range(7):
                for x in range(16):
                    set_pixel(x, y, r, g, b)
                    previous_colour = (r, g, b)
            set_pixel(255, 255, 255, 255, 255)
        time.sleep(1)
    except KeyboardInterrupt:
        print("Done")
        ser.close()
        sys.exit()
