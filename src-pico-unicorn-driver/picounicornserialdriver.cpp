#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include <cstring>
#include "pico_unicorn.hpp"

using namespace pimoroni;

PicoUnicorn pico_unicorn;

int main() {
  stdio_init_all();
  pico_unicorn.init();
  char inputBuffer[20];
  char displayBuffer[112][20];
  int displayBufferPosition = 0;
  int x, y, r, g, b;

  while(true) {
    fgets(inputBuffer, 20, stdin);
    sscanf(inputBuffer, "%d %d %d %d %d", &x, &y, &r, &g, &b);
    printf("Parsed: x:%d y:%d r:%d g:%d b:%d\n", x, y, r, g, b);

    if(x != 255){
      strncpy(displayBuffer[displayBufferPosition], inputBuffer, 20);
      displayBufferPosition++;
    }

    if((displayBufferPosition == 112) || (x == 255)){
      for(int i = 0; i < displayBufferPosition; i++){
        strncpy(inputBuffer, displayBuffer[i], 20);
        sscanf(inputBuffer, "%d %d %d %d %d", &x, &y, &r, &g, &b);
        pico_unicorn.set_pixel(x, y, r, g, b);
      }
      displayBufferPosition = 0;
    }
  }
  return 0;
}
