//////////////////////////////////////////////////////////////////////////////////////
// INTEGRATION LAB-05:  Lab05_Color_SensorTest                                      //
//                                                                                  //
// This program tests the functionality of the left and righ color sensors.  The    //
// program will output to the serial monitor the color sensed by the color sensors. //
// The colors that the program will detect are Black, White, Red, Green, and Blue.  //
// If the test fails, then the color sensors must be recalibrated.                  //
//////////////////////////////////////////////////////////////////////////////////////

// TCS230 or TCS3200 pins wiring to Arduino
// RIGHT COLOR SENSOR
#define RSOut 4
#define RS0   3 
#define RS1   2 
#define RS2   1 
#define RS3   0
// LEFT COLOR SENSOR
#define MSOut 14
#define MS0   15
#define MS1   16
#define MS2   17
#define MS3   18
// MIDDLE COLOR SENSOR
#define LSOut 19
#define LS0   20
#define LS1   21
#define LS2   22
#define LS3   23

// Define the minimum and maximum analog values for each color based on the calibration test

int LredMin   =  81;     int RredMin   =  90;     int MredMin   =  83;
int LredMax   =  528;    int RredMax   =  732;     int MredMax   =  584;
int LgreenMin =  79;     int RgreenMin =  89;     int MgreenMin =  80;
int LgreenMax =  560;    int RgreenMax =  805;     int MgreenMax =  628;
int LblueMin  =  68;     int RblueMin  =  73;      int MblueMin  =  72;
int LblueMax  =  499;    int RblueMax  =  680;     int MblueMax  =  579;

// Stores frequency read by the photodiodes of the color sensors
int RredFreq    =  0;
int RgreenFreq  =  0;
int RblueFreq   =  0;
int LredFreq    =  0;
int LgreenFreq  =  0;
int LblueFreq   =  0;
int MredFreq    =  0;
int MgreenFreq  =  0;
int MblueFreq   =  0;

// Stores the red. green and blue color values for the right and left sensors
int RredColor   =  0;
int RgreenColor =  0;
int RblueColor  =  0;
int LredColor   =  0;
int LgreenColor =  0;
int LblueColor  =  0;
int MredColor   =  0;
int MgreenColor =  0;
int MblueColor  =  0;

// 0 == Black, 1 == Red, 2 == Blue, 3 == Green, 4 == White, 5 == Other
extern int Rcolor;
extern int Mcolor;
extern int Lcolor;

