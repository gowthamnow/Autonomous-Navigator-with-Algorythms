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
