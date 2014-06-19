#include "LPD8806.h"
#include "SPI.h"
byte me = 1;

int nLEDs = 16;

int dataPinLeft = 13;
int clockPinLeft = 12;

int dataPinRight  = 11;
int clockPinRight = 10;

int dataPinBack  = 9;
int clockPinBack = 8;

int dataPinRightCollector = 4;
int clockPinRightCollector = 3;

int dataPinLeftCollector = 2;
int clockPinLeftCollector = 1;

LPD8806 leftstrips = LPD8806(nLEDs, dataPinLeft, clockPinLeft);
LPD8806 rightstrips = LPD8806(nLEDs, dataPinRight, clockPinRight);
LPD8806 backstrips = LPD8806(nLEDs, dataPinBack, clockPinBack);
LPD8806 rightCollectorstrips = LPD8806(nLEDs, dataPinRightCollector,clockPinRightCollector);
LPD8806 leftCollectorstrips = LPD8806(nLEDs,dataPinLeftCollector,clockPinRightCollector);

LPD8806 strips[6];

void setup(){
  strips[0] = leftCollectorstrips;
  strips[1] = leftstrips;
  strips[2] = backstrips;
  strips[3]=rightstrips;
  strips[4] = rightCollectorstrips;
  for(int a = 0; a<5;a++){
  strips[a].begin();
  strips[a].show();
  }
  //void dither(uint32_t c, uint8_t wait);

  // void scanner(uint8_t r, uint8_t g, uint8_t b, uint8_t wait);
  //void wave(uint32_t c, int cycles, uint8_t wait);
  //uint32_t Wheel(uint16_t WheelPos);
  //void launchLight(uint32_t,uint32_t,uint8_t);

}
void loop(){
  
  switch(me){   
  case 1: 
  for(int a = 0 ; a <5;a++){
    colorWipe(strips[a].Color(  127, 127,   127), 50);  // Green
    colorWipe(strips[a].Color(  0, 127,   0), 50);  // WHITE
    colorWipe(strips[a].Color(  0, 0,   0), 1);  // BLANK
  }break;
  case 2:
  for(int a = 0 ; a <5;a++){
    doubleWipe(strips[a],strips[a].Color(127,0,0),strips[a].Color(0,0,127),50);
    doubleWipe(strips[a],strips[a].Color(0,127,0),strips[a].Color(127,127,127),50);
    colorWipe(strips[a].Color(  0, 0,   0), 1);  // BLANK  
  }break;
  case 3:
  for(int a = 0 ; a <5;a++){
    dither(strips[a],strips[a].Color(0,127,0), 15);// green
    dither(strips[a],strips[a].Color(127,127,127), 15);// white
    colorWipe(strips[a].Color(  0, 0,   0),1);  // BLANK
  }break;
  case 4:
  for(int a = 0 ; a <5;a++){
    scanner(strips[a],0,127,0, 8);        // green
    colorWipe(strips[a].Color(  0, 0,   0), 1);  // BLANK
  }break;
  case 5:
  for(int a = 0;a<5;a++){
    theaterChase(strips[a],strips[a].Color(127, 127, 127), 50); // White
    theaterChase(strips[a],strips[a].Color(0, 127, 0), 50); // green
    colorWipe(strips[a].Color(  0, 0,   0), 1);  // BLANK
  }break;
  case 6:
  for(int a = 0;a<5;a++){
    wave(strips[a].Color(0,127,127), 2, 40); // green icy
    colorWipe(strips[a].Color(  0, 0,   0), 1);  // BLANK
  }break;
  case 7:
    randomRainbow(500,5);

    break;
  case 8:
//  scannerPAC(2,40);
  launchLight(strips[a],strips.Color(127,0,0),40);
  launchLight(strips[a],strips.Color(127,10,0),40);
  colorWipe(strips.Color(0,0,0),1); 
  Wipe4(strips[a],100,strips.Color(0,127,0),strips.Color(127,127,127));
  Wipe4(strips[a],100,strips.Color(0,0,127),strips.Color(127,0,0)); 
  colorWipe(strips.Color(0,0,0),1);
  
  binaryCount(20,1000,strips.Color(0,127,0));
  colorWipe(strips.Color(0,0,0),1);  */

    break;
  }
   me++;
  if(me >8){
    me = 0;
  }
  colorChase(strips.Color(0, 127, 0), 50); // Green
  colorChase(strips.Color(127, 127, 127), 50); // White





}

