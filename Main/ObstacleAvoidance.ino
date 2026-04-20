// Infrared
#define LftIn 13
#define RtIn 12

unsigned int Rflag = 0;
unsigned int Lflag = 0;

unsigned int CurrDir = 0;

enum ObstacleState{Forward,Right,Left,Backward,EndOA};
enum ObstacleState gObstacle = Right;

void ObstacleSetup() {
  attachInterrupt(digitalPinToInterrupt(RtIn), RightInterrupt, LOW);
  attachInterrupt(digitalPinToInterrupt(LftIn), LeftInterrupt, LOW);
}

void ObstacleAvoidance() {
  // put your main code here, to run repeatedly:
  Ultrasonic();
  delay(10);
  switch(gObstacle)
  {
    case Forward:
    //
    ColorSensor();
    if((Lcolor == 3 && Mcolor == 3) || (Mcolor == 3 && Rcolor == 3) || (Rcolor == 3 && Lcolor == 3))
    {
      gObstacle = EndOA;
    }
    if(distance > 20)
    {
      MovFWD(35);
      Rflag = 0;
      Lflag = 0;
    }
    else if(distance < 20 && CurrDir == 0)
    {
      gObstacle = Right;
    }
    else if(distance < 20 && CurrDir == 1)
    {
      gObstacle = Left;
    }
    break;

    case Right:
      //
      Lcolor = 0;
      ColorSensor();
      StrafeRt(35);
      if(distance > 25)
      {
        delay(700);
        gObstacle = Forward;
      }
      else if(Rcolor == 4 && Lflag == 0)
      {
        //RotateLft(35);
        //delay(50);
        gObstacle = Left;
        CurrDir = 1;
        Rflag = 1;
      }
    break;

    case Left:
    //
      Rcolor = 0;
      ColorSensor();
      StrafeLft(35);
      if(distance > 25)
      {
        delay(700);
        gObstacle = Forward;
      }
      else if(Lcolor == 4 && Rflag == 0)
      {
        Lflag = 1;
        RotateLft(50);
        delay(20);
        gObstacle = Right;
        CurrDir = 0;
      }
    break;

    case Backward:
      MovBKWD(35);
      delay(400);
      Stop();
      gObstacle = Forward;
    break;

    case EndOA:
      Stop();
    break;
  }
}

void LeftInterrupt()
{
  if(gProgramSelection == 0)
  {
    MovBKWD(35);
    delay(10);
    gObstacle = Backward;
  }
  
}

void RightInterrupt()
{
  if(gProgramSelection == 0)
  {
    MovBKWD(35);
    delay(10);
    gObstacle = Backward;
  }
}
