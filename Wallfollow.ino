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

void countLeftOut1()
{
    leftEncoder = leftEncoder + 1;  
     
}

void countRightOut1()
{
    rightEncoder = rightEncoder + 1;
}


