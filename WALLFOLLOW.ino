#include <Wire.h>
#include <VL53L0X.h>
#include <VL6180X.h>
//MOTOR DRIVER
#define ENA PB1
#define PHA PB10
#define ENB PA7
#define PHB PB0
#define MODE PA6

//#define leftOut1 PB12   //interrupt pins of motors 
#define leftOut PB13          
#define rightOut PB14
//#define rightOut2 PB11 //pb11

#define led PC13 

void motorDiver()
{   
  pinMode(ENB, OUTPUT);
  pinMode(PHA, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(PHB, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);
}

void motorInterrupt()
{
    pinMode(leftOut, INPUT);
    pinMode(rightOut, INPUT);
}

//#include "piccolaVariables.h"
int leftBase =220;
int rightBase = 220;
int leftPwm;
int rightPwm;

unsigned long leftEncoder = 0;
unsigned long rightEncoder = 0;
unsigned long encoderLeftCount = 0;
unsigned long encoderRightCount = 0;

int dif = 0;

float tof[5];
int wallAvailable[3];
int cellWalls[3];

int rightWall  = 1;
int leftWall = 1;

float leftP = 0.2;
float leftD = 0.685;

float leftError = 0;
float leftLastError = 0;

float rightP = 0.2;
float rightD = 0.685;

float rightError = 0;
float rightLastError = 0;

float wallP = 0.2;
float wallD = 1.6;

float wallError = 0;
float wallLastError = 0;

float correction;

char nextMove = 'F';
//char R1;
unsigned long time;


boolean left,right,front;
int cell =0;
boolean  L = true;
boolean  R= true;
boolean  F=   false; 

//#include "piccolaTof.h"

#define GPIO1 PA0  
#define GPIO2 PA1 
#define GPIO3 PA6
#define GPIO4 PA5

#define Sensor1_newAddress 44
#define Sensor3_newAddress 45
#define Sensor2_newAddress 46
#define tofAddress1 47
#define tofAddress2 43


VL53L0X Sensor1;
VL53L0X Sensor2;
VL53L0X Sensor3;
VL6180X tof1;
VL6180X tof2;


void tofSetup()
{
  pinMode(GPIO1, OUTPUT);
   pinMode(GPIO2, OUTPUT);
    pinMode(GPIO3, OUTPUT);
    pinMode(GPIO4, OUTPUT);
    
  Wire.begin();
  
   Sensor1.setAddress(Sensor1_newAddress);
  pinMode(GPIO1, INPUT);
  delay(10);
  Sensor1.init();
   Sensor1.setTimeout(50);
  Sensor1.startContinuous();
  tof[3]=Sensor1.readRangeContinuousMillimeters();
  //Serial2.print(tof[3]);
  //Serial2.print("  ");
  
  Sensor2.setAddress(Sensor2_newAddress);
  pinMode(GPIO2, INPUT);
  delay(10);
  Sensor2.init();
   Sensor2.setTimeout(50);
  Sensor2.startContinuous();
  tof[2]=Sensor2.readRangeContinuousMillimeters();
 // Serial2.print(tof[4]);
 // Serial2.print("  ");
  
Sensor3.setAddress(Sensor3_newAddress);
  //pinMode(GPIO1, INPUT);
  delay(10);
  Sensor3.init();
   Sensor3.setTimeout(50);
  Sensor3.startContinuous();
  tof[1]=Sensor3.readRangeContinuousMillimeters();
//  Serial2.print(tof[5]);
 // Serial2.print("  ");
  
    digitalWrite(GPIO3, HIGH);
    delay(10);
    tof1.init();
    tof1.configureDefault();
    tof1.setTimeout(10);
    tof1.setAddress(tofAddress1);
    tof[4] = tof1.readRangeSingleMillimeters();
    delay(50);
   // Serial2.print(tof[1]);
  //  Serial2.print("range : ");
   // Serial2.print(tof[1]);
    //Serial2.print("  ");

    digitalWrite(GPIO4, HIGH);
    delay(10);
    tof2.init();
    tof2.configureDefault();
    tof2.setTimeout(10);
    tof2.setAddress(tofAddress2);
    tof[0] = tof2.readRangeSingleMillimeters();
    delay(50);
   // Serial2.print(tof[1]);
    //Serial2.print("range2 : ");
   // Serial2.print(tof[2]);
  //  Serial2.println(' ');
}
void tofPid()
{
  tof[2]=Sensor2.readRangeContinuousMillimeters();
   tof[4] = tof1.readRangeSingleMillimeters();
    tof[0] = tof2.readRangeSingleMillimeters();
   /*     Serial2.print(tof[0]);
    Serial2.print("  ");
    Serial2.print(tof[2]);
    Serial2.print("  ");
    Serial2.println(tof[4]);*/
}

void tofCell()
{
  tof[3]=Sensor1.readRangeContinuousMillimeters();
  tof[2]=Sensor2.readRangeContinuousMillimeters();
  tof[1]=Sensor3.readRangeContinuousMillimeters();
  /*  Serial2.print(tof[1]);
    Serial2.print("  ");
    Serial2.print(tof[2]);
    Serial2.print("  ");
    Serial2.println(tof[3]);*/
}
void printTof()
{
    
    Serial2.print(tof[0]);
    Serial2.print(",  ");
    
    Serial2.print(tof[1]);
    Serial2.print(",  ");
    Serial2.print(tof[2]);
    Serial2.print(",  ");
    Serial2.print(tof[3]);
    Serial2.print(",  ");
    
    Serial2.print(tof[4]);
    Serial2.println();
    
}
void checkWallsPid()
{
    if (tof[2] > 170)
    {
        wallAvailable[1] =  0;
    }
    else
    {
        wallAvailable[1] =  1;
    } 

    if (tof[0] <= 150)
    {
        wallAvailable[0] = 1;
    }
    else
    {
        wallAvailable[0] = 0; 
    }

    if (tof[4] <= 150)
    {
        wallAvailable[2] = 1;
    }
    else
    {
        wallAvailable[2] = 0; 
    }
}
void checkWallsCell()
{
    if (tof[2] > 250)
    {
        cellWalls[1] =  0;
    }
    else
    {
        cellWalls[1] =  1;
    } 

    if (tof[1] <= 250)
    {
        cellWalls[0] = 1;
    }
    else
    {
        cellWalls[0] = 0; 
    }

    if (tof[3] <= 250)
    {
        cellWalls[2] = 1;
    }
    else
    {
        cellWalls[2] = 0; 
    }
}


//#include "piccolaMotors.h"
void stbyHigh()
{
    digitalWrite(MODE, HIGH);
}

void stbyLow()
{
    digitalWrite(MODE, LOW);
}

void leftForward()
{
  digitalWrite(PHB, LOW);
}

void leftReverse()
{
  digitalWrite(PHB, HIGH);
}

void leftBrake()
{
    analogWrite(ENB, 0);
}

void leftForwardBase()
{
    stbyHigh();
    leftForward();
    analogWrite(ENB, leftBase);
}

void leftReverseBase()
{
    stbyHigh();
    leftReverse();
    analogWrite(ENB, leftBase);
}

void rightForward()
{
  digitalWrite(PHA, HIGH);
}

void rightReverse()
{
  digitalWrite(PHA, LOW);
}

void rightBrake()
{
  analogWrite(ENA, 0);
}

void rightForwardBase()
{
    stbyHigh();
    rightForward();
    analogWrite(ENA, rightBase);
}

void rightReverseBase()
{
    stbyHigh();
    rightReverse();
    analogWrite(ENA, rightBase);
}

void writePwm()
{
    analogWrite(ENB, leftPwm);
    analogWrite(ENA, rightPwm);
}

void writeBasePwm()
{
    analogWrite(ENB, leftBase);
    analogWrite(ENA, rightBase);
}

void forward()
{
    stbyHigh();
    leftForward();
    rightForward();
    writePwm();
}

void reverse()
{
    stbyHigh();
    leftReverse();
    rightReverse();
    writePwm();
}

void brake()
{
    stbyHigh();
    leftBrake();
    rightBrake();
    delay(100);
}

void forwardBase()
{
    stbyHigh();
    leftForward();
    rightForward();
    writeBasePwm();
}

void reverseBase()
{
    stbyHigh();
    leftReverse();
    rightReverse();
    writeBasePwm();
}

void turnRight()
{
    stbyHigh();
    leftForward();
    rightReverse();
    writeBasePwm();
}

void turnLeft()
{
    stbyHigh(); 
    leftReverse();
    rightForward();
    writeBasePwm();
}
void countLeftOut1()
{
    leftEncoder = leftEncoder + 1;  
     
}

void countRightOut1()
{
    rightEncoder = rightEncoder + 1;
}
void wallFollow()
{
  tofPid();
  
   checkWallsPid();
    if (wallAvailable[0] == 1 && wallAvailable[2] == 1)
    {
        wallPid();
       forward();
    }

    else if (wallAvailable[0] == 0 && wallAvailable[2] == 1)
    {
        rightPid();
       // brake();
        forward();
    }

    else if (wallAvailable[0] == 1 && wallAvailable[2] == 0)
    {
        leftPid();
       // brake();
        forward();
    }
    else if(wallAvailable[0] == 0 && wallAvailable[2] == 0)
    {
        
      //  brake();
        forwardBase();
    }
}  
void wallPid()
{
    wallError = (tof[4] - (tof[0]));
    rightLastError = 60 - tof[4];
    leftLastError = 60 - tof[0];
    correction = (wallError * wallP) + ((wallError - wallLastError) * wallD);
    wallLastError = wallError;
    if (correction > 20 )
    {
        correction = 0;
    }

    else if (correction < -20)
    {
        correction = 0;
    }
    leftPwm = leftBase + correction;
    rightPwm = rightBase - correction;

}
void rightPid()
{
    rightError = 75 - tof[4];
   
    correction  = (rightError * rightP) + ((rightError - rightLastError) * rightD);
    rightLastError = rightError;
   
    if (correction > 20 )
    {
        correction = 0;
    }

    else if (correction < -20)
    {
        correction = 0;
    }
    leftPwm = leftBase - correction;
    rightPwm = rightBase + correction;

}
void leftPid()
{
    leftError =75 - tof[0];
    //wallLastError = 0 - (leftError * 2);
    correction = (leftError * leftP) + ((leftError - leftLastError) * leftD);
    leftLastError = leftError;
    if (correction > 20 )
    {
        correction = 0;
    }

    else if (correction < -20)
    {
        correction = 0;
    }
    leftPwm = leftBase + correction;
    rightPwm = rightBase - correction;
}
void cellBrake()
{
  
        tof[2] = Sensor2.readRangeContinuousMillimeters();

   while(tof[2]>=50)
    {   
        wallFollow();
    }
    brake();
    encoderLeftCount = leftEncoder;
    encoderRightCount = rightEncoder;
}


void RcellBrake()
{if(tof[4]>120){
  encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
  encoderRightCount = encoderRightCount + 500;
    encoderLeftCount = encoderLeftCount + 500;

       while (rightEncoder <= encoderRightCount && leftEncoder <= encoderLeftCount)
      {
        wallFollow();
        if(tof[4]<200)
        break;
      }
 // return;
    }
    else{
    
       tof[4] = tof1.readRangeSingleMillimeters();
        //tof[2] = tof3.readRangeSingleMillimeters();
   while(tof[4]<150)
    {    
        wallFollow();
    }
    brake();
    }
    checkWallsCell();   
    if(cellWalls[1] == 0)
    { encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount = encoderRightCount + 600;
    encoderLeftCount = encoderLeftCount + 600;

       while (rightEncoder <= encoderRightCount )
      {
        wallFollow();
      }
    }
    else 
    { tof[2] = Sensor2.readRangeContinuousMillimeters();
      while(tof[2]>=60)
    {    
        wallFollow();
    }
      
      }
    brake();
    
}
void LcellBrake()
{
  if(tof[0]>150){
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;

  encoderRightCount = encoderRightCount + 500;
    encoderLeftCount = encoderLeftCount + 500;

       while (rightEncoder <= encoderRightCount && leftEncoder <= encoderLeftCount)
      {
        wallFollow();
        if(tof[0]<150)
        break;
      }
  //return;
  }
  else{
        tof[0] = tof2.readRangeSingleMillimeters();

   while(tof[0]<150)
    {
        wallFollow();
    }
    brake();
  }
    checkWallsCell();
    if(cellWalls[1] == 0)
    {
     encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount = encoderRightCount + 600;
    encoderLeftCount = encoderLeftCount + 600;

      while (rightEncoder <= encoderRightCount && leftEncoder <= encoderLeftCount)
      {
     
          wallFollow();
      }
    }
    
    else
    { tof[2] =Sensor2.readRangeContinuousMillimeters();
      while(tof[2]>=60)
      {   
        wallFollow();
       }

    }
     brake();
    
}
void rightAboutTurn()
{
    
    rightBase=210;
    leftBase=210;
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount=  310;
    encoderLeftCount=  310;
    while(rightEncoder <= encoderRightCount)
    {
        turnRight();
    }

    brake();
    leftBase = 210;
    rightBase = 210;
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
}
void leftAboutTurn()
{

    rightBase=210;
    leftBase=210;
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount= encoderRightCount + 310;
    encoderLeftCount= encoderLeftCount + 310;
    while(rightEncoder <= encoderRightCount)
    {
        turnLeft();
    }
    

    brake();
    leftBase = 210;
    rightBase = 210;
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
}
void turnBack(){
    rightBase=210;
    leftBase=210;
    
    rightBase = 210;
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount= encoderRightCount + 620;
    encoderLeftCount= encoderLeftCount + 620;
    while(rightEncoder <= encoderRightCount)
    {
        turnRight();
    }

    brake();
    
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;

}
void cellStart()
{
    /*encoderRightCount = encoderRightCount + 300;
    encoderLeftCount = encoderLeftCount + 300;
    rightBase=70;
    leftBase=70;
    while (rightEncoder <= encoderRightCount || leftEncoder <= encoderLeftCount)
    {
        dif = leftEncoder - encoderLeftCount + 300;
        rightBase = int(70+110/(1+pow(2.73,((150-dif)*0.05))));
        leftBase = int(70+110/(1+pow(2.73,((150-dif)*0.05))));
        forwardBase();
    }
    rightBase=210;
    leftBase=180;*/
    encoderRightCount= encoderRightCount + 120;
    encoderLeftCount= encoderLeftCount + 120;
    while (rightEncoder <= encoderRightCount && leftEncoder <= encoderLeftCount)
    {
       // tofPid();
        wallFollow();
    }
    encoderLeftCount = leftEncoder;
    encoderRightCount = rightEncoder;
    brake();
    delay(100);
}
void RcellStart()
{
   
     tof[4] = tof1.readRangeSingleMillimeters();
        //tof[2] = tof3.readRangeSingleMillimeters();
   while(tof[4]>150)
    {    
        wallFollow();
    }
    /*encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount = encoderRightCount + 100;
    encoderLeftCount = encoderLeftCount + 100;

       while (rightEncoder <= encoderRightCount && leftEncoder <= encoderLeftCount)
      {
        wallFollow();
      }*/
    brake();
    delay(100);
}
void LcellStart()
{
   
     tof[0] = tof2.readRangeSingleMillimeters();
        //tof[2] = tof3.readRangeSingleMillimeters();
   while(tof[0]>100)
    {    
        wallFollow();
    }
  /*  encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount = encoderRightCount + 100;
    encoderLeftCount = encoderLeftCount + 100;

       while (rightEncoder <= encoderRightCount && leftEncoder <= encoderLeftCount)
      {
        wallFollow();
      }*/
    brake();
    delay(100);
}
void cellForward()
{Serial2.println('F');
leftEncoder = 0;
rightEncoder =0;
    encoderLeftCount =  50;
    encoderRightCount =  50;
    while (leftEncoder <= encoderLeftCount && rightEncoder <= encoderRightCount)
    {
       // tofCell();
        wallFollow();
        //forwardBase();
    }
    encoderLeftCount = leftEncoder;
    encoderRightCount = rightEncoder;
}

/*void rightTurn()
{
  cellBrake();
  rightAboutTurn();
  cellStart();
}*/
void rightTurn()
{
  RcellBrake();
  rightAboutTurn();
  RcellStart();
}
/*void leftTurn(){
  cellBrake();
  leftAboutTurn();
  cellStart();
}*/
void leftTurn(){
  LcellBrake();
  leftAboutTurn();
  LcellStart();
}
void cellBack()
{
    cellBrake();
    turnBack();
    cellStart();
}
void mazeSolve()
{
    tofCell();
    checkWallsCell();
    
    if (cellWalls[2] == 0 )
    {   

        nextMove = 'R';

    }

    else if (cellWalls[1] == 0)
    {
        nextMove = 'F';
      
    }

    else if (cellWalls[0] == 0)
    {

        nextMove = 'L';
      
    }
    else if (cellWalls[0] == 1)
    {
       nextMove = 'B';
    
    }

    switch (nextMove)
    {
    case 'F' :      //move forward
        cellForward();
        break;
  
        break;
    case 'R' :      //move right
        Serial2.println('R');
        // brake();
        rightTurn();
        break;

    case 'L' :      //move left
        Serial2.println('L');
       // brake();
        leftTurn();
        break;
    
    
    case 'B' :      //move back
        Serial2.println('B');
    //    brake();
     cellBack();
        break;
    }
    
}

void setup()
{
    tofSetup();
    motorDiver();
    motorInterrupt();
    pinMode(led, OUTPUT);
  //  attachInterrupt(digitalPinToInterrupt(PB12), countLeftOut1, RISING);
    attachInterrupt(digitalPinToInterrupt(PB13), countLeftOut1, RISING);
    attachInterrupt(digitalPinToInterrupt(PB14), countRightOut1, RISING);
   // attachInterrupt(digitalPinToInterrupt(PB15), countRightOut1, RISING);
    Serial2.begin(9600);
    Serial2.print("READY");
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500); 
    digitalWrite(led, HIGH);
    delay(500); 
     if(tof[1]==65535 || tof[2]==65535 || tof[3]==65535 ) {
      while (1){
        digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW
  delay(500); 
       Serial2.print("ERROR");
      }
    }
}

void loop()
{/*Serial2.print("READY");

    digitalWrite(led, LOW);
    digitalWrite(led, HIGH);
    */delay(1000);
    while(1)
    {//rightAboutTurn();
     //delay(100);
      //wallFollow();
     mazeSolve();
    // tofPid();
     //tofCell();   
   //printTof();

    }
}
