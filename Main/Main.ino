/*
*
* Kevin Granillo, Ivy Newman, Trin Whitehat, Nolan Leist
* June 7, 2025
*
* This program can perform two different tasks depending on the one chosen
*
* Pick-up Place and Return starts by grabbing a box, reading the size and color
* finding the corresponding path and placing it on a platform at the end. 
* The system then return to where it started
*
* Obstacle avoidance finds gaps in the walls without violating the white boundaries
* of the area of operation. It stops once it reaches the green line at the end.
*
*
*
*/

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* BEGIN Includes */

#include <Servo.h> // Servo library

/* END Includes */

/* Private define ------------------------------------------------------------*/
/* BEGIN PD */

#define gripperButton 25 // Gripper Button

// Ultrasonic Sensor
#define Trig 10
#define Echo 11

/* END PD */

/* Private Variables ---------------------------------------------------------*/
/* BEGIN PV */

// Color Sensor Variables
int Lcolor;
int Rcolor;
int Mcolor;

// Holds the box color and box size
int BoxColor;
int gSize;

Servo Gripper; // create servo object to control a servo
int actualPosition = 180; // Begins with the gripper open
int PWMSignal;
int distance = 0;
int duration = 0;
int val1;

int Counter = 0;
int GreenCount = 0;

/* END PV */

enum State_e{Start,InSearch,LineFollow,Place,End,StopProgram}; // Defines state machine of pickup place and return
enum State_e gState = Start; // Default state is set to Start

enum gripperState{Pickup,Grab,Line}; // Defines state machine of gripper 
enum gripperState gripperState = Pickup; // Default state is set to pickup

void setup() {
  // Sets up all the sensors 
  Color_Sensor_setup();
  GripperColorSetup();
  MovementSetup();
  //ObstacleSetup();
  Gripper.attach(24); // attaches the servo on pin 24 to the servo object
  pinMode(gripperButton, INPUT_PULLUP); // Sets button to pullup
  pinMode(Trig, OUTPUT); 
  pinMode(Echo, INPUT);
  delay(5000); // Allows for sensors to properly start
}

void loop() {
  switch(gState){ // State Machine
  
    case Start:
      Ultrasonic(); // Reads ultrasonic sensor
      delay(10);
      switch(gripperState)
      {
        case Pickup:
          MovFWD(35); // Begins moving towards the pickup platform
          // safe position - middle of range of motion 0-300 degrees
          actualPosition = 150; // gripper begins open
          // mapping actual position for PWM signals
          val1 = map(actualPosition, 0, 300, 0, 180); // scale it to use it with the servo (value between 0 and 180)
          Gripper.write(val1); // sets the servo position according to the scaled value
          delay(100); // waits for the servo to get there
          if(distance < 10) // When the system is close to the platform close gripper until button is pressed
          {
            Stop(); // Stop moving
            gripperState = Grab; // Grab box
            actualPosition = 170;
            // mapping actual position for PWM signals
            val1 = map(actualPosition, 0, 300, 0, 180); // scale it to use it with the servo (value between 0 and 180)
            Gripper.write(val1); // sets the servo position according to the scaled value
            delay(100); // waits for the servo to get there
          }
        break;

        case Grab:
          if(digitalRead(gripperButton) == HIGH){ // If button is not pressed
          // safe position - middle of range of motion 0-300 degrees
          actualPosition -= 2; // Begin closing gripper 
          // mapping actual position for PWM signals
          val1 = map(actualPosition, 0, 300, 0, 180); // scale it to use it with the
          Gripper.write(val1); // sets the servo position according to the scaled value
          delay(100); // waits for the servo to get there
          if(digitalRead(gripperButton) == LOW) // If button is pressed
          {
            actualPosition -= 4;
          }
          } else {
            if(actualPosition < 122) // Determines size of box based on gripper position
            {
              gSize = 0; // Small Box
            }
            else {
              gSize = 1; // Big Box
            }
            delay(500);
            GripperColorSensor(); // Reads the color of the box
            gripperState = Line; // Begins looking for green line
          }
          if(actualPosition < 110)
          {
            actualPosition = 150;
            val1 = map(actualPosition, 0, 300, 0, 180); // scale it to use it with the
            Gripper.write(val1); // sets the servo position according to the scaled value
            delay(100); // waits for the servo to get there
          }
        break;

        case Line:
          if(Lcolor == 3 || Mcolor == 3 || Rcolor == 3) // If green is detected
          {
            if(BoxColor == 1) // If box is red rotate right
            {
              MovFWD(35); // Move forward to align center of rotation
              delay(500);
              RotateRt(35);
              delay(1000);
              Stop();
              gState = InSearch; // Begin searching for box color line
            }
            else if(BoxColor == 2) // If box is blue rotate left
            {
              MovFWD(35); // Move forward to align center of rotation
              delay(500);
              RotateLft(35);
              delay(1000);
              Stop();
              gState = InSearch; // Begin searching for box color line
            }
          }
          else
          {
            if(Counter == 0){
              MovBKWD(30);
              delay(1000);
              Counter++;
            }
            else // Move backward
            {
              val1 = map(actualPosition, 0, 300, 0, 180); // scale it to use it with the servo (value between 0 and 180)
              Gripper.write(val1); // sets the servo position according to the scaled value
              delay(100); // waits for the servo to get there
              ColorSensor();
              MovBKWD(30);
            }
          }
        break;
      }
    break;

    case InSearch: // Searches for box color line
      ColorSensor(); // reads color sensors
      LineSearch(3);
    break;

    case LineFollow:
      Ultrasonic(); // reads ultrasonic sensor
      delay(10);
      ColorSensor(); // reads color sensors
      LineFollowing();
      if((Lcolor == 3 && Mcolor == 3) || (Mcolor == 3 && Rcolor == 3) || (Rcolor == 3 && Lcolor == 3)) // If two color sensors detect green switch to box placement
      {
        gState = Place;
      }
    break;

    case Place:
      ColorSensor(); // reads color sensors
      Ultrasonic(); // reads ultrasonic sensor
      LinePlace();
    break;

    case End:
      ColorSensor(); // reads color sensors
      LineFollowing(); // follows box color line
      if((Lcolor == 3 && Mcolor == 3) || (Mcolor == 3 && Rcolor == 3) || (Rcolor == 3 && Lcolor == 3)) // If two sensors detect green, add to green counter
      {
        GreenCount++;
      }
      if(GreenCount == 6) // This is about the amount of times green is red once it reaches the second green line
      {
        if((Lcolor == 3 && Mcolor == 3) || (Mcolor == 3 && Rcolor == 3) || (Rcolor == 3 && Lcolor == 3)) // If two sensors detect green
        {
          gState = StopProgram; // Stops the program
        }
      }
    break;

    case StopProgram:
      Stop();
    break;
  }
}

void Ultrasonic() // Function for ultrasonic sensor
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  // Read the echoPin, returns the sound wave in microseconds
  duration = pulseIn(Echo, HIGH);

  // Based on the reflection, Calculate the distance the object is from the sensor
  distance = duration * 0.034 / 2;     // Speed of sound wave divided by 2 (send & receive)
}