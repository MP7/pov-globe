#include <Time.h> 

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
boolean oneCycle = false;
int count = 0; // Count the number of 
boolean front = false;
boolean back = false;
unsigned long time;
int led = 13;
void setup() {
  // declare the ledPin as an OUTPUT:
 Serial.begin(9600);
 pinMode(led, OUTPUT);  
}

void loop(){

  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  /*
  if(sensorValue>200){
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(led, LOW);
  }
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  */
  
  if(!oneCycle){//one cycle
      if(sensorValue >350) front = true;//meet 1st magnet, value read ~ 1023 
      if(sensorValue <100) back = true; //meet 2nd magnet, value read ~ 5 or 6
    //Serial.println(sensorValue);       
   }
    oneCycle = front && back;
  if(oneCycle) {  
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(80);               // wait for a 0.08 seconds; about 0.1 seconds/cycle
    digitalWrite(led, LOW);

    count++; 
    oneCycle = false;  
    front = false;
    back = false;
    if(count >= 2 || count == 1000){     
    Serial.println(sensorValue); 
    Serial.print("count");
    Serial.println(count);
    time = millis();
    Serial.println(time);}
    }
}
  
 


