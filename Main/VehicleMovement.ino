// Rear RIGHT Motor (RRM) pin connections
#define EnableLM2 37 
#define FLM_in1   38 
#define FLM_in2   35

// Front RIGHT Motor (FRM) pin connections
#define EnableRM2 36
#define RLM_in3   34
#define RLM_in4   33

// Front LEFT Motor (FLM) pin connections
#define EnableLM1 29
#define RRM_in1   27
#define RRM_in2   30

// Rear LEFT Motor (RLM) pin connections
#define EnableRM1 28
#define FRM_in3   31
#define FRM_in4   32

void MovementSetup() {
  // put your setup code here, to run once:
  // Set all motor controller pins as outputs
	
  pinMode(EnableLM1, OUTPUT);
  pinMode(EnableRM1, OUTPUT);
  pinMode(RRM_in1, OUTPUT);
  pinMode(RRM_in2, OUTPUT);
  pinMode(FRM_in3, OUTPUT);
  pinMode(FRM_in4, OUTPUT);

  pinMode(EnableLM2, OUTPUT);
  pinMode(EnableRM2, OUTPUT);
  pinMode(FLM_in1, OUTPUT);
  pinMode(FLM_in2, OUTPUT);
  pinMode(RLM_in3, OUTPUT);
  pinMode(RLM_in4, OUTPUT);
	
  // Initial state - Turn off all the motors
	
  digitalWrite(RRM_in1, LOW);
  digitalWrite(RRM_in2, LOW);
  digitalWrite(FRM_in3, LOW);
  digitalWrite(FRM_in4, LOW);
  digitalWrite(FLM_in1, LOW);
  digitalWrite(FLM_in2, LOW);
  digitalWrite(RLM_in3, LOW);
  digitalWrite(RLM_in4, LOW);

}

