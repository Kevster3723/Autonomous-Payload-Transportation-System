extern int gSize;
int LineCounter = 0;
int TurnCount = 0;

void LineFollowing()
{

  if(Lcolor == BoxColor)
  {
    RotateLft(30);
    //delay(80);
  }
  else if(Mcolor == BoxColor)
  {
    MovFWD(30);
  }
  else if(Rcolor == BoxColor)
  {
    RotateRt(30);
    //delay(80);
  }
  else if(Rcolor == BoxColor && Mcolor == BoxColor)
  {
    RotateRt(30);
  }
  else if(Lcolor == BoxColor && Mcolor == BoxColor)
  {
    RotateLft(30);
  }
  else
  {
    MovFWD(30);
  }
}

void LineSearch(int Color)
{
    if(Lcolor == Color)
  {
    RotateLft(30);
    //delay(80);
  }
  else if(Mcolor == Color)
  {
    MovFWD(30);
  }
  else if(Rcolor == Color)
  {
    RotateRt(30);
    //delay(80);
  }
  else if(Rcolor == BoxColor && BoxColor == 1)
  {
    // Box Color Detected
    delay(500);
    RotateRt(35);
    delay(1100);
    gState = LineFollow;
  }
  else if(Lcolor == BoxColor && BoxColor == 2)
  {
    delay(500);
    RotateLft(35);
    delay(1100);
    gState = LineFollow;
  }
  else
  {
    MovFWD(35);
  }
}

void LinePlace()
{
  if(Lcolor == BoxColor && Mcolor == BoxColor && Rcolor == BoxColor && TurnCount == 0)
  {
    MovFWD(35);
    delay(400);
    if(gSize == 1)
    {
      RotateLft(35);
      delay(1200);
    }
    else 
    {
      RotateRt(35);
      delay(1200);
    }
    TurnCount++;
  } 
  else if(distance < 5)
  {
    Stop();
    delay(500);
    actualPosition = 170;
    val1 = map(actualPosition, 0, 300, 0, 180); // scale it to use it with the servo (value between 0 and 180)
    Gripper.write(val1); // sets the servo position according to the scaled value
    delay(100); // waits for the servo to get there
    MovBKWD(35);
    delay(500);
    RotateLft(35);
    delay(2400);
    MovFWD(35);
    delay(1200);
    if(gSize == 1)
    {
      RotateLft(35);
      delay(1100);
      MovFWD(35);
      delay(700);
      RotateRt(35);
      delay(1100);
    } 
    else 
    {
      RotateRt(35);
      delay(1100);
      MovFWD(35);
      delay(700);
      RotateLft(35);
      delay(1100);
    }
    MovFWD(35);
    delay(500);
    Stop();
    gState = End;
  }
  else
  {
    if(Lcolor == BoxColor)
    {
      RotateLft(30);
      //delay(80);
    }
    else if(Mcolor == BoxColor)
    {
      MovFWD(30);
    }
    else if(Rcolor == BoxColor)
    {
      RotateRt(30);
      //delay(80);
    }
    else
    {
      MovFWD(30);
    }
  }
}