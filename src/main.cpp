#include <Arduino.h>
#include <LiquidCrystal.h>

#include "./pinRead.h"
#include "./pinWrite.h"
#include "./hexToDec.h"
#include "./decToHex.h"
#include "./RGBWrite.h"
#include "./printValueOfPin.h"

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int indexOfArduino = 48;

String inputString = "";
boolean frameComplete = false; 

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);

  for (int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }

  pinMode(A0, INPUT);
}

void loop() {
  while (Serial.available() && frameComplete == false) {
    char inChar = (char)Serial.read();
    if (inChar == '&') {
      frameComplete = true;
    } else {
      inputString += inChar; 
    }
  }

  if (!Serial.available() && frameComplete == true) {
    // tu powinna być cała odebrana ramka
    int frameLength = inputString.length();
    char charHolder[frameLength + 1];
    inputString.toCharArray(charHolder, frameLength+1);
    char inputData[frameLength - 7];
    
    if ((int)charHolder[0] != 58) {
      // znak startu niepoprwny
      // wyślij błąd
      
    } else {
      if ((int)charHolder[1] == indexOfArduino) {
        // numer Arduino zgadza sie z numerem z ramki
        char incomingCrc[] = {charHolder[frameLength-2], charHolder[frameLength-1]};
        
        int tmpCrc = 0;
        int lengthOfCrcChars = frameLength - 2;
        for ( int i = 0; i < lengthOfCrcChars; i++ ) {
          tmpCrc += charHolder[i];
        }
        tmpCrc %= 256;

        if ( tmpCrc == hexToDec(incomingCrc) ) { // CRC is CORRECT
          if ((int)charHolder[2] == 87) { // WRITE
            if ((int)charHolder[3] == 48) {
              int pin = (int)charHolder[4] - 48;
              pinWrite(frameLength, inputData, charHolder, pin);
              Serial.print(inputString);
              Serial.print("&");
            } else if ((int)charHolder[3] == 49) {
              int pin = (int)charHolder[4] - 38;
              pinWrite(frameLength, inputData, charHolder, pin);
              Serial.print(inputString);
              Serial.print("&");
            } else if ((int)charHolder[3] == 65) { 
              int pin = (int)charHolder[4] - 34;
              pinWrite(frameLength, inputData, charHolder, pin);
              Serial.print(inputString);
              Serial.print("&");
            } else if ((int)charHolder[3] == 50) { //RGB
              int pin = 20;
              RGBWrite(frameLength, inputData, charHolder, pin);
            } else {
              // błąd pinu
              Serial.print(":0N331E&");
            }
            
          } else if ((int)charHolder[2] == 82) { // READ
            if ((int)charHolder[3] == 48) {
              int pin = (int)charHolder[4] - 48;
              int valueOfPin = pinRead(pin);
              int crcCalc = 58;
              char result[2];

              Serial.print(":");
              Serial.print((char)indexOfArduino);
              crcCalc += indexOfArduino;
              Serial.print(charHolder[2]);
              crcCalc += charHolder[2];
              Serial.print(charHolder[3]);
              crcCalc += charHolder[3];
              Serial.print(charHolder[4]);
              crcCalc += charHolder[4];
              
              crcCalc = printValueOfPin(valueOfPin, crcCalc);

              crcCalc %= 256;
              decToHex(crcCalc, result);
              Serial.print(result);
              Serial.print("&");

            } else if ((int)charHolder[3] == 49) {
              int pin = (int)charHolder[4] - 38;
              int valueOfPin = pinRead(pin);
              int crcCalc = 58;
              char result[2];
              
              Serial.print(":");
              Serial.print((char)indexOfArduino);
              crcCalc += indexOfArduino;
              Serial.print(charHolder[2]);
              crcCalc += charHolder[2];
              Serial.print(charHolder[3]);
              crcCalc += charHolder[3];
              Serial.print(charHolder[4]);
              crcCalc += charHolder[4];
              
              crcCalc = printValueOfPin(valueOfPin, crcCalc);
              
              crcCalc %= 256;
              decToHex(crcCalc, result);
              Serial.print(result);
              Serial.print("&");

            } else if ((int)charHolder[3] == 65) { 
              int pin = (int)charHolder[4] - 34;
              int valueOfPin = pinRead(pin);
              int crcCalc = 58;
              char result[2];
              
              Serial.print(":");
              Serial.print((char)indexOfArduino);
              crcCalc += indexOfArduino;
              Serial.print(charHolder[2]);
              crcCalc += charHolder[2];
              Serial.print(charHolder[3]);
              crcCalc += charHolder[3];
              Serial.print(charHolder[4]);
              crcCalc += charHolder[4];
              
              crcCalc = printValueOfPin(valueOfPin, crcCalc);

              crcCalc %= 256;
              decToHex(crcCalc, result);
              Serial.print(result);
              Serial.print("&");

            } else {
              // błąd pinu
              Serial.print(":0N331E&");
            }
          } else {
            // błąd rozkazu
            Serial.print(":0N221C&");
          }
        } else {
          //suma kontrolna sie nie zgadza
          Serial.print(":0N111A&");
        }
      }
    }
    
    inputString = "";
    frameComplete = false;
  }
}

