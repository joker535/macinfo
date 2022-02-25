//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
char buf[8];
int mcVal[2];
int bufIndex = 0;
int curPos = 0;
int state = 0; //0初始，1m , 2c , 3s 

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
SSD1306Wire display(0x3c, 5, 4);  
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void loop() {
//  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
//  }

  if (SerialBT.available() > 0) {
    int data = SerialBT.read();
    showMC((char)data);
  }
  delay(20);
}

void drawFontFaceDemo(int m , int c) {
  display.clear();
  // Font Demo1
  // create more fonts at http://oleddisplay.squix.ch/
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0,  String(m));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, String(c));
  display.display();
  delay(10);
}

void showMC(char data ){
      if(state == 0){
        if(data == 'm'){
          state = 1;
        }
      }else if(state == 1){
        if(data == 'c'){
          state = 2;
        }else{
          state = 0;
        }
      }else if(state == 2){
        if(data == 's'){
          state = 3;
          bufIndex = 0;
          curPos = 0;
        }else{
          state = 0;
        }
      }else if(state == 3){
        if(data == 'm' || data == '\n' || data == 's'){
         
          buf[bufIndex] = '\0';
          int value = atoi(buf);
          bufIndex = 0;
          mcVal[curPos++] = value;
          if(data == 's'){
            
          }else{
              dacWrite(25,mcVal[0]);
            Serial.println(mcVal[0]);
            dacWrite(26,mcVal[1]);
             Serial.println(mcVal[1]);
             drawFontFaceDemo(mcVal[0],mcVal[1]);
            state = 0;
          }

        }else{
           buf[bufIndex++] = data;
        }
      }else {

      }
}
  