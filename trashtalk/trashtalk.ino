/**
 * trashtalk - Interactive Rubbish Bin
 * 
 * A South East Makerspace project developed for the Waterford Imagine Festival 2016 
 * Github: https://github.com/semkr/digistreets
 * Wiki: https://wiki.southeastmakerspace.org/projects/digistreets/talking_rubbish/start
 * Version: 0.1.0
 */

#include <SoftwareSerial.h>
//#include <DFPlayer_Mini_Mp3.h>

int inPin;
int outPin;

void setup(){
  Serial.begin(9600);
  //mp3_set_serial(Serial);
  //delay(1);
  //mp3_set_volume(15);
  inPin = 6;
  outPin = 5;
  
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);

  //mp3_play();
}

void loop(){
  int val = digitalRead(inPin);
  Serial.println(val);
  
  if(val == LOW){
    delay(1000);
    val = digitalRead(inPin);
    Serial.println(val);
    Serial.println("1st yes");
    if(val == LOW){    
      //mp3_play(1);
      Serial.println("2nd yes");
        digitalWrite(outPin, LOW);
      delay(100);
      digitalWrite(outPin, HIGH);
    }
    delay(10000);
  }
  else {
    Serial.println("no");
  }
  delay(1000);
}

