// GRIPPER COLOR SENSOR
#define GSOut 9
#define GS0   8
#define GS1   7
#define GS2   6
#define GS3   5

// Define the minimum and maximum analog values for each color based on the calibration test

int GredMin = 47;
int GredMax = 450;
int GgreenMin = 48;
int GgreenMax = 468;
int GblueMin = 38;
int GblueMax = 357;

// Stores frequency read by the photodiodes of the color sensors
int GredFreq = 0;
int GgreenFreq = 0;
int GblueFreq = 0;

// Stores the red. green and blue color values for the right and left sensors
int GredColor = 0;
int GgreenColor = 0;
int GblueColor = 0;

extern int BoxColor;

void GripperColorSetup() 
{
  // Setting the outputs of the Teensy so the Teensy can send control information
  // to the color sensors
  pinMode(GS0, OUTPUT);
  pinMode(GS1, OUTPUT);
  pinMode(GS2, OUTPUT);
  pinMode(GS3, OUTPUT);

  // Setting the sensorOut of the color sensors as an input to the Teensy
  pinMode(GSOut, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(GS0,HIGH);
  digitalWrite(GS1,LOW);
}

void GripperColorSensor() 
{
    ///////////////////// FOR Gripper COLOR SENSOR /////////////////////////////
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(GS2,LOW);
  digitalWrite(GS3,LOW);
  // Reading the output frequency
  GredFreq = AvgColor(GSOut);
  // Remaping the value of the RED (R) frequency from 0 to 255
  GredColor = map(GredFreq, GredMin, GredMax, 255, 0);
  delay(10);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(GS2,HIGH);
  digitalWrite(GS3,HIGH);
  // Reading the output frequency
  GgreenFreq = AvgColor(GSOut);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  GgreenColor = map(GgreenFreq, GgreenMin, GgreenMax, 255, 0);
  delay(10);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(GS2,LOW);
  digitalWrite(GS3,HIGH);
  // Reading the output frequency
  GblueFreq = AvgColor(GSOut);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  GblueColor = map(GblueFreq, GblueMin, GblueMax, 255, 0);
  delay(10);

  // Checks the current detected color and prints it to the serial monitor
  // 0 == Black, 1 == Red, 2 == Blue, 3 == Green, 4 == White, 5 == Other
  if (GredColor<100 && GgreenColor<100 && GblueColor<100) // Black
  {
    BoxColor = 0;
  } else if (GredColor>200 && GgreenColor>200 && GblueColor>200) // White
  {
    BoxColor = 4;
  } else if (GredColor>GgreenColor && GredColor>GblueColor) // Red
  {
    BoxColor = 1;
  } else if (GgreenColor>(GredColor+20) && GgreenColor>GblueColor) // Green
  {
    BoxColor = 3;
  } else if (GblueColor>GgreenColor && GblueColor>GredColor) // Blue
  {
    BoxColor = 2;
  } else // Other Color
  {
    BoxColor = 5;
  }
  /////////////////////////////////////////////////////////////////////////
}