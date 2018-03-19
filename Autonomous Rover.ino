#include <Servo.h> 
//#include <SoftwareSerial.h>
#include "Ultrasonic.h"
//#include "DHT.h"
//#define dht_pin=A0

//dht DHT;
//Constants - Connections     
const int motorA1= 10;     
const int motorA2= 11;  
//const int enableA = 3; 
const int motorB1= 12;     
const int motorB2= 13; 
//SoftwareSerial mySerial(0,1);//RX,TX
//const int enableB = 7;    

Ultrasonic ultrasonic(A2 ,A3); //Create Ultrsonic object ultrasonic(trig pin,echo pin)
Servo myservo;          //Create Servo object to control a servo

//Variables
int distance;         //Variable to store distance from an object
int checkRight;
int checkLeft;
int pos=100;          //Variable to store the servo position. By default 90 degrees - sensor will 'look' forward
//int speedPWM = 255;   //Change speed (PWM max 255)

void setup()
{
  Serial.begin(9600);
  myservo.attach(6);      //Servo pin connected to pin 7
  myservo.write(pos);     // tell servo to go to position in variable 'pos' 
  pinMode(3,OUTPUT);
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT); 
  //pinMode(enableA, OUTPUT);
  //pinMode(enableB, OUTPUT);
  delay(5000); //Wait 5 seconds...
  distance = ultrasonic.Ranging(CM);
}

void loop(){
   //analogWrite(enableA, speedPWM);
    //analogWrite(enableB, speedPWM);
    //Read distance...
    //while(mySerial.available())
    //{
      //char state = mySerial.read();
      //if(state=='1')
      //{
      
      distance = ultrasonic.Ranging(CM); //Tip: Use 'CM' for centimeters or 'INC' for inches
    delay(20);
    //Check for objects...
    if (ultrasonic.Ranging(CM) > 15){
      forward();
      Serial.print("Voyage started");
      Serial.print("Object is at:");
      Serial.println(distance);
    }
    else if (ultrasonic.Ranging(CM) <=15){
      stop();
       Serial.print("Object is at: ");
      Serial.println(distance);//Object detected! Stop the robot and check left and right for the better way out!
       delay(500);
       Serial.println("Sensing the area...");
      for(pos = 30; pos < 170; pos += 1){  //goes from 0 degrees to 180 degrees 
                myservo.write(pos);   
                //digitalWrite(3,HIGH);//tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position 
            } 
            
            checkLeft = ultrasonic.Ranging(CM);   //Take distance from the left side
            
            for(pos = 170; pos>=30; pos-=1){     //goes from 180 degrees to 0 degrees                           
                myservo.write(pos);
                  //digitalWrite(3,HIGH);//tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position   
            }
            
            checkRight= ultrasonic.Ranging(CM);
            
            myservo.write(100);                   // Sensor "look" forward again
            
            //Finally, take the right decision, turn left or right?
            if (checkLeft < checkRight){
              left();
              //digitalWrite(3,HIGH);
              //delay(500);
              //digitalWrite(3,LOW);// delay, change value if necessary to make robot turn.            
              }
            else if (checkLeft > checkRight){
              right();
              // digitalWrite(3,HIGH);
              //delay(500);
              //digitalWrite(3,LOW); // delay, change value if necessary to make robot turn.
            }
            else if (checkLeft <=10 && checkRight <=10){
              backward(); //The road is closed... go back and then left ;)
              left();
            }
    }
    delay(150);

}
void forward(){

  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
  //digitalWrite(3,HIGH);
  //delay(500);
  //digitalWrite(3,LOW);
}

void backward(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void right(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void stop(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  //digitalWrite(3,HIGH);
        //delay(200);
      //digitalWrite(3,LOW);
}
