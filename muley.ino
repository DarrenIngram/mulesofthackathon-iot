#include <neopixel.h>
#include <stdio.h>
#include <string.h>

SYSTEM_MODE(AUTOMATIC);

#define PIXEL_PIN D1
#define PIXEL_COUNT 12
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
Servo muleyServo;

void setup()
{
    bool setMoodSuccess = Particle.function("setMood", setMood);
    bool danceSuccess = Particle.function("dance", dance);
    bool setPositionSuccess = Particle.function("setPosition", setPosition);
    
    muleyServo.attach(D0);
    muleyServo.write(45);
    strip.begin();
    colorWipe(strip.Color(255,140,0), 50);
    delay(100);
    clearLights();
    
    delay(100);
}

void loop()
{

}

// Fill the dots one after the other with a color, wait (ms) after each one
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void discoLights(uint32_t color){
    for (uint16_t i=0; i<3; i++){
        colorWipe(color, 10);
        delay(10);
        clearLights();
    }
    
}


void clearLights() {
    colorWipe(strip.Color(0, 0, 0), 50); // off
}


int setMood(String mood){
    clearLights();
    
    uint32_t color = strip.Color(0, 0, 0); // Off
    
    if(mood == "positive") {
        color = strip.Color(0, 255, 0); // Green
    } else if (mood == "negative") {
        color = strip.Color(255,0,0); // Red
    } else if (mood == "neutral") {
        color = strip.Color(0,0,255); // Blue
    }
    
    discoLights(color);
    colorWipe(color, 50);
}

int dance(String extra){

  for(uint16_t i=0; i<40; i++) {
    setServo(generateRandomNumber(160));
    delay(generateRandomNumber(200));
  }

    setServo(45); // Make Muley face the front.
    return 1;
}

int generateRandomNumber(int maxRand)
{
    return rand() % maxRand;
}

int setPosition(String position){
    int pos = position.toInt();
    
    setServo(pos);
    return 1;
}


int setServo(int pos){
    // Make sure the position is set to a valid range.
    // This would usually be 0-180 (the valid servo range in degrees), but my servo is wonky and gets really upset going past 160!
    if (pos < 0) {
        pos = 0;
    } else if (pos > 160) {
        pos = 160;
    }
    
    muleyServo.write(pos);
}