int dither(LPD8806 strips, uint32_t c, uint8_t wait) {
  int hiBit = 0;
  int n = strips.numPixels() - 1;
  for(int bit=1; bit < 0x8000; bit <<= 1){
    if(n & bit) hiBit = bit;
  }
  int bit, reverse;
  for(int i=0; i<(hiBit << 1); i++) {
    reverse = 0;
    for(bit=1; bit <= hiBit; bit <<= 1) {
      reverse <<= 1;
      if(i & bit) reverse |= 1;
    }
    strips.setPixelColor(reverse, c);
    strips.show();
    d1elay(wait);
  }
  delay(250);
}

void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strips.numPixels(); i++) {
    strips.setPixelColor(i, c);
    strips.show();
    delay(wait);
  }
}

void colorChase(LPD8806 strips, uint32_t c, uint8_t wait) {
  int i;
  for(1i=0; i<strips.numPixels(); i++) strips.setPixelColor(i, 0);
  for(i=0; i<strips.numPixels(); i++) {
    strips.setPixelColor(i, c); // Set new pixel 'on'
    strips.show();              // Refresh LED states
    strips.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }
}
//THECODEFORBOBBYBYHIREN
void launchLight(uint32_t c , uint8_t wait){
  int i;
  int h=15;
  for(i=0; i<3; i++) strips.setPixelColor(i,0);
  for(i=0; i<3; i++){
    strips.setPixelColor(i,c);
    strips.show();
    strips.setPixelColor(i,0);
    delay(wait);
  }
}

void fire(LPD8806 strips, uint32_t c , uint8_t wait){
  int i;
  for(i=3; i<strips.numPixels(); i++) strips.setPixelColor(i,0);
  for(i=3; i<strips.numPixels(); i++){
    strips.setPixelColor(i,c);
    strips.show();
    strips.setPixelColor(i,0);
    delay(wait);
  }
  

  for(i=3; i<strips.numPixels(); i++) strips.setPixelColor(i,0);
  for(i=3; i<strips.numPixels(); i++){
    strips.setPixelColor(i,c);
    strips.show();
    strips.setPixelColor(i,0);
    delay(wait);
  }
}

void theaterChase(LPD8806 strips, uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strips.numPixels(); i=i+3) {
        strips.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strips.show();

      delay(wait);

      for (int i=0; i < strips.numPixels(); i=i+3) {
        strips.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void scanner(LPD8806 strips, uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  int i, j, pos, dir;

  pos = 0;
  dir = 1;

  for(i=0; i<((strips.numPixels()-1) * 8); i++) {
    // Draw 5 pixels centered on pos.  setPixelColor() will clip
    // any pixels off the ends of the strips, no worries there.
    // we'll make the colors dimmer at the edges for a nice pulse
    // look
    strips.setPixelColor(pos - 2, strips.Color(r/4, g/4, b/4));
    strips.setPixelColor(pos - 1, strips.Color(r/2, g/2, b/2));
    strips.setPixelColor(pos, strips.Color(r, g, b));
    strips.setPixelColor(pos + 1, strips.Color(r/2, g/2, b/2));
    strips.setPixelColor(pos + 2, strips.Color(r/4, g/4, b/4));

    strips.show();
    delay(wait);
    // If we wanted to be sneaky we could erase just the tail end
    // pixel, but it's much easier just to erase the whole thing
    // and draw a new one next time.
    for(j=-2; j<= 2; j++) 
      strips.setPixelColor(pos+j, strips.Color(0,0,0));
    // Bounce off ends of strips
    pos += dir;
    if(pos < 0) {
      pos = 1;
      dir = -dir;
    } 
    else if(pos >= strips.numPixels()) {
      pos = strips.numPixels() - 2;
      dir = -dir;
    }
  }
}

// Sine wave effect
#define PI 3.14159265
void wave(uint32_t c, int cycles, uint8_t wait) {
  float y;
  byte  r, g, b, r2, g2, b2;

  /* Need to decompose color into its r, g, b elements
   g = (c >> 16) & 0x7f;
   r = (c >>  8) & 0x7f;
   b =  c        & 0x7f; 
   */
  g = (c >> 16) | 0;
  r = (c >> 8)  | 0x0;
  b = c         | 0x00;
  for(int x=0; x<(strips.numPixels()*5); x++)
  {
    for(int i=0; i<strips.numPixels(); i++) {
      y = sin(PI * (float)cycles * (float)(x + i) / (float)strips.numPixels());
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
      strips.setPixelColor(i, r2, g2, b2);
    }
    strips.show();
    delay(wait);
  }
}


//Jason's crazy cool code
void randomRainbow(int cycles,uint8_t wait){
  int j;
  for (j=0; j < cycles; j++) {
    // 5 cycles of all 384 colors in the wheel
    strips.setPixelColor(random(0,16), strips.Color(random(0,2)*127,random(0,2)*127,random(0,2)*127));
    // write all the pixels out
    strips.show();
    delay(wait);
  }
}*/

void Wipe4(LPD8806 strips, uint8_t wait, uint32_t c,uint32_t cc){
  int j = strips.numPixels();  
    for(int i = 0; i < 4; i ++){
      strips.setPixelColor(i,c);
      strips.setPixelColor(j/2-(i+1),cc);
      strips.setPixelColor(j/2+i,c);
      strips.setPixelColor(j-(i+1),cc);
      strips.show();
      delay(wait);
   } 
}

void doubleWipe(LPD8806 strips, uint32_t c, int cc, uint8_t wait){
  int i;
  int j = 15;
  for (i=0; i < strips.numPixels(); i++) {
    strips.setPixelColor(i, c);
    strips.setPixelColor(j-i,cc);
    strips.show();
    delay(wait);
  }
}

/*void scannerPAC(LPD8806 strips, int cycles,uint8_t wait) {
  for(int cycled = 0; cycled < cycles; cycled++){
  for(int x = 0; x < strips.numPixels();x++){
    strips.setPixelColor(x,strips.Color(0,0,0));
  }
  strips.setPixelColor((strips.numPixels()/3)-1,strips.Color(127,127,127));
  strips.setPixelColor((2*strips.numPixels()/3)-1,strips.Color(127,127,127));
  strips.setPixelColor((strips.numPixels())-1,strips.Color(127,127,127));

  int i, j, pos, dir;
  pos = 0;
  dir = 1;
  for(i=0; i<((strips.numPixels()-1)*2 + 13); i++) {
    if(dir > 0){
      strips.setPixelColor(pos, strips.Color(127, 63, 0));
      strips.setPixelColor(pos - 2, strips.Color(127, 0, 0));
      strips.setPixelColor(pos - 3, strips.Color(127, 0, 127));
      strips.setPixelColor(pos - 4, strips.Color(0, 127, 127));
      strips.setPixelColor(pos - 5, strips.Color(127, 20, 0));
      strips.setPixelColor(pos - 6, strips.Color(0,0,0));
    }else{
      strips.setPixelColor(pos - 6, strips.Color(127, 63, 0));
      strips.setPixelColor(pos - 5, strips.Color(0,0,0));
      strips.setPixelColor(pos - 4, strips.Color(127, 0, 0));
      strips.setPixelColor(pos - 3, strips.Color(127, 0, 127));
      strips.setPixelColor(pos - 2, strips.Color(0, 127, 127));
      strips.setPixelColor(pos - 1, strips.Color(127, 20, 0));
      strips.setPixelColor(pos, strips.Color(0,0,0));
    }

    strips.show();
    delay(wait);
    for(j=-2; j<= 2; j++) 
      strips.setPixelColor(pos+j, strips.Color(0,0,0));
    pos += dir;
    if(pos < 0) {
      pos = 1;
      dir = -dir;
    } 
    else if(pos >= strips.numPixels()+6) {
      pos = strips.numPixels()+6;
      dir = -dir;
    }
  }
  }
}*/
void binaryCount(long cycles, uint8_t wait, uint32_t c){
  int bit1=0,bit2=0,bit3=0,bit4=0,bit5=0,bit6=0,bit7=0,bit8=0,bit9=0,bit10=0,bit11=0,bit12=0,bit13=0,bit14=0,bit15=0,bit16=0;
  for( int i = 0; i< cycles ; i++){    
    if(i%2 == 0){
      strips.setPixelColor(0,c);
      if(bit1 == 0) {
        bit1=1;
      } else {
        bit1=0;
      }
    }else{
      strips.setPixelColor(0,strips.Color(0,0,0));
    }
    if((i+bit1)%2 == 0){
      strips.setPixelColor(1,c);
    }else{
      strips.setPixelColor(1,strips.Color(0,0,0));
    }
    if((i+1)%4 == 0){
      if(bit3 == 1){
        bit3 = 0;
        strips.setPixelColor(2,strips.Color(0,0,0));
      }else{
        strips.setPixelColor(2,c);
        bit3 = 1;        
      } 
    }
    if((i+1)%8 == 0){
      if(bit4 == 1){
        strips.setPixelColor(3,strips.Color(0,0,0));
        bit4 = 0;
      }else{
        strips.setPixelColor(3,c);
        bit4 = 1;
      }
    }    
    if((i+1)%16 == 0){
      if(bit5 == 1){
        strips.setPixelColor(4,strips.Color(0,0,0));
        bit5 = 0;
      }else{
        strips.setPixelColor(4,c);
        bit5 = 1;
      }
    }
    if((i+1)%32 == 0){
      if(bit6 == 1){
        strips.setPixelColor(5,strips.Color(0,0,0));
        bit6 = 0;
      }else{
        strips.setPixelColor(5,c);
        bit6 = 1;
      }
    }
    if((i+1)%64 == 0){
      if(bit7 == 1){
        strips.setPixelColor(6,strips.Color(0,0,0));
        bit7 = 0;
      }else{
        strips.setPixelColor(6,c);
        bit7 = 1;
      }
    }
    if((i+1)%128 == 0){
      if(bit8 == 1){
        strips.setPixelColor(7,strips.Color(0,0,0));
        bit8 = 0;
      }else{
        strips.setPixelColor(7,c);
        bit8 = 1;
      }
    }
    if((i+1)%256 == 0){
      if(bit9 == 1){
        strips.setPixelColor(8,strips.Color(0,0,0));
        bit9 = 0;
      }else{
        strips.setPixelColor(8,c);
        bit9 = 1;
      }
    }
    if((i+1)%512 == 0){
      if(bit10 == 1){
        strips.setPixelColor(9,strips.Color(0,0,0));
        bit10 = 0;
      }else{
        strips.setPixelColor(9,c);
        bit10 = 1;
      }
    }
    if((i+1)%1024 == 0){
      if(bit11 == 1){
        strips.setPixelColor(10,strips.Color(0,0,0));
        bit11 = 0;
      }else{
        strips.setPixelColor(10,c);
        bit11 = 1;
      }
    }
    if((i+1)%2048 == 0){
      if(bit12 == 1){
        strips.setPixelColor(11,strips.Color(0,0,0));
        bit12 = 0;
      }else{
        strips.setPixelColor(11,c);
        bit12 = 1;
      }
    }
    if((i+1)%4096 == 0){
      if(bit13 == 1){
        strips.setPixelColor(12,strips.Color(0,0,0));
        bit13 = 0;
      }else{
        strips.setPixelColor(12,c);
        bit13 = 1;
      }
    }
    if((i+1)%8192 == 0){
      if(bit14 == 1){
        strips.setPixelColor(13,strips.Color(0,0,0));
        bit14 = 0;
      }else{
        strips.setPixelColor(13,c);
        bit14 = 1;
      }
    }
    if((i+1)%16384 == 0){
      if(bit15 == 1){
        strips.setPixelColor(14,strips.Color(0,0,0));
        bit15 = 0;
      }else{
        strips.setPixelColor(14,c);
        bit15 = 1;
      }
    }
    if((i+1)%32768 == 0){
      if(bit16 == 1){
        strips.setPixelColor(15,strips.Color(0,0,0));
        bit16 = 0;
      }else{
        strips.setPixelColor(15,c);
        bit16 = 1;
      }
    }
    strips.show();
    delay(wait);
  }
}


/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
  case 0:
    r = 127 - WheelPos % 128;   //Red down
    g = WheelPos % 128;      // Green up
    b = 0;                  //blue off
    break; 
  case 1:
    g = 127 - WheelPos % 128;  //green down
    b = WheelPos % 128;      //blue up
    r = 0;                  //red off
    break; 
  case 2:
    b = 127 - WheelPos % 128;  //blue down 
    r = WheelPos % 128;      //red up
    g = 0;                  //green off
    break; 
  }
  return(strips.Color(r,g,b));
}