void Color_Sensor_setup() 
{
  // Setting the outputs of the Teensy so the Teensy can send control information
  // to the color sensors
  pinMode(RS0, OUTPUT);
  pinMode(RS1, OUTPUT);
  pinMode(RS2, OUTPUT);
  pinMode(RS3, OUTPUT);
  pinMode(LS0, OUTPUT);
  pinMode(LS1, OUTPUT);
  pinMode(LS2, OUTPUT);
  pinMode(LS3, OUTPUT);
  pinMode(MS0, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  
  // Setting the sensorOut of the color sensors as an input to the Teensy
  pinMode(RSOut, INPUT);
  pinMode(LSOut, INPUT);
  pinMode(MSOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(RS0,HIGH);
  digitalWrite(RS1,LOW);
  digitalWrite(LS0,HIGH);
  digitalWrite(LS1,LOW);
  digitalWrite(MS0,HIGH);
  digitalWrite(MS1,LOW);
  
  // Setting serial communication baud rate
}

void ColorSensor() 
{
    ///////////////////// FOR RIGHT COLOR SENSOR /////////////////////////////
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(RS2,LOW);
  digitalWrite(RS3,LOW);
  // Reading the output frequency
  RredFreq = pulseIn(RSOut,LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  RredColor = map(RredFreq, RredMin, RredMax, 255, 0);
  delay(10);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(RS2,HIGH);
  digitalWrite(RS3,HIGH);
  // Reading the output frequency
  RgreenFreq = pulseIn(RSOut,LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  RgreenColor = map(RgreenFreq, RgreenMin, RgreenMax, 255, 0); 
  delay(10);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(RS2,LOW);
  digitalWrite(RS3,HIGH);
  // Reading the output frequency
  RblueFreq = pulseIn(RSOut,LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  RblueColor = map(RblueFreq, RblueMin, RblueMax, 255, 0);
  delay(10);

  // Checks the current detected color and prints it to the serial monitor
  // 0 == Black, 1 == Red, 2 == Blue, 3 == Green, 4 == White, 5 == Other
  if (RredColor<130 && RgreenColor<130 && RblueColor<130) // Black
  {
    Rcolor = 0;
  } else if (RredColor>250 && RgreenColor>250 && RblueColor>250) // White
  {
    Rcolor = 4;
  } else if (RredColor>RgreenColor && RredColor>RblueColor) // Red
  {  
    Rcolor = 1;
  } else if (RgreenColor>(RredColor) && RgreenColor>RblueColor) // Green
  {
    Rcolor = 3;
  } else if (RblueColor>(RgreenColor) && RblueColor>RredColor) // Blue
  {
    Rcolor = 2;
  } else
  {
    Rcolor = 5;
  }
  /////////////////////////////////////////////////////////////////////////

  ///////////////////// FOR LEFT COLOR SENSOR /////////////////////////////
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(LS2,LOW);
  digitalWrite(LS3,LOW);
  // Reading the output frequency
  LredFreq = pulseIn(LSOut,LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  LredColor = map(LredFreq, LredMin, LredMax, 255, 0);
  delay(10);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(LS2,HIGH);
  digitalWrite(LS3,HIGH);
  // Reading the output frequency
  LgreenFreq = pulseIn(LSOut,LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  LgreenColor = map(LgreenFreq, LgreenMin, LgreenMax, 255, 0);
  delay(10);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(LS2,LOW);
  digitalWrite(LS3,HIGH);
  // Reading the output frequency
  LblueFreq = pulseIn(LSOut,LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  LblueColor = map(LblueFreq, LblueMin, LblueMax, 255, 0);
  delay(10);

  // Checks the current detected color and prints it to the serial monitor
  // 0 == Black, 1 == Red, 2 == Blue, 3 == Green, 4 == White, 5 == Other
  if (LredColor<100 && LgreenColor<100 && LblueColor<100) // Black
  {
    Lcolor = 0;
  } else if (LredColor>200 && LgreenColor>200 && LblueColor>200) // White
  {
    Lcolor = 4;
  } else if (LredColor>LgreenColor && LredColor>LblueColor) // Red
  {   
    Lcolor = 1;
  } else if (LgreenColor>LredColor && LgreenColor>LblueColor) // Green
  {
    Lcolor = 3;
  } else if (LblueColor>LgreenColor && LblueColor>LredColor) // Blue
  {
    Lcolor = 2;
  } else // Other Color
  {
    Lcolor = 5;
  }
  ////////////////////////////////////////////////////////////////////////////

   ///////////////////// FOR MIDDLE COLOR SENSOR /////////////////////////////
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(MS2,LOW);
  digitalWrite(MS3,LOW);
  // Reading the output frequency
  MredFreq = pulseIn(MSOut,LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  MredColor = map(MredFreq, MredMin, MredMax, 255, 0);
  delay(10);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(MS2,HIGH);
  digitalWrite(MS3,HIGH);
  // Reading the output frequency
  MgreenFreq = pulseIn(LSOut,LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  MgreenColor = map(MgreenFreq, MgreenMin, MgreenMax, 255, 0);
  delay(10);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(MS2,LOW);
  digitalWrite(MS3,HIGH);
  // Reading the output frequency
  MblueFreq = pulseIn(LSOut,LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  MblueColor = map(MblueFreq, MblueMin, MblueMax, 255, 0);
  delay(10);

  // Checks the current detected color and prints it to the serial monitor
  // 0 == Black, 1 == Red, 2 == Blue, 3 == Green, 4 == White, 5 == Other
  if (MredColor<100 && MgreenColor<100 && MblueColor<100) // Black
  {
    Mcolor = 0;
  } else if (MredColor>200 && MgreenColor>200 && MblueColor>200) // White
  {
    Mcolor = 4;
  } else if (MredColor>MgreenColor && MredColor>MblueColor) // Red
  {
    Mcolor = 1;    
  } else if (MgreenColor>(MredColor) && MgreenColor>MblueColor) // Green
  {
    Mcolor = 3;
  } else if (MblueColor>MgreenColor && ((MblueColor)>MredColor)) // Blue
  {
    Mcolor = 2;
  } else // Other Color
  {
    Mcolor = 5;
  }

  /////////////////////////////////////////////////////////////////////////
}