void Stop() 
{
  // The PWM value is 0 for a modulation of 0%
  
  analogWrite(EnableLM1, 0);
  analogWrite(EnableRM1, 0);

  analogWrite(EnableLM2, 0);
  analogWrite(EnableRM2, 0);
  
  // Turn off all motors

  digitalWrite(RRM_in1, LOW);
  digitalWrite(RRM_in2, LOW);
  digitalWrite(FRM_in3, LOW);
  digitalWrite(FRM_in4, LOW);

  digitalWrite(FLM_in1, LOW);
  digitalWrite(FLM_in2, LOW);
  digitalWrite(RLM_in3, LOW);
  digitalWrite(RLM_in4, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// MovFWD( int speed ):  Right and Left wheels will rotate in the CW direction.
//    "speed" parameter {0 - 100} is the modulation percentage of the PWM signal.
//////////////////////////////////////////////////////////////////////////////

void MovFWD(float speed )
{
  float  PWMval = 255*(speed/100);
  // The PWMval varies between 0 and 255
  
  analogWrite(EnableLM1, PWMval);
  analogWrite(EnableRM1, PWMval);

  analogWrite(EnableLM2, PWMval);
  analogWrite(EnableRM2, PWMval);

  // Rotate Right and Left wheels clockwise (CW) 

  digitalWrite(RRM_in1, HIGH);
  digitalWrite(RRM_in2, LOW);
  digitalWrite(FRM_in3, HIGH);
  digitalWrite(FRM_in4, LOW); 

  digitalWrite(FLM_in1, LOW);
  digitalWrite(FLM_in2, HIGH);
  digitalWrite(RLM_in3, LOW);
  digitalWrite(RLM_in4, HIGH); 
}

//////////////////////////////////////////////////////////////////////////////
// MovBKWD( int speed ):  Right and left wheels will rotate in the CCW direction.
//    "speed" parameter {0 - 100} is the modulation percentage of the PWM signal.
//////////////////////////////////////////////////////////////////////////////

void MovBKWD( float speed )
{
  float  PWMval = 255*(speed/100);
  // The PWMval varies between 0 and 255
  
  analogWrite(EnableLM1, PWMval);
  analogWrite(EnableRM1, PWMval);

  analogWrite(EnableLM2, PWMval);
  analogWrite(EnableRM2, PWMval);

  // Rotate Right and Left wheels counter-clockwise (CCW)  
  digitalWrite(RRM_in1, LOW);
  digitalWrite(RRM_in2, HIGH);
  digitalWrite(FRM_in3, LOW);
  digitalWrite(FRM_in4, HIGH); 

  digitalWrite(FLM_in1, HIGH);
  digitalWrite(FLM_in2, LOW);
  digitalWrite(RLM_in3, HIGH);
  digitalWrite(RLM_in4, LOW); 
}

//////////////////////////////////////////////////////////////////////////////
// RotateRt( int speed ):  
//    CW rotation of vehicle -- Left wheel rotates forward; Right wheel
//    rotates backwards.  Each time this subroutine is called, causes the
//    vehicle to rotate in time-step increments.  The predefined value for
//    "TimeStep_ms" is the number of milli-seconds of rotation.  The angle
//    the vehicle will be facing is determined by how fast the vehicle is 
//    rotating and the duration of rotation (how long the vehicle has been)
//    rotating.
//
//    "speed" parameter {0 - 100} is the modulation percentage of the PWM signal.
//////////////////////////////////////////////////////////////////////////////

void RotateRt( float speed )
{
  float  PWMval = 255*(speed/100);
  // The PWMval varies between 0 and 255
  
  analogWrite(EnableLM1, PWMval);
  analogWrite(EnableRM1, PWMval);

  analogWrite(EnableLM2, PWMval);
  analogWrite(EnableRM2, PWMval);

  // Rotate Left wheel forward; Rotate Right wheel backward  
  
  digitalWrite(RRM_in1, LOW);
  digitalWrite(RRM_in2, HIGH);
  digitalWrite(FRM_in3, LOW);
  digitalWrite(FRM_in4, HIGH); 

  digitalWrite(FLM_in1, LOW);
  digitalWrite(FLM_in2, HIGH);
  digitalWrite(RLM_in3, LOW);
  digitalWrite(RLM_in4, HIGH); 
}

//////////////////////////////////////////////////////////////////////////////
// RotateLft( int speed ):  
//    CCW rotation of vehicle -- Left wheel rotates backward; Right wheel
//    rotates forward.  Each time this subroutine is called, causes the
//    vehicle to rotate in time-step increments.  The predefined value for
//    "TimeStep_ms" is the number of milli-seconds of rotation.  The angle
//    the vehicle will be facing is determined by how fast the vehicle is 
//    rotating and the duration of rotation (how long the vehicle has been
//    rotating).
//
//    "speed" parameter {0 - 100} is the modulation percentage of the PWM signal.
//////////////////////////////////////////////////////////////////////////////

void RotateLft( float speed)
{
  float  PWMval = 255*(speed/100);
  // The PWMval varies between 0 and 255
  
  analogWrite(EnableLM1, PWMval);
  analogWrite(EnableRM1, PWMval);

  analogWrite(EnableLM2, PWMval);
  analogWrite(EnableRM2, PWMval);

  // Rotate Left wheel backward; Rotate Right wheel forward  
  digitalWrite(RRM_in1, HIGH);
  digitalWrite(RRM_in2, LOW);
  digitalWrite(FRM_in3, HIGH);
  digitalWrite(FRM_in4, LOW); 

  digitalWrite(FLM_in1, HIGH);
  digitalWrite(FLM_in2, LOW);
  digitalWrite(RLM_in3, HIGH);
  digitalWrite(RLM_in4, LOW); 
}

void StrafeLft(float speed)
{
    float  PWMval = 255*(speed/100);
  // The PWMval varies between 0 and 255
  
  analogWrite(EnableLM1, PWMval);
  analogWrite(EnableRM1, PWMval);

  analogWrite(EnableLM2, PWMval);
  analogWrite(EnableRM2, PWMval);

  // Rotate Left wheel backward; Rotate Right wheel forward  
  digitalWrite(RRM_in1, LOW);
  digitalWrite(RRM_in2, HIGH);
  digitalWrite(FRM_in3, HIGH);
  digitalWrite(FRM_in4, LOW); 

  digitalWrite(FLM_in1, HIGH);
  digitalWrite(FLM_in2, LOW);
  digitalWrite(RLM_in3, LOW);
  digitalWrite(RLM_in4, HIGH); 
}

void StrafeRt(float speed)
{
    float  PWMval = 255*(speed/100);
  // The PWMval varies between 0 and 255
  
  analogWrite(EnableLM1, PWMval);
  analogWrite(EnableRM1, PWMval);

  analogWrite(EnableLM2, PWMval);
  analogWrite(EnableRM2, PWMval);

  // Rotate Left wheel backward; Rotate Right wheel forward  
  digitalWrite(RRM_in1, HIGH);
  digitalWrite(RRM_in2, LOW);
  digitalWrite(FRM_in3, LOW);
  digitalWrite(FRM_in4, HIGH); 

  digitalWrite(FLM_in1, LOW);
  digitalWrite(FLM_in2, HIGH);
  digitalWrite(RLM_in3, HIGH);
  digitalWrite(RLM_in4, LOW); 

}