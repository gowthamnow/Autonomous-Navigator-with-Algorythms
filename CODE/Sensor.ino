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
