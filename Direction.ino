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