/*
  Auto_Robot2019-2020

  By: BounkhongDev
*/

#include <Servo.h>
int servoPin = 5;
Servo Servo1;
int servoPin1 = 2;
Servo Servo2;


/***** Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)*****/
int enableA = 3;
int pinA1 = 8;
int pinA2 = 9;


/********Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)******/
int enableB = 4;
int pinB1 = 6;
int pinB2 = 7;

/*Ultrasonic sensor*/
const unsigned int TRIG_PIN = 52;
const unsigned int ECHO_PIN = 53;


int sensor[4] = {0, 0, 0, 0};
int count = 0, i;
boolean canCount = false;
boolean enable_ultrasonic_sensor = false;


void setup()
{
  Serial . begin ( 9600 ) ;

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Servo1.attach(servoPin);
  Servo2.attach(servoPin1);
  
  
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);

  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
}

void loop()
{  
   Servo1.write(7);//arm up


  enableMotors();
  analogWrite(enableA,95);  //speed motor A
  analogWrite(enableB,92);  //speed motor B

  sensor[0] = digitalRead(A1);
  sensor[1] = digitalRead(A2);
  sensor[2] = digitalRead(A3);
  sensor[3] = digitalRead(A4);


  if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) &&  (sensor[3] == 1) ) {
    forward(10);
    canCount = true;


  }


  else if ((sensor[0] == 0) && (sensor[1] == 0||sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) ) {
    turnRight(0);
    canCount = true;
   

  }


//  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)) {
//    turnRight(0);
//    canCount = true;
//   
//
//  }


  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0||sensor[2] == 1) && (sensor[3] == 0)  ) {
    turnLeft(0);
    canCount = true;
   

  }


//  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1)  && (sensor[3] == 0) ) {
//    turnLeft(0);
//    canCount = true;
//   
//
//  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0)  && (sensor[3] == 0) ) {
       enable_ultrasonic_sensor = false;
    if (canCount == true) {
      count++;
      canCount = false;

      if (count == 2) {
        Serial . println ("Stop1") ;
        if (enable_ultrasonic_sensor == false) {
          enable_ultrasonic_sensor = true;
        }

      } else if (count == 3) {
        Serial . println ("Stop2") ;
        delay(220);
        brake(3000);
        Servo1.write(60);//a
        delay(2000);

        Servo2.write(45); //h vang
        delay(1000);
        
         Servo1.write(7);//arm up
     
         forward(10);
      }
      else if (count == 6) {
        Serial . println ("Stop3") ;
//        brake(3000);
//        forward(10);
        if (enable_ultrasonic_sensor == false) {
          enable_ultrasonic_sensor = true;
        }

      }
      else if (count == 8) {
        Serial . println ("Stop4") ;
//        brake(3000);
//        forward(10);
        brake(3000);
        Servo1.write(60);//a
        delay(2000);

        Servo2.write(45); //h vang
        delay(1000);
        
         Servo1.write(7);//arm up
     
         forward(10);

      }
      else if (count == 10) {
        Serial . println ("Stop5") ;
//        brake(3000);
//        forward(10);

       if (enable_ultrasonic_sensor == false) {
          enable_ultrasonic_sensor = true;
        }

      }
      else if (count == 13) {
        Serial . println ("Stop6") ;
        delay(220);
//        brake(3000);
//        forward(10);
        brake(3000);
        Servo1.write(60);//a
        delay(2000);

        Servo2.write(45); //h vang
         delay(1000);
        
         Servo1.write(7);//arm up
       
         forward(10);

      }
    }

  }
  else{
      forward(10);
    }

  if (count == 14) {
    Serial . println ("Stop Working") ;
    coast(3000);

  }

  if (enable_ultrasonic_sensor == true) {
     coast(3000);
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    const unsigned long duration = pulseIn(ECHO_PIN, HIGH);

    int distance = duration / 29 / 2;
    Serial.println(distance);
    if (distance <= 3) {
       delay(3000);
      Servo1.write(146.9); ////147.9 down
      delay(2000);
          
        Servo2.write(170); // put
        delay(1000);
      
      Servo1.write(7);/// up
   //   delay(2000);
      
      forward(10);
      enable_ultrasonic_sensor = false;
    }

  }

}

/************Define high-level H-bridge commands*************/

void enableMotors()
{
  motorAOn();
  motorBOn();
}

void disableMotors()
{
  motorAOff();
  motorBOff();
}

void forward(int time)
{
  Serial.println("F");
  motorAForward();
  motorBForward();
  delay(time);
}

void backward(int time)
{
  motorABackward();
  motorBBackward();
  delay(time);
}

void turnLeft(int time)
{
  motorABackward();
  motorBForward();
  delay(time);
}

void turnRight(int time)
{
  motorAForward();
  motorBBackward();
  delay(time);
}

void coast(int time)
{
  motorACoast();
  motorBCoast();
  delay(time);
}

void brake(int time)
{
  motorABrake();
  motorBBrake();
  delay(time);
}
//Define low-level H-bridge commands

/*******enable motors***********/
void motorAOn()
{
  digitalWrite(enableA, HIGH);
  digitalWrite(enableA, HIGH);
}

void motorBOn()
{
  digitalWrite(enableB, HIGH);
}

/****************disable motors*****************/
void motorAOff()
{
  digitalWrite(enableB, LOW);
}

void motorBOff()
{
  digitalWrite(enableA, LOW);
}

/*******************motor A controls*******************/
void motorAForward()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
}

void motorABackward()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
}

/*****************motor B controls*******************/
void motorBForward()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
}

void motorBBackward()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
}


/*************coasting and braking wheels**********/
void motorACoast()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, LOW);
}

void motorABrake()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
}

void motorBCoast()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, LOW);
}

void motorBBrake()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
}
