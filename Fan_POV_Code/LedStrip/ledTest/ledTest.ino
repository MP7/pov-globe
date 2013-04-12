#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
boolean oneCycle = false;
int count = 0; // Count the number of 
boolean front = false;
boolean back = false;


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  // colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  //lightUP(strip.Color(0, 0, 0), 50);
 // lightUP(strip.Color(0, 0, 0), 50);
  
   //rainbow(20);
   //rainbowCycle(20);
   hallEffect();
}

void hallEffect(){
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  if(!oneCycle){//one cycle
      if(sensorValue >350) front = true;//meet 1st magnet, value read ~ 1023 
      if(sensorValue <100) back = true; //meet 2nd magnet, value read ~ 5 or 6

   }
    oneCycle = front && back;
  if(oneCycle) {  
    lightUP(strip.Color(255, 0, 0), 1);
    lightUP(strip.Color(0, 255, 0), 1);
    lightUP(strip.Color(0, 0, 255), 1);
    lightUP(strip.Color(0, 0, 0), 0);
    count++; 
    oneCycle = false;  
    front = false;
    back = false;
   /* if(count >= 2 || count == 1000){     
    Serial.println(sensorValue); 
    Serial.print("count");
    Serial.println(count);
    time = millis();
    Serial.println(time);}
    }*/
}

}

void lightUP(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  //delay(wait);
  delayMicroseconds(wait);
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

