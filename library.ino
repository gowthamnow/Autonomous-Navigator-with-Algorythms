#include <Wire.h>
#include <VL53L0X.h>
#include <VL6180X.h>
#include "piccolaVariables.h"
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

