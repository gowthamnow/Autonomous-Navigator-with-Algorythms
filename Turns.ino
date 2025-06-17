

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
{
    Serial2.print("READY");

    digitalWrite(led, LOW);
    digitalWrite(led, HIGH);
    delay(1000);
    while(1)
    {
     rightAboutTurn();
     delay(100);
     wallFollow();
     mazeSolve();
     tofPid();
     tofCell();   
     printTof();

    }
}