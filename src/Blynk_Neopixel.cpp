#define BLYNK_TEMPLATE_ID "TMPL6jluSAid8"
#define BLYNK_TEMPLATE_NAME "RGB Control"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial

#define APP_DEBUG

#include "BlynkEdgent.h"
#include <Adafruit_NeoPixel.h>

#define PIN D5 // Pin D5 untuk NeoPixel
#define NUM_PIXELS 1 // Jumlah NeoPixel

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

int redValue = 0, greenValue = 0, blueValue = 0;

void setColor() {
  strip.setPixelColor(0, strip.Color(redValue, greenValue, blueValue));
  strip.show();
}

BLYNK_WRITE(V0) { 
  redValue = param.asInt();
  setColor();
}

BLYNK_WRITE(V1) { 
  greenValue = param.asInt();
  setColor();
}

BLYNK_WRITE(V2) { 
  blueValue = param.asInt();
  setColor();
}



void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
