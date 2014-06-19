byte theByte;
byte datas;
#include "LPD8806.h"
#include "SPI.h"
byte me = 1;
int nLEDs = 16;

int DpLeft = 13;
int CpLeft = 12;

int DpRight  = 11;
int CpRight = 10;

int DpBack  = 2;
int CpBack = 1;

int DpRightCollect = 4;
int CpRightCollect = 3;

int DpLeftCollect = 9;
int CpLeftCollect = 8;

LPD8806 strip = LPD8806(nLEDs, DpLeft, CpLeft);
LPD8806 LeftStrips = LPD8806(nLEDs, DpLeft, CpLeft);
LPD8806 RightStrips = LPD8806(nLEDs, DpRight, CpRight);
LPD8806 BackStrips = LPD8806(nLEDs, DpBack, CpBack);
LPD8806 RightCollectStrips = LPD8806(nLEDs, DpRightCollect, CpRightCollect);
LPD8806 LeftCollectStrips = LPD8806(nLEDs, DpLeftCollect, CpLeftCollect);

int i;

void setup(){
  Serial.begin(9600);
  LeftStrips.begin();
  RightStrips.begin();
  BackStrips.begin();
  RightCollectStrips.begin();
  LeftCollectStrips.begin();
  LeftStrips.show();
  RightStrips.show();
  BackStrips.show();
  LeftCollectStrips.show();
  RightCollectStrips.show();

}

//kill();
//countdown();

void loop(){

  datas = digitalRead(5);         // Set 'data' to the reading at pin 4

  bitWrite(theByte, 0, datas);    // Write a 0 or 1 to the first bit of 'data;

  datas = digitalRead(6);     // Set 'data' to the reading at pin 5
  bitWrite(theByte, 1, datas);    // Write a 0 or 1 to the second bit of 'data'

  datas = digitalRead(7);          // Set 'data' to the reading at pin 6
  bitWrite(theByte, 2, datas);    // Write a 0 or 1 to the third bit of 'data
  Serial.println(theByte);
  int taco = 7;

  switch(taco){
  case 0:
    //  wave(strip.Color(0,127,0), 2, 40); // green icy
    //  wave(strip.Color(0,127,0), 4, 50);  
    wave(strip.Color(0,127,0), 2, 60); 

    break;
  case 1:
    doubleWipe(strip.Color(0,127,0),strip.Color(127,127,127),50); //green n' white cross

    break;
  case 2:
    fixedFlash();

    break;
  case 3:
    scanner(0,127,0, 8); 

    break;
  case 4:
    scanner(0,127,0, 15); 

    break;
  case 5:
    colorWipe(strip.Color(127,127,127),50);

    break; 
  case 6:
    colorWipe(strip.Color(0, 127,0), 0);

    break;
  case 7:
    kill();

    break;
  }
}
void kill(){
  int i;
  for(i=0; i<strip.numPixels(); i++){
    LeftStrips.setPixelColor(i,strip.Color(0,0,0));
    RightStrips.setPixelColor(i,strip.Color(0,0,0));
    BackStrips.setPixelColor(i,strip.Color(0,0,0));
    LeftCollectStrips.setPixelColor(i,strip.Color(0,0,0));
    RightCollectStrips.setPixelColor(i,strip.Color(0,0,0));
  }
  LeftStrips.show();
  RightStrips.show();
  BackStrips.show();
  LeftCollectStrips.show();
  RightCollectStrips.show();
}

void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  for(i=0; i<strip.numPixels(); i++){
    LeftStrips.setPixelColor(15 - i,c);
    RightStrips.setPixelColor(i,c);
    BackStrips.setPixelColor(i,c);
    LeftCollectStrips.setPixelColor(i,c);
    RightCollectStrips.setPixelColor(15 - i,c);

    LeftStrips.show();
    RightStrips.show();
    BackStrips.show();
    LeftCollectStrips.show();
    RightCollectStrips.show();
    
    delay(wait);
  }

}


void doubleWipe(uint32_t c, int cc, uint8_t wait){
  int i;
  int j = 15;
  for (i=0; i < strip.numPixels(); i++) {
    LeftStrips.setPixelColor(i, cc);
    LeftStrips.setPixelColor(j-i,c);
    LeftStrips.show();
    
    RightStrips.setPixelColor(i, c);
    RightStrips.setPixelColor(j-i,cc);
    RightStrips.show();
    
    BackStrips.setPixelColor(i, c);
    BackStrips.setPixelColor(j-i,cc);
    BackStrips.show();
    
    LeftCollectStrips.setPixelColor(i, c);
    LeftCollectStrips.setPixelColor(j-i,cc);
    LeftCollectStrips.show();
    
    RightCollectStrips.setPixelColor(i, cc);
    RightCollectStrips.setPixelColor(j-i,c);
    RightCollectStrips.show();
    delay(wait);
  }
}

