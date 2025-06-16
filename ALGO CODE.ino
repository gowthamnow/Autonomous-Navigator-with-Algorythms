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
//#define rightOut2 PB11 

byte x=0;
byte y=0;
int enx=0;
int eny=0;  
#define led PC13 

boolean cellcenter = false;

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

int leftWallAvailable = 0;
int rightWallAvailable = 0;
int frontWallAvailable = 0;

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


//boolean left,right,front;
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
    tof1.setTimeout(50);
    tof1.setAddress(tofAddress1);
    tof[4] = tof1.readRangeSingleMillimeters();
   // delay(50);
   // Serial2.print(tof[1]);
  //  Serial2.print("range : ");
   // Serial2.print(tof[1]);
    //Serial2.print("  ");

    digitalWrite(GPIO4, HIGH);
    delay(10);
    tof2.init();
    tof2.configureDefault();
    tof2.setTimeout(50);
    tof2.setAddress(tofAddress2);
    tof[0] = tof2.readRangeSingleMillimeters();
  //  delay(50);
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
      /*  Serial2.print("tofpid");
        Serial2.print(tof[0]);
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
   /* Serial2.print(tof[1]);
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
{tofPid();
    if (tof[2] > 200)
    {
        wallAvailable[1] =  0;
    }
    else
    {
        wallAvailable[1] =  1;
    } 

    if (tof[0] <= 100)
    {
        wallAvailable[0] = 1;
    }
    else
    {
        wallAvailable[0] = 0; 
    }

    if (tof[4] <= 100)
    {
        wallAvailable[2] = 1;
    }
    else
    {
        wallAvailable[2] = 0; 
    }
}/*
void checkWallsCell()
{
    if (x == 0 && y == 0)
    {
        time = 0;
        while(time <10)
        {
            tofStart();
            if (tof[2] <= 180)
            {
            frontWallAvailable = frontWallAvailable + 1;
            }
            else
            {
            frontWallAvailable = frontWallAvailable - 1;
            }
            if (tof[1] <= 150)
            {
            leftWallAvailable= leftWallAvailable + 1;
            }
            else
            {
            leftWallAvailable= leftWallAvailable - 1;
            }
            if (tof[3] <= 150)
            {
            rightWallAvailable= rightWallAvailable + 1;
            }
            else
            {
            rightWallAvailable= rightWallAvailable - 1;
            }
            time = time + 1;
        }
    }
    if (frontWallAvailable >=0 )
    {
        cellWalls[1] =  0;
        F = true;
        frontWallAvailable = 0;
    }
    else
    {
        cellWalls[1] =  1;
        F = false;
        frontWallAvailable = 0;
    } 
    if (leftWallAvailable >= 0)
    {
        cellWalls[0] = 1;
        L = true;
        leftWallAvailable = 0;
    }
    else
    {
        cellWalls[0] = 0;
        L = false;
        leftWallAvailable = 0;
    }
    if (rightWallAvailable >= 0)
    {
        cellWalls[2] = 1;
        R = true;
        rightWallAvailable = 0;
    }
    else
    {
        cellWalls[2] = 0;
        R = false;
        rightWallAvailable = 0;
    }
    
}*/
void checkWallsCell()
{if (x == 0 && y == 0)
    { cellWalls[1] =  0;
    cellWalls[0] =  1;
    cellWalls[2] =  1;
    return ;
    }
    
  tofCell();
    if (tof[2] > 220)
    {
        cellWalls[1] =  0;
        F =false;
    }
    else
    {
        cellWalls[1] =  1;
        F =true;
    } 

    if (tof[1] <= 180)
    {
        cellWalls[0] = 1;
        L=true;
    }
    else
    {
        cellWalls[0] = 0; 
        L=false;
    }

    if (tof[3] <= 180)
    {
        cellWalls[2] = 1;
        R=true;
    }
    else
    {
        cellWalls[2] = 0; 
        R=false;
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
    wallError = (tof[0] - (tof[4]));
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
    leftPwm = leftBase - correction;
    rightPwm = rightBase + correction;

}
void rightPid()
{
    rightError = 60 - tof[4];
   
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
    leftError = 60 - tof[0];
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
void ocellBrake()
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
{   // tof[4] = tof1.readRangeSingleMillimeters();
  if((x == 7 && y == 7)||(x == 8 && y == 7)||(x == 8 && y == 8)||(x == 7 && y == 8))
  {
   encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
  encoderRightCount =  600;
    encoderLeftCount =  600;

       while (rightEncoder <= encoderRightCount  )
      {
        wallFollow();
        if( tof[2]<50)
         {
        break;
        } 
       
      }
       brake();
    return;
    }
  if(wallAvailable[2] == 0){
  encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
  encoderRightCount =  300;
    encoderLeftCount =  300;

       while (rightEncoder <= encoderRightCount && wallAvailable[2] == 0 )
      {
        wallFollow();
        if(tof[4]<150 || tof[2]<70)
         {
        break;
        } 
      }
 
    }
    else{
    
       tof[4] = tof1.readRangeSingleMillimeters();
        //tof[2] = tof3.readRangeSingleMillimeters();
   while(tof[4]<150)
    {    
        wallFollow();
        if(tof[4]>150 || tof[2]<70)
         {
        break;
        } 
    }
    brake();
    }
    
    checkWallsCell();   
    if(cellWalls[1] == 0)
    { encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount = 600;
    encoderLeftCount = 600;

       while (rightEncoder <= encoderRightCount )
      {
        wallFollow();
      }
    }
    else 
    { tof[2] = Sensor2.readRangeContinuousMillimeters();
      while(tof[2]>=50)
    {    
        wallFollow();
    }
      
      }
    brake();
    
}
void LcellBrake()
{if((x == 7 && y == 7)||(x == 8 && y == 7)||(x == 8 && y == 8)||(x == 7 && y == 8))
  {
   encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
  encoderRightCount =  970;
    encoderLeftCount =  970;

       while (rightEncoder <= encoderRightCount  )
      {
        wallFollow();
       if( tof[2]<50)
         {
        break;
        } 
      }
       brake();
    return;
    }
  //tof[0] = tof2.readRangeSingleMillimeters();
  if(wallAvailable[0] == 0){
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;

  encoderRightCount = 300;
    encoderLeftCount = 300;

       while (rightEncoder <= encoderRightCount && wallAvailable[0] == 1)
      {
        wallFollow();
        if(tof[0]<150)
        {
        break;
        }
      }
  //return;
  }
  else{
        tof[0] = tof2.readRangeSingleMillimeters();

   while(tof[0]<180)
    {
        wallFollow();
    }
    brake();
  }
    //checkWallsCell();   
    if(tof[2]>=350)
    { encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount = 600;
    encoderLeftCount = 600;

       while (rightEncoder <= encoderRightCount )
      {
        wallFollow();
      }
    }
     else 
    { tof[2] = Sensor2.readRangeContinuousMillimeters();
      while(tof[2]>=50)
    {    
        wallFollow();
    }
      
      }
    brake();
    /*
  //  tof[2] = Sensor2.readRangeContinuousMillimeters();
    if(tof[2]<=300)
    {
      //tof[2] = Sensor2.readRangeContinuousMillimeters();
      while(tof[2]>60)
      {   
        wallFollow();
       }

    }
    
    else
    { 
     encoderLeftCount = 0;
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
     brake();
    */
}
void rightAboutTurn()
{
    
    rightBase=210;
    leftBase=210;
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount= encoderRightCount + 320;
    encoderLeftCount= encoderLeftCount + 320;
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
    encoderRightCount= encoderRightCount + 320;
    encoderLeftCount= encoderLeftCount + 320;
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
    
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount= encoderRightCount + 620;
    encoderLeftCount= encoderLeftCount + 620;
    while(rightEncoder <= encoderRightCount)
    {
        turnLeft();
    }

    brake();
    
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;

}
void ocellStart()
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
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderRightCount= encoderRightCount + 120;
    encoderLeftCount= encoderLeftCount + 120;
    while (rightEncoder <= encoderRightCount )
    {
       // tofPid();
        wallFollow();
    }
    encoderLeftCount = leftEncoder;
    encoderRightCount = rightEncoder;
    brake();
    //delay(100);
}
void RcellStart()
{if((x == 7 && y == 7)||(x == 8 && y == 7)||(x == 8 && y == 8)||(x == 7 && y == 8))
  {
    
    return;
  }
     tof[4] = tof1.readRangeSingleMillimeters();
        //tof[2] = tof3.readRangeSingleMillimeters();
   while(tof[4]>150)
    {    
        wallFollow();
        if( tof[2]<50)
         {
        break;
        } 
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
   //delay(100);
}

void LcellStart()
{if((x == 7 && y == 7)||(x == 8 && y == 7)||(x == 8 && y == 8)||(x == 7 && y == 8))
  {
    
    return;
  }
     tof[0] = tof2.readRangeSingleMillimeters();
        //tof[2] = tof3.readRangeSingleMillimeters();
   while(tof[0]>100)
    {    
        wallFollow();
    }
    brake();
    delay(100);
}

void cellForward()
{ if((x == 7 && y == 7)||(x == 8 && y == 7)||(x == 8 && y == 8)||(x == 7 && y == 8))
  { 
    while ((tof[0]>100&&tof[4]<100)||(tof[0]<100&&tof[4]>100))
      {
        wallFollow();
      }
    
    return;
  }  
  if(cellcenter)
    {
          leftBase = 210;
    rightBase = 210;
         rightEncoder=0;
         leftEncoder=0;
         encoderLeftCount = 500;
         encoderRightCount = 500;
    
       while (rightEncoder <= encoderRightCount )
      {
        wallFollow();
      }
      cellcenter = false;
      return;
    }
    leftBase = 210;
    rightBase = 210;
    encoderLeftCount = 0;
    encoderRightCount = 0;
    leftEncoder = 0;
    rightEncoder = 0;
    encoderLeftCount =  800;
    encoderRightCount =  800;
    while ( rightEncoder <= encoderRightCount)
    {
        //tofCell();
        wallFollow();
        //forwardBase();
    }
   //encoderLeftCount = leftEncoder;
    //encoderRightCount = rightEncoder;
}

void cellStart()
{  
         rightEncoder=0;
         leftEncoder=0;
         encoderLeftCount = 350;
         encoderRightCount = 350;
    
       while (rightEncoder <= encoderRightCount )
      {
        wallFollow();
      }
    /*  encoderLeftCount = encoderLeftCount + 150;
    encoderRightCount = encoderRightCount + 150;
    while ( rightEncoder <= encoderRightCount)
    {
        wallFollow();
        //encoderPid();
        if (tof[2] <= 180)
        {
          frontWallAvailable = frontWallAvailable + 1;
        }
        else
        {
          frontWallAvailable = frontWallAvailable - 1;
        }
        if (tof[0] <= 150)
        {
          leftWallAvailable= leftWallAvailable + 1;
        }
        else
        {
          leftWallAvailable= leftWallAvailable - 1;
        }
        if (tof[4] <= 150)
        {
          rightWallAvailable= rightWallAvailable + 1;
        }
        else
        {
          rightWallAvailable= rightWallAvailable - 1;
        }
    }*/

    brake();

}

void cellBrake()
{
rightEncoder=0;
leftEncoder=0;
encoderRightCount=300;
encoderLeftCount=300;
rightBase=100;
leftBase=100;

while (rightEncoder <= encoderRightCount )
    {wallFollow();
     /* rightBase = int(180-110/(1+pow(2.73,((300-rightEncoder)*0.012))));
      leftBase = int(180-110/(1+pow(2.73,((300-leftEncoder)*0.012))));
      
        forwardBase();
       */ 
    }
    brake();
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
  cellcenter = true;
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
  cellcenter = true;
}
void cellBack()
{
    ocellBrake();
    turnBack();
    //ocellStart();
}




#include <EEPROM.h>
//#include "piccolaZlgoVariables.h"
#include <QueueArray.h>

byte xprev=0;
byte yprev=0;
byte orient=0;
byte state=0;
boolean shortPath= false;
boolean middleSquare= true;
byte x_0;
byte y_0;
byte x_1;
byte y_1;
byte x_2;
byte y_2;
byte x_3;
byte y_3;
byte mazeSize = 16;
char dir;
char turning;
QueueArray <byte> queue;
QueueArray <byte> pathQueue;
 
byte xdes;
byte ydes; 
unsigned long timer;
int cellCount =1;


byte cells[16][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    
            };

byte flood2[16][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    
            };
            
byte flood[16][16]=
       {{14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},
       {13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
       {12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
       {11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
       {10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
       {9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
       {8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
       {7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
       {7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
       {8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
       {9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
       {10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
       {11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
       {12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
       {13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
       {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},
       };



byte xrun=0;
byte yrun=0;
//#include "piccolaZlgo.h"

void appendDestination(byte xdes,byte ydes, boolean middleSquare){
  
    if (middleSquare == true){
      for (int i=0; i<16; i++){
        for (int j=0; j<16; j++){
            flood[i][j]=254;
            //Serial2.print(flood[i][j]);
        }
       // Serial2.println();
    }

    flood[8][8]=0;
    flood[7][8]=0;
    flood[8][7]=0;
    flood[7][7]=0;

    queue.enqueue(8);
    queue.enqueue(8);
    queue.enqueue(7);
    queue.enqueue(8);
    queue.enqueue(8);
    queue.enqueue(7);
    queue.enqueue(7);
    queue.enqueue(7);
    }

    else{
    for (int i=0; i<16; i++){
        for (int j=0; j<16; j++){
            flood[i][j]=254;
        }
    }

    flood[ydes][xdes]=0;

    queue.enqueue(ydes);
    queue.enqueue(xdes);
    Serial2.println("xdes");
    Serial2.println(xdes);
    
    Serial2.println(ydes);
    
     
}
}

byte orientation(byte orient, char turning){
  if (turning== 'L'){
        orient=orient-1;
        if (orient==-1|| orient== 255)
            orient=3;
  }
    else if(turning== 'R'){
        orient=orient+1;
        if (orient==4|| orient==255)
            orient=0;
    }
    else if(turning== 'B'){
        if (orient==0)
            orient=2;
        else if (orient==1)
            orient=3;
        else if (orient==2)
            orient=0;
        else if (orient==3)
            orient=1;
    }

    return(orient);
}

byte updateCoordinates(){//byte x, byte y, byte orient){
    
    if (orient==0)
        y=y+1;
    if (orient==1)
        x=x+1;
    if (orient==2)
        y=y-1;
    if (orient==3)
        x=x-1;

    return(x,y);
}



void updateWalls(byte x, byte y, byte orient, boolean L, boolean R, boolean F){
  printTof();
  if((x == 7 && y == 7)||(x == 8 && y == 7)||(x == 8 && y == 8)||(x == 7 && y == 8)){
    return;
  }
    if(L && R && F){
        if (orient==0)
            cells[y][x]= 13;
        else if (orient==1)
            cells[y][x]= 12;
        else if (orient==2)
            cells[y][x]= 11;
        else if (orient==3)
            cells[y][x]= 14;
            //return;
    }

    else if (L && R && !F){
        if (orient==0 || orient== 2)
            cells[y][x]= 9;
        else if (orient==1 || orient==3)
            cells[y][x]= 10;
           // return;
    }

    else if (L && F && !R){
        if (orient==0)
            cells[y][x]= 8;
        else if (orient==1)
            cells[y][x]= 7;
        else if (orient==2)
            cells[y][x]= 6;
        else if (orient==3)
            cells[y][x]= 5;
           // return;
    }

    else if (R && F && !L){
        if (orient==0)
            cells[y][x]= 7;
        else if (orient==1)
            cells[y][x]= 6;
        else if (orient==2)
            cells[y][x]= 5;
        else if (orient==3)
            cells[y][x]= 8;
            //return;
    }

    else if(F){
        if (orient==0)
            cells[y][x]= 2;
        else if (orient==1)
            cells[y][x]= 3;
        else if (orient==2)
            cells[y][x]= 4;
        else if (orient==3)
            cells[y][x]= 1;
            //return;
    }

    else if(L){
        if (orient==0)
            cells[y][x]= 1;
        else if (orient==1)
            cells[y][x]= 2;
        else if (orient==2)
            cells[y][x]= 3;
        else if (orient==3)
            cells[y][x]= 4;
            //return;
    }

    else if(R){
        if (orient==0)
            cells[y][x]= 3;
        else if (orient==1)
            cells[y][x]= 4;
        else if (orient==2)
            cells[y][x]= 1;
        else if (orient==3)
            cells[y][x]= 2;
            //return;
    }

    else{
        cells[y][x]= 15;
        //return;
        
    }
   
}

boolean isAccessible(byte x, byte y, byte xNext, byte yNext){
  if (xNext==254 || yNext== 254){
    return(false);
  }
  if (x==xNext){
        if(y>yNext){
            if(cells[y][x]==4 || cells[y][x]==5 || cells[y][x]==6 || cells[y][x]==10 || cells[y][x]==11 || cells[y][x]==12 || cells[y][x]==14 || cells[yNext][xNext]==2 || cells[yNext][xNext]==7 || cells[yNext][xNext]==8 || cells[yNext][xNext]==10 || cells[yNext][xNext]==12 || cells[yNext][xNext]==13 || cells[yNext][xNext]==14 )
                return (false);
            else
                return(true);
        }
        else{
            if(cells[y][x]==2 || cells[y][x]==7 || cells[y][x]==8 || cells[y][x]==10 || cells[y][x]==12 || cells[y][x]==13 || cells[y][x]==14 || cells[yNext][xNext]==4 || cells[yNext][xNext]==5 || cells[yNext][xNext]==6 || cells[yNext][xNext]==10 || cells[yNext][xNext]==11 || cells[yNext][xNext]==12 || cells[yNext][xNext]==14 )
                return (false);
            else
                return(true);
        }
  }
    else if (y==yNext){
        if(x>xNext){
            if(cells[y][x]==1 || cells[y][x]==5 || cells[y][x]==8 || cells[y][x]==9 || cells[y][x]==11 || cells[y][x]==13 || cells[y][x]==14 || cells[yNext][xNext]==3 || cells[yNext][xNext]==6 || cells[yNext][xNext]==7 || cells[yNext][xNext]==9 || cells[yNext][xNext]==11 || cells[yNext][xNext]==12 || cells[yNext][xNext]==13 )
                return (false);
            else
                return (true);
        }
        else{
            if(cells[y][x]==3 || cells[y][x]==6 || cells[y][x]==7 || cells[y][x]==9 || cells[y][x]==11 || cells[y][x]==12 || cells[y][x]==13 || cells[yNext][xNext]==1 || cells[yNext][xNext]==5 || cells[yNext][xNext]==8 || cells[yNext][xNext]==9 || cells[yNext][xNext]==11 || cells[yNext][xNext]==13 || cells[yNext][xNext]==14 )
                return (false);
            else
                return (true);
        }


    }

}

byte getSurrounds(byte x,byte y){
    x_3= x-1;
    y_3=y;
    x_0=x;
    y_0=y+1;
    x_1=x+1;
    y_1=y;
    x_2=x;
    y_2=y-1;
    if(x_1>= mazeSize){
        x_1=254;}
    if(y_0>= mazeSize){
        y_0=254;}
    if(x_3== 255){
        x_3 =254;}
    if(y_2== 255){
        y_2=254;}
    return (x_0,y_0,x_1,y_1,x_2,y_2,x_3,y_3);  //order of cells- north,east,south,west
}



void floodFill3(){
  Serial2.println("FF3");
  //showFlood();
  
    while (!queue.isEmpty ()){
        
        yrun=queue.dequeue();
        xrun=queue.dequeue();
        /*Serial2.print("yrun");
        Serial2.println(yrun);
        
        Serial2.print("Xrun");
        Serial2.print(xrun);
         Serial2.println(' ');*/
        
        x_0,y_0,x_1,y_1,x_2,y_2,x_3,y_3 = getSurrounds(xrun,yrun);
        //Serial2.println(x_0);
        if(x_0>=0 && y_0>=0 ){
            if (flood[y_0][x_0]==254){
                if (isAccessible(xrun,yrun,x_0,y_0)){
                    flood[y_0][x_0]=flood[yrun][xrun]+1;
                    queue.enqueue(y_0);
                    queue.enqueue(x_0);
                }
            }
        }
        if(x_1>=0 and y_1>=0){
            if (flood[y_1][x_1]==254){
                if (isAccessible(xrun,yrun,x_1,y_1)){
                    flood[y_1][x_1]=flood[yrun][xrun]+1;
                    queue.enqueue(y_1);
                    queue.enqueue(x_1);
                }
            }
        }
        if(x_2>=0 and y_2>=0 ){
            if (flood[y_2][x_2]==254){
                if (isAccessible(xrun,yrun,x_2,y_2)){
                    flood[y_2][x_2]=flood[yrun][xrun]+1;
                    queue.enqueue(y_2);
                    queue.enqueue(x_2);
                }
            }
        }
        if(x_3>=0 and y_3>=0 ){
            if (flood[y_3][x_3]==254){
                if (isAccessible(xrun,yrun,x_3,y_3)){
                    flood[y_3][x_3]=flood[yrun][xrun]+1;
                    queue.enqueue(y_3);
                    queue.enqueue(x_3);
                }
            }
        }
        
    }
    //Serial2.println("FLOOD ");
    showFlood();
    Serial2.println("FF3EX");
}



char toMove(byte x,byte y,byte xprev,byte yprev,byte orient){
    
    x_0,y_0,x_1,y_1,x_2,y_2,x_3,y_3 = getSurrounds(x,y);
    
    byte val= flood[y][x];
    byte prev=254;
    byte minVals[4]={254,254,254,254};

    /*  for (int i=0; i<4;i++){
        Serial2.print("minVals");
          Serial2.print(minVals[i]);
          Serial2.print(' ');
        }
      Serial2.println(' ');
*/


    if (isAccessible(x,y,x_0,y_0)){
        if (x_0==xprev && y_0==yprev)
            prev=0;
        minVals[0]= flood[y_0][x_0];
        Serial2.println(1000);
    }
    else
      minVals[0]=254;
    
    if (isAccessible(x,y,x_1,y_1)){
        if (x_1==xprev && y_1==yprev)
            prev=1;
        minVals[1]= flood[y_1][x_1];
        Serial2.println(2000);
    }
    else
      minVals[1]=254;
      
    if (isAccessible(x,y,x_2,y_2)){
        if (x_2==xprev && y_2==yprev)
            prev=2;
        minVals[2]= flood[y_2][x_2];
        Serial2.println(3000);
    }
    else
      minVals[2]=254;
      
    if (isAccessible(x,y,x_3,y_3)){
        if (x_3==xprev && y_3==yprev)
            prev=3;
        minVals[3]= flood[y_3][x_3];
        Serial2.println(4000);
    }
    else
      minVals[3]=254;

    
   Serial2.println(prev);
    byte minVal=254;
    byte minCell=0;
    byte noMovements=0;
    
    
    for (int i=0; i<4;i++){
      Serial2.print(minVals[i]);
      Serial2.print(' ');
        if (minVals[i]!= 254){
            noMovements+=1;}
    }
    Serial2.println(' ');
    for (int i=0; i<4;i++){
        if (minVals[i]<minVal){
            if (noMovements==1){
                minVal= minVals[i];
                minCell= i;
            }
            else{
                if(i!=prev){
                    minVal= minVals[i];
                    minCell= i;
                    Serial2.print(minVals[i]);
                    Serial2.print(' ');
                    Serial2.println(minCell);
                    
                }
            }
        }
    }
 for (int i=0; i<4;i++){
        Serial2.print("minVals");
          Serial2.print(minVals[i]);
          Serial2.print(' ');
        }
      Serial2.println(' ');
    
    if (minCell==orient)
        return ('F');
    else if((minCell==orient-1) || (minCell== orient+3))
        return('L');
    else if ((minCell==orient+1) || (minCell== orient-3))
        return('R');
    else
        return('B');


}





void center(){
  if (x == 7 && y == 7){
    cells[8][7] = 8;
    cells[8][8] = 7;
    cells[7][8] = 6;
    if (orient == 0){
      cells[7][7] = 1;
    }
    else if (orient == 1){
      cells[7][7] = 4;
    }   
  }
  else if (x == 8 && y == 7){
    cells[8][8] = 7;
    cells[7][8] = 6;
    cells[7][7] = 5;
    if (orient == 1){
      cells[8][7] = 2;
    }
    else if (orient == 2){
      cells[8][7] = 1;
    }   
  }
  else if (x == 8 && y == 8){
    cells[7][8] = 6;
    cells[7][7] = 5;
    cells[8][7] = 8;
    if (orient == 2){
      cells[8][8] = 3;
    }
    else if (orient == 3){
      cells[8][8] = 2;
    }   
  }
  else if (x == 7 && y == 8){
    cells[7][7] = 5;
    cells[8][7] = 8;
    cells[7][8] = 7;
    if (orient == 0){
      cells[7][8] = 3;
    }
    else if (orient == 3){
      cells[7][8] = 4;
    }   
  }
}
//#include "piccolaZlgoSupport.h"


void showCells(){
      Serial2.println("CELLS ");

  for (int i=15; i>=0; i--){
    for (int j=0; j<16;j++){
      Serial2.print(cells[i][j]); 
      Serial2.print(' ');
    }
    Serial2.println(' ');
  }
}

void showFlood(){
  for (int i=15; i>=0; i--){
    for (int j=0; j<16;j++){
      Serial2.print(flood[i][j]); 
      Serial2.print(' ');
    }
    Serial2.println(' ');
  }
}




void traverse(byte xdes, byte ydes, boolean middleSquare){

 /* appendDestination(xdes,ydes,middleSquare);
  floodFill3();

  //tofPid();
  tofCell();
  checkWallsCell();
  updateWalls(x, y, orient, L, R, F);
  */

  appendDestination(xdes,ydes,middleSquare);
  floodFill3();   
  checkWallsCell();
  updateWalls(x, y, orient, L, R, F);
  
    
   showFlood();
    showCells();
     
      /*xprev=x;
        yprev=y;
        updateCoordinates();
*/
    
  while(flood[y][x]!=0){
  
  checkWallsCell();
  updateWalls(x, y, orient, L, R, F); 
    showCells(); 
    appendDestination(xdes,ydes,middleSquare);
    floodFill3();
    dir= toMove(x,y,xprev,yprev,orient);

    Serial2.println(dir);
    
        if (dir=='L'){
            orient = orientation(orient,'L');
            leftTurn();
           // brake();
        }

        else if (dir=='R'){
            orient = orientation(orient,'R');
            rightTurn();
            //brake();
            Serial2.println("RFinsh");
            delay(1000);
        }

        else if (dir=='B'){
            orient = orientation(orient,'B');
           // orient = orientation(orient,'L');
           cellBack();
           //brake();
        }
        else{
          if(x==0 && y==0){
            //ocellStart();
            //brake();
            delay(1000);
          }
          else{
          cellForward();
          brake();
          }
        }
        
        
        xprev=x;
        yprev=y;
        updateCoordinates();
        delay(500);
        Serial2.println("NEXT");
       // printTof();
        //delay(1000);
        

  }
    Serial2.print('x');
    
    Serial2.println(x);
    
    Serial2.print('y');
    
    Serial2.println(y);

}
void mazeSolve()
{
   // tofCell();
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
       // brake();
        break;
   /* case '>' :      //move right NO WALL IN F
       brake();
       NWrightTurn();
      */  
        break;
    case 'R' :      //move right
        // brake();
        rightTurn();
        break;

    case 'L' :      //move left
       // brake();
        leftTurn();
        break;
    
    
    case 'B' :      //move back
       // brake();
     cellBack();
        break;
    }
    
}
int mode =0;
void mazestart(){
  while(1){
    tof[2] = Sensor2.readRangeContinuousMillimeters();
    if( tof[2]<50){
      mode =1;
    break;
  }
  }

  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500); 
    digitalWrite(led, HIGH);
    delay(1000); 


    
   //  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
 // delay(500); 
   // digitalWrite(led, HIGH);
     //while(time < 10){
   //if( tof[2]<50){
     // mode =2;}
  //time = time +1;
 
  //digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  //delay(500); 
    //digitalWrite(led, HIGH);
    //delay(200);
    //digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  //delay(500); 
    //digitalWrite(led, HIGH);
 

}
 
void setup()
{
    tofSetup();
    motorDiver();
    motorInterrupt();
    //attachInterrupt(digitalPinToInterrupt(PB12), countLeftOut1, RISING);
    attachInterrupt(digitalPinToInterrupt(PB13), countLeftOut1, RISING);
    attachInterrupt(digitalPinToInterrupt(PB14), countRightOut1, RISING);
   pinMode(led, OUTPUT);
   // attachInterrupt(digitalPinToInterrupt(PB15), countRightOut1, RISING);
    Serial2.begin(9600);
    Serial2.print("READY");
    tofCell();
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


void loop(){
 mazestart();
 if (mode == 2){
  while(1){
  mazeSolve();}
 
 }
//traverse(byte xdes, byte ydes, boolean middleSquare, boolean shortPath)
traverse(0,0,true); 
cellStart();// traverses to center
//cellForward();
Serial2.println("centre");
delay(1000);
Serial2.println(' ');
enx=1;
eny=y; 
center();  //saves the walls of the middle square
showCells();

Serial2.println("CENTER");
Serial2.println(' ');
Serial2.println(' ');
/*
Serial2.println("CENTER RETURN");
traverse(0,0,false);  // traverses back to the starting square
Serial2.println(' ');
Serial2.println(' ');
showCells();*/
while(1){}

}
void loopt()
{/*Serial2.print("READY");

    digitalWrite(led, LOW);
    digitalWrite(led, HIGH);
    */delay(1000);
    while(1)
    {//cellForward();
         // brake();
      //leftAboutTurn();
      //turnBack();
      //wallFollow();
    // mazeSolve();
    tofPid();
        tofCell();
   printTof();

    }
}
void loopq(){
/*
  wallFollow();
  //delay(1000);

// Serial2.println(b);
 // cellStart();
  tofPid();
  tofCell();
  printTof();
  //while(1){}*/
}
