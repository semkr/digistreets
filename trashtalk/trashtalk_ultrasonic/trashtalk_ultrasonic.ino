/**
 * trashtalk - Interactive Rubbish Bin
 * 
 * A South East Makerspace project developed for the Waterford Imagine Festival 2016 
 * Github: https://github.com/semkr/digistreets
 * Wiki: https://wiki.southeastmakerspace.org/projects/digistreets/talking_rubbish/start
 * Version: 0.3.0
 *
 * This sketch uses the NewPing library which you can get at: http://playground.arduino.cc/Code/NewPing
 */
 
#include <NewPing.h>

#define MAX_DISTANCE 80 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define TRIGGER_PIN  0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define PIN_OUT      2  // Go low to activate MP3 module
#define PLAY_TIME    15 // Number of seconds it will allow an mp3 file to play for without possible interruption

unsigned int distance;
unsigned int previous_distance;
unsigned int threshold;
unsigned int low_threshold;
unsigned int high_threshold;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void play(){
  //Serial.println("play");
  digitalWrite(PIN_OUT, LOW);
  delay(100);
  digitalWrite(PIN_OUT, HIGH);
  delay(PLAY_TIME * 1000);
}

boolean check_distance(){
  //Serial.println("check_distance");
  if(distance == 5 || distance == 0){ return false; } // Seem to be getting a lot of invalid values from the sensor/library ignore
  
  threshold = (previous_distance / 5) + 1; // Calculate what 25% of the previous distance is
  low_threshold = previous_distance - threshold; // 25% lower than previous_distance
  high_threshold = previous_distance + threshold; // 25% higher than previous_distance

  if(low_threshold < 0) { low_threshold = 0; } // Ensure the low_threshold does not go negative
  if(high_threshold > MAX_DISTANCE) { high_threshold = MAX_DISTANCE; } // Ensure we are activating only up to the MAX_DISTANCE value

  if(distance <= low_threshold || distance > high_threshold){ 
    // If the new distance is more than 25% lower or higher than the previous distance, activate
    return true;
  }
  else{
    return false;
  }
}

void setup() {
  //Serial.begin(9600);
  pinMode(PIN_OUT, OUTPUT);
  digitalWrite(PIN_OUT, HIGH);
  delay(3000); // allow things to stabilize, incase the mp3 module needs time
  play(); //trigger the mp3 once on startup just to test everything
  previous_distance = sonar.convert_cm(sonar.ping_median(40)); // Set the previous distance
}

void loop() {
  distance = sonar.convert_cm(sonar.ping_median(15)); // Take 15 readings and average them
  //Serial.println(distance);
  
  if(check_distance()){
    play();
    previous_distance = distance;
  }
  else{
    delay(100);
  }
}
