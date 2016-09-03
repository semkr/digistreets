/**
 * trashtalk - Interactive Rubbish Bin
 * 
 * A South East Makerspace project developed for the Waterford Imagine Festival 2016 
 * Github: https://github.com/semkr/digistreets
 * Wiki: https://wiki.southeastmakerspace.org/projects/digistreets/talking_rubbish/start
 * Version: 0.1.0
 *
 * This sketch uses the NewPing library which you can get at: http://playground.arduino.cc/Code/NewPing
 */
 
#include <NewPing.h>

#define TRIGGER_PIN  0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define PIN_OUT 2  // Go low to activate MP3 module
#define PLAY_TIME 15

unsigned int distance;
unsigned int previous_distance;
unsigned int tenPer;
unsigned int low;
unsigned int high;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void play(){
  digitalWrite(PIN_OUT, LOW);
  delay(100);
  digitalWrite(PIN_OUT, HIGH);
  delay(PLAY_TIME * 1000);
}

void setup() {
  //Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  low = 0;
  high = 0;
  previous_distance = 0;

  pinMode(PIN_OUT, OUTPUT);
  digitalWrite(PIN_OUT, HIGH);
  delay(3000);      //allow things to stabilize, in case the mp3 module needs time and whatnut
  play(); //trigger the mp3 once on startup just to test everything
  distance = sonar.convert_cm(sonar.ping_median(40));
}

void loop() {
  distance = sonar.convert_cm(sonar.ping_median(15));

  if (distance != 5){
    tenPer = (distance/5)+1;
    low = distance - tenPer;
    high = distance + tenPer;

    if(previous_distance < low || previous_distance > high){
      play();
      previous_distance = distance;
    }
    else {
    }
  }
}
