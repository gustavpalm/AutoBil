//****Includes******//
#include <Servo.h>
#include <NewPing.h> 


//****Defines and variables******//
#define MRF A0 //motor left forward
#define MRB A1 // motor left backward
#define MLB A2 // motor right forward
#define MLF A3 // motor right backward
#define TRIGGER_PIN 11 //Pin 11 for UCsensors trigger port
#define ECHO_PIN 12 // pin 12 for UCsensors Echo pin
#define MinObs 20 //minimum distance decrease speed
#define MinObsStop // minimum distance stop
#define MAX_DISTANCE 500
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;  // create servo object to control a servo
int pos = 0;  // variable to store the servo position
unsigned int distance;// distance from UCsensor
int obstacle[3];
bool left=false;// Line Follower left true is black
bool right=false;// Line Follower right true is black
bool ObsLeft=false;
bool ObsRight=false;

//****Setup******//
void setup() {
    Serial.begin(9600);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT); 
  pinMode(A4, INPUT); //left LineF
  pinMode(A5, INPUT); //Right LineF
  pinMode(8, OUTPUT);
}



void serv()
{

  
   for (pos = 10; pos <= 185; pos += 2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    UCsensor();
    delay(15);
    
    
  }
  for (pos = 185; pos >= 10; pos -= 2) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    UCsensor();
    delay(15);
     
  }
 
 }


void LineFollower()
{
  if( analogRead(A4)>200)  
    left=true;  
  else
  left=false;

  if( analogRead(A5)>200)  
    right=true;
    //Sväng bilen åt vänster. Tanken är att linjeföljarna ska befinna sig innanför linjerna och när den reagerar på en linje och håller på att köra utanför linjerna ska den då svänga in från linjerna. Samma princip ovan. Lägg till reglerteknik auch.   
  else
  right=false;
 
}

void UCsensor(){//Ultra sonic sensor 
   distance = sonar.ping_cm();
   Serial.println(distance);
}


// move forward with given speed
void Forward(int Speed)
{
  analogWrite(MLF,Speed);
  analogWrite(MRF,Speed);  
  UCsensor();
}
// move backward with given speed
void Backward(int Speed)
{
  analogWrite(MLB,Speed);
  analogWrite(MRB,Speed);
  UCsensor();
  
}
// turn left with given speed
void TurnLeft(int Speed)
{
  analogWrite(MRF,Speed);
  analogWrite(MLB,Speed);
  UCsensor();
  
}
//turn right with given speed
void TurnRight(int Speed)
{
  analogWrite(MLF,Speed);
  analogWrite(MRB,Speed);
  UCsensor(); 
 
}
void Tuta()
{
  digitalWrite(4,1);
}

void CheckRight()
{
    for (pos = 10; pos <= 185; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 
    
  }
  UCsensor();
    if(distance < 10 && distance > 1)
    ObsRight= true;
    else 
    ObsRight= false;

       
}
void CheckLeft()
{
   for ( pos = 185; pos >= 10; pos -= 2) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
     
  }
  UCsensor();
    if(distance < 10 && distance > 1)
    ObsLeft =true;
    else 
    ObsLeft =false;
}


void loop() //Mainfunktionen
{
UCsensor();
LineFollower();

  if(distance < 10 && distance > 1)// avbrott 
  {
    Backward(250);
      
  }

    else // framm[t 
  {
    Forward(255);
    if(right)
    {
      TurnLeft(100);  
    }
    if(left)
    {
      TurnRight(100);
    }
    
  }
    
  
 
                       
  

}
