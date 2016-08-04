/**
 * trashtalk - Interactive Rubbish Bin
 * 
 * A South East Makerspace project developed for the Waterford Imagine Festival 2016 
 * Github: https://github.com/semkr/digistreets
 * Wiki: https://wiki.southeastmakerspace.org/projects/digistreets/talking_rubbish/start
 * Version: 0.1.0
 */

#define PIN_IN  6
#define PIN_OUT 5

void play() {
  digitalWrite(PIN_OUT, LOW);
  delay(100);
  digitalWrite(PIN_OUT, HIGH);  
}

void setup(){
  Serial.begin(9600);
  
  pinMode(PIN_IN,  INPUT );
  pinMode(PIN_OUT, OUTPUT);
  
  digitalWrite(PIN_OUT, HIGH);  

  delay(2000);      //allow things to stabilize, in case the mp3 module needs time and whatnut
  play();           //trigger the mp3 once on startup just to test everything
}

void loop(){
  int val = digitalRead(PIN_IN);
  Serial.println(val);
  
  if(val == HIGH){
    Serial.println("1st yes - check again in a second");

    delay(1000);
    val = digitalRead(PIN_IN);
    Serial.println(val);
    
    if(val == HIGH){    
      Serial.println("2nd yes - play a clip");
      play();
    }
    
    delay(10000);
  }
  else {
    Serial.println("no");
  }
  delay(1000);
}