
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
