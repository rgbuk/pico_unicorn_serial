#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include <cstring>
#include "pico_unicorn.hpp"

using namespace pimoroni;

PicoUnicorn pico_unicorn;

bool StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}


char *inputString(FILE* fp, size_t size){
    char *str;
    int ch;
    size_t len = 0;
    str = (char*)realloc(NULL, sizeof(*str)*size);
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = (char*)realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';
    return (char*)realloc(str, sizeof(*str)*len);
}


int main() {
  stdio_init_all();
  pico_unicorn.init();
  char *inputBuffer;
  char displayBuffer[112][25];
  int displayBufferPosition = 0;
  int x, y, r, g, b;

  while(true) {
    inputBuffer = inputString(stdin, 25);
    if(StartsWith(inputBuffer, "MSG ")){
      sscanf(inputBuffer, "MSG %d %d %d %d %d", &x, &y, &r, &g, &b);
      printf("Parsed: x:%d y:%d r:%d g:%d b:%d\n", x, y, r, g, b);

      if(x != 255){
        strncpy(displayBuffer[displayBufferPosition], inputBuffer, 25);
        displayBufferPosition++;
      }

      if((displayBufferPosition == 111) || (x == 255)){
        for(int i = 0; i <= displayBufferPosition; i++){
          strncpy(inputBuffer, displayBuffer[i], 25);
          sscanf(inputBuffer, "MSG %d %d %d %d %d", &x, &y, &r, &g, &b);
          pico_unicorn.set_pixel(x, y, r, g, b);
        }
        displayBufferPosition = 0;
      }
    }
    free(inputBuffer);
  }
  return 0;
}