void fixedFlash(){
  int i;
  for(i=0; i<strip.numPixels(); i++){
    LeftStrips.setPixelColor(i,strip.Color(90,40,0));
    RightStrips.setPixelColor(i,strip.Color(90,40,0));
    BackStrips.setPixelColor(i,strip.Color(90,40,0));
    LeftCollectStrips.setPixelColor(i,strip.Color(90,40,0));
    RightCollectStrips.setPixelColor(i,strip.Color(90,40,0));
  }
  LeftStrips.show();
  RightStrips.show();
  BackStrips.show();
  LeftCollectStrips.show();
  RightCollectStrips.show();
  
  delay(200);
  
  for(i=0; i<strip.numPixels(); i++){
    LeftStrips.setPixelColor(i,strip.Color(0,0,0));
    RightStrips.setPixelColor(i,strip.Color(0,0,0));
    BackStrips.setPixelColor(i,strip.Color(0,0,0));
    LeftCollectStrips.setPixelColor(i,strip.Color(0,0,0));
    RightCollectStrips.setPixelColor(i,strip.Color(0,0,0));
  }
  LeftStrips.show();
  RightStrips.show();
  BackStrips.show();
  LeftCollectStrips.show();
  RightCollectStrips.show();
  
  delay(200);
}

void yellowflash(){
  int i;
  int c=0;

  for(int i=0; i<strip.numPixels();i++){
    strip.setPixelColor(i,strip.Color(90,40,0));
  }

  strip.show();
  for(int c = 100; c > 1; c--){
    for(int i=0; i<strip.numPixels(); i++){
      strip.setPixelColor(i,strip.Color(c,c/2,0));   
    } 
    delay(5);
    strip.show();
  }
}
#define PI 3.14159265
void wave(uint32_t c, int cycles, uint8_t wait) {
  float y;
  byte  r, g, b, r2, g2, b2;

  // Need to decompose color into its r, g, b elements
  g = (c >> 16) & 0x7f;
  r = (c >>  8) & 0x7f;
  b =  c        & 0x7f; 

  for(int x=0; x<(strip.numPixels()*5); x++)
  {
    for(int i=0; i<strip.numPixels(); i++) {
      y = sin(PI * (float)cycles * (float)(x + i) / (float)strip.numPixels());
      if(y >= 0.0) {
        // Peaks of sine wave are white
        y  = 1.0 - y; // Translate Y to 0.0 (top) to 1.0 (center)
        r2 = 127 - (byte)((float)(127 - r) * y);
        g2 = 127 - (byte)((float)(127 - g) * y);
        b2 = 127 - (byte)((float)(127 - b) * y);
      } 
      else {
        // Troughs of sine wave are black
        y += 1.0; // Translate Y to 0.0 (bottom) to 1.0 (center)
        r2 = (byte)((float)r * y);
        g2 = (byte)((float)g * y);
        b2 = (byte)((float)b * y);
      }
      LeftStrips.setPixelColor(15 - i, r2, g2, b2);
      RightStrips.setPixelColor(i, r2, g2, b2);
      BackStrips.setPixelColor(i, r2, g2, b2);
      LeftCollectStrips.setPixelColor(i, r2, g2, b2);
      RightCollectStrips.setPixelColor(15 - i, r2, g2, b2);
    }
    LeftStrips.show();
    RightStrips.show();
    BackStrips.show();
    LeftCollectStrips.show();
    RightCollectStrips.show();
    delay(wait);
  }
}

