/**
 * trashtalk - Interactive Rubbish Bin
 * 
 * A South East Makerspace project developed for the Waterford Imagine Festival 2016 
 * Github: https://github.com/semkr/digistreets
 * Wiki: https://wiki.southeastmakerspace.org/projects/digistreets/talking_rubbish/start
 * Version: 0.1.0
 */
 
#include <NewPing.h>

#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define PIN_OUT 5

unsigned int value;
unsigned int distance;
unsigned int tenPer;
unsigned int low;
unsigned int high;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void play(){
  Serial.println(" Trigger");
  digitalWrite(PIN_OUT, LOW);
  delay(100);
  digitalWrite(PIN_OUT, HIGH);
}

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  value = 0;
  low = 0;
  high = 0;

  pinMode(PIN_OUT, OUTPUT);
  digitalWrite(PIN_OUT, HIGH);
  delay(2000);      //allow things to stabilize, in case the mp3 module needs time and whatnut
  play(); //trigger the mp3 once on startup just to test everything
  distance = sonar.convert_cm(sonar.ping_median(40));
}

void loop() {
  value = sonar.convert_cm(sonar.ping_median(15));

  if (value != 5){
    tenPer = (distance/5)+1;
    if (distance < tenPer) {
      low = 0;   
    }
    else {
      low = distance - tenPer;  
    }
    high = distance + tenPer;
  
    Serial.print(value); // Send ping, get distance in cm and print result (0 = outside set distance range)
    Serial.print(", ");
    Serial.print(tenPer);
    Serial.print(", ");
    Serial.print(low);
    Serial.print(", ");
    Serial.print(high);
  
    if(value < low || value > high){
      play();
      delay(3000);
      distance = sonar.convert_cm(sonar.ping_median(40));
    }
    else {
      Serial.println();
    }
  }
}
