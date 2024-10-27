#define BLYNK_TEMPLATE_ID "TMPL6jluSAid8"
#define BLYNK_TEMPLATE_NAME "RGB Control"
#define BLYNK_FIRMWARE_VERSION "0.1.3"
#define BLYNK_PRINT Serial

#define APP_DEBUG

#include "BlynkEdgent.h"
#include <Blynk/BlynkDebug.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define PIN D5 // Pin D5 untuk NeoPixel
#define NUM_PIXELS 1 // Jumlah NeoPixel
#define DHTPIN D2 // Pin D2 untuk DHT11
#define DHTTYPE DHT11 // Tipe sensor DHT

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
DHT dht(DHTPIN, DHTTYPE);

int redValue = 0, greenValue = 0, blueValue = 0;
BlynkTimer timer;

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

void sendSensorData() {
  float temperature = dht.readTemperature(); // Membaca suhu
  float humidity = dht.readHumidity(); // Membaca kelembapan

  if (!isnan(temperature) && !isnan(humidity)) {
    Blynk.virtualWrite(V3, temperature); // Mengirim suhu ke V3
    Serial.println(temperature);
    Blynk.virtualWrite(V4, humidity); // Mengirim kelembapan ke V4
    Serial.println(humidity);
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
}

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Inisialisasi NeoPixel
  dht.begin(); // Inisialisasi DHT11
  
  BlynkEdgent.begin();
  timer.setInterval(2000L, sendSensorData); // Mengirim data setiap 2 detik
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}
