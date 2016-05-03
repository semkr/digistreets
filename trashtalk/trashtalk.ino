/**
 * trashtalk - Interactive Rubbish Bin
 * 
 * A South East Makerspace project developed for the Waterford Imagine Festival 2016 
 * Github: https://github.com/semkr/digistreets
 * Wiki: https://wiki.southeastmakerspace.org/projects/digistreets/talking_rubbish/start
 * Version: 0.1.0
 */

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

int inPin;

void setup(){
  Serial.begin(9600);
  mp3_set_serial(Serial);
  delay(1);
  mp3_set_volume(15);
  inPin = A0;
  pinMode(inPin, INPUT);
}

void loop(){
  int val = analogRead(inPin);
  if(val == 0){
    mp3_play();
  }
  delay(2000);
}