void flames(uint8_t wait, uint32_t r,uint32_t g,uint32_t b){
  int variable = 3;
  for(int i = 0; i <= strip.numPixels(); i++){
    for(int red = 0; red < i; red++){
      strip.setPixelColor(red,strip.Color(127,0,0));
    }
    for(int orange = 0; orange < i*2/3; orange++){
      strip.setPixelColor(orange,strip.Color(117,20,0));
    }
    for(int yellow = 0; yellow < i/3; yellow++){
      strip.setPixelColor(yellow,strip.Color(127,60,0));
    }
    strip.show();
    delay(wait);
  }

  for(int i = 0; i <= strip.numPixels(); i++){
    for(int red = i; red < strip.numPixels(); red++){
      strip.setPixelColor(red,strip.Color(127,0,0));
    }
    for(int orange = i; orange < strip.numPixels()*2/3; orange++){
      strip.setPixelColor(orange,strip.Color(117,20,0));
    }
    for(int yellow = i; yellow < strip.numPixels()/3; yellow++){
      strip.setPixelColor(yellow,strip.Color(127,60,0));
    }
    strip.setPixelColor(i,strip.Color(0,0,0));
    strip.show();
    delay(wait);      
  }   
}
void scanner(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  int i, j, pos, dir;

  pos = 0;
  dir = 1;

  for(i=0; i<((strip.numPixels()-1) * 8); i++) {
    // Draw 5 pixels centered on pos.  setPixelColor() will clip
    // any pixels off the ends of the strip, no worries there.
    // we'll make the colors dimmer at the edges for a nice pulse
    // look
    LeftStrips.setPixelColor(15 - (pos - 2), strip.Color(r/4, g/4, b/4));
    LeftStrips.setPixelColor(15 - (pos - 1), strip.Color(r/2, g/2, b/2));
    LeftStrips.setPixelColor(15 - pos, strip.Color(r, g, b));
    LeftStrips.setPixelColor(15 - (pos + 1), strip.Color(r/2, g/2, b/2));
    LeftStrips.setPixelColor(15 - (pos + 2), strip.Color(r/4, g/4, b/4));
    
    RightStrips.setPixelColor(pos - 2, strip.Color(r/4, g/4, b/4));
    RightStrips.setPixelColor(pos - 1, strip.Color(r/2, g/2, b/2));
    RightStrips.setPixelColor(pos, strip.Color(r, g, b));
    RightStrips.setPixelColor(pos + 1, strip.Color(r/2, g/2, b/2));
    RightStrips.setPixelColor(pos + 2, strip.Color(r/4, g/4, b/4));
    
    BackStrips.setPixelColor(pos - 2, strip.Color(r/4, g/4, b/4));
    BackStrips.setPixelColor(pos - 1, strip.Color(r/2, g/2, b/2));
    BackStrips.setPixelColor(pos, strip.Color(r, g, b));
    BackStrips.setPixelColor(pos + 1, strip.Color(r/2, g/2, b/2));
    BackStrips.setPixelColor(pos + 2, strip.Color(r/4, g/4, b/4));
    
    LeftCollectStrips.setPixelColor(pos - 2, strip.Color(r/4, g/4, b/4));
    LeftCollectStrips.setPixelColor(pos - 1, strip.Color(r/2, g/2, b/2));
    LeftCollectStrips.setPixelColor(pos, strip.Color(r, g, b));
    LeftCollectStrips.setPixelColor(pos + 1, strip.Color(r/2, g/2, b/2));
    LeftCollectStrips.setPixelColor(pos + 2, strip.Color(r/4, g/4, b/4));
    
    RightCollectStrips.setPixelColor(15 - (pos - 2), strip.Color(r/4, g/4, b/4));
    RightCollectStrips.setPixelColor(15 - (pos - 1), strip.Color(r/2, g/2, b/2));
    RightCollectStrips.setPixelColor(15 - pos, strip.Color(r, g, b));
    RightCollectStrips.setPixelColor(15 - (pos + 1), strip.Color(r/2, g/2, b/2));
    RightCollectStrips.setPixelColor(15 - (pos + 2), strip.Color(r/4, g/4, b/4));

    LeftStrips.show();
    RightStrips.show();
    BackStrips.show();
    LeftCollectStrips.show();
    RightCollectStrips.show();
    delay(wait);
    // If we wanted to be sneaky we could erase just the tail end
    // pixel, but it's much easier just to erase the whole thing
    // and draw a new one next time.
    for(int i = 0; i < strip.numPixels(); i++){
      LeftStrips.setPixelColor(i,strip.Color(0,0,0));
      RightStrips.setPixelColor(i,strip.Color(0,0,0));
      BackStrips.setPixelColor(i,strip.Color(0,0,0));
      LeftCollectStrips.setPixelColor(i,strip.Color(0,0,0));
      RightCollectStrips.setPixelColor(i,strip.Color(0,0,0));
    }
    // Bounce off ends of strip
    pos += dir;
    if(pos < 0) {
      pos = 1;
      dir = -dir;
    } 
    else if(pos >= strip.numPixels()) {
      pos = strip.numPixels() - 2;
      dir = -dir;
    }
  }
}

void ProgressBar(){

  for(int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(127,127,127));
    strip.show();
    delay(1000/strip.numPixels());
  }
  while(true){

    for(int i=0;i<strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(0,0,0));

    }
    strip.show();

    delay(75);
    for(int i=0;i<strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(127,127,127));

    }
    strip.show();

    delay(75);


  }


}








