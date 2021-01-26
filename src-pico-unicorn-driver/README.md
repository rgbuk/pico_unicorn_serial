# Set pixels over serial

```
def set_pixel(sx, sy, sr, sg, sb):
    print("Writing to Pico")
    ser.write('{:03d} {:03d} {:03d} {:03d} {:03d}'.format(sx, sy, sr, sg, sb).encode())
    print("Pico Responded: {}".format(ser.readline().decode()))
```

# Update display
To update the display from the buffer send an x coordinate of 255

For example:
```
set_pixel(255, 255, 255, 255, 255)
```

Otherwise display will update when buffer is full