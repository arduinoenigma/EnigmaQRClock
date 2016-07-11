// A QR Clock for the Arduino UNO + Seeed Touchscreen LCD platform
// by @arduinoenigma 
// uses a modified @chooftech QR library and a modified Xark display driver
// update times of a second are possible
// http://ch00ftech.com/2013/04/23/optimizing-the-qr-clock/
// http://ch00ftech.com/wp-content/uploads/2012/10/main1.c
//
// to set the time, open a serial monitor and type the following command
// r1;h15;m22;s25;u10;d;x;
// r1 sets rotation so plug is to the right. Any rotation is fine, setting is for purists
// h15 sets hours to 15
// m22 sets minutes to 22
// s10 sets seconds to 25
// u10 sets update rate to 10 seconds, 1,5,10,15,20,30,60 are valid
// d shows the time
// x starts the clock now
// if a command with a two digit parameter is sent with two digits, the semicolon can be omitted
// the following are valid strings
// r1h15m22s25u10dx
// r1h9;m5;s25u1;dx
// 

#define TFTSeed
//#define TFTAdafruit

#include <SPI.h>
#include <FastTftILI9341.h>      //https://github.com/arduinoenigma/FastSeedTFTv2

PDQ_ILI9341 Tft;

//raw input string from user GLOBAL VAR to generate();
char input[17];

//GLOBAL VAR to generate() and printcode();
unsigned char outputmatrix[56] = {128, 63, 192, 247, 247, 137, 254, 34, 209, 95, 36, 250, 139, 124, 127, 31, 160, 10, 248, 255, 255, 191, 255, 255, 255, 255, 255, 254, 255, 255, 255, 255, 251, 255, 255, 253, 63, 224, 255, 247, 253, 255, 162, 255, 95, 244, 255, 139, 254, 127, 223, 255, 15, 248, 255, 255};

unsigned long ul_LastGenerated = 0UL;

byte hours = 0;
byte mins = 0;
byte secs = 0;
byte ampm = 0;
byte update = 10;
byte rotation = 0;

byte xo = 15;
byte yo = 55;

void advancetime()
{
  input[0] = (hours / 10) + '0';
  input[1] = (hours - (hours / 10) * 10) + '0';
  input[2] = ':';
  input[3] = (mins / 10) + '0';
  input[4] = (mins - (mins / 10) * 10) + '0';

  //input[5] = ';';
  //input[6] = 0;

  input[5] = ':';
  input[6] = (secs / 10) + '0';
  input[7] = (secs - (secs / 10) * 10) + '0';
  input[8] = ';';
  input[9] = 0;


  secs += update;
  if (secs >= 60)
  {
    secs = secs - 60;
    mins++;
    if (mins == 60)
    {
      mins = 0;
      hours++;
      if (hours == 24)
      {
        mins = 0;
        hours = 0;
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  Tft.TFTinit();

  Serial.println("valid init string is: r1;h15;m22;s25;u10;d;x;");

  advancetime();
  generate();
  ul_LastGenerated = millis();
  printcode(&outputmatrix[0]);

  advancetime();
  generate();
}

void loop() {

  unsigned long ul_CurrentMillis;
  ul_CurrentMillis = millis();

  SerialFSM();

  if ((ul_CurrentMillis - ul_LastGenerated) >= (update * 1000))
  {
    ul_LastGenerated += update * 1000;
    printcode(&outputmatrix[0]);
    advancetime();
    generate();
  }



}
