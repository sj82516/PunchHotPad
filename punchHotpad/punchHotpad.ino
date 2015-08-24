#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // hotpad control pin
  pinMode(7,OUTPUT);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  // read the value
  int punchValue = analogRead(A0);
  Serial.println(punchValue);
  if(punchValue>600){
    digitalWrite(7,HIGH);
    //from blue to no color
    for(int j=0;j<20;j++){
      for(int i=0;i<NUMPIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(0,0,255-j*12)); // Moderately bright green color.
        pixels.show();
        delay(80);
       }
    }
    //from no color to red
    for(int j=0;j<20;j++){
       for(int i=0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(j*12,0,0)); 
        pixels.show();
        delay(80);
      }
    }
    delay(500); 
    while(punchValue>600){
      delay(500);
      punchValue = analogRead(A0); 
    }
  }else{
    digitalWrite(7,LOW);
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0,0,255));
      pixels.show(); 
     }
  }

}
