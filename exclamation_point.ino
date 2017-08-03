// ATTINY85
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int LED_PIN = 3; // use blue numbers on this page for reference: https://web.archive.org/web/20170803023943/https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/attiny85-use-hints
const int NUMBER_OF_LEDS = 8;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800); // AT TINY 85

const int BUTTON_PIN = 4; // use blue numbers on this page for reference: https://web.archive.org/web/20170803023943/https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/attiny85-use-hints
int button_state = 0;

int speed_delay = 40; // ms to delay color change

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(BUTTON_PIN, INPUT);

}

void loop() {
  uint16_t i, j;
  byte *c;

  
  for(j=0; j<256; j++) {
    button_state = digitalRead(BUTTON_PIN); // HIGH or LOW

    for(i=0; i< NUMBER_OF_LEDS; i++) {
      if (i == 5) { continue; } // keep this pixel dark since it's under tape
      
      if (button_state == HIGH) {
         // STROBE!!!!!

        if (random(0,100) <= 5) {
          strip.setPixelColor(i, 255, 255, 255);
        } else {
          strip.setPixelColor(i, 0,0,0);
        }

        speed_delay = 20;
        
      } else {
        c = Wheel(((i * 256 / NUMBER_OF_LEDS-1) + j) & 255);
      
        speed_delay = 40;
        strip.setPixelColor(i, *c, *(c+1), *(c+2));

      }
      

    }
    strip.show();
    delay(speed_delay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
     c[0]=WheelPos * 3;
     c[1]=255 - WheelPos * 3;
     c[2]=0;
  } else if(WheelPos < 170) {
     WheelPos -= 85;
     c[0]=255 - WheelPos * 3;
     c[1]=0;
     c[2]=WheelPos * 3;
  } else {
     WheelPos -= 170;
     c[0]=0;
     c[1]=WheelPos * 3;
     c[2]=255 - WheelPos * 3;
  }

  return c;
}
