/*
*********made by gada888 From LUOYANG
*Date:30-12-2020*******
*/

#include <AFMotor.h>                                      // The Adafruit Motor Shield Library ver. 1
#include <Servo.h> 
                                                   
//****************************************************************************************************
Servo loadServo;  
int loadServoPin = 9;
int servoDelay = 500;
// Setup Drive Motors using the Adafruit Motor Controller version 1.0 Library

AF_DCMotor motor1(1, MOTOR12_64KHZ);                      // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ);                      // create motor #2, 64KHz pwm

int mtr_Spd = 250;                                        // set the speed of the motors

//*****************************************************************************************************
// Bluetooth Variables & Setup

String str;                                               // raw string received from android to arduino
int blueToothVal;                                         // stores the last value sent over via bluetooth

//*****************************************************************************************************

void setup() 
{  
  Serial.begin(9600);                                   
  loadServo.attach(loadServoPin);
  loadServo.write(120);
  delay(150);
}

//*****************************************************************************************************
// Main Loop

void loop()
{   
  bluetooth();                                          // Run the Bluetooth procedure to see if there is any data being sent via BT
}




//*****************************************************************************************************
// This procedure reads the serial port - Serial1 - for bluetooth commands being sent from the Android device

void bluetooth()
{
 while (Serial.available())                             // Read bluetooth commands over COM
 {  
  {  
      str = Serial.readStringUntil('\n');               // str is the temporary variable for storing the last sring sent over bluetooth from Android device
      //Serial.print(str);             
  } 
    
    blueToothVal = (str.toInt());                        //  convert the string 'str' into an integer and assign it to blueToothVal
    Serial.print("BlueTooth Value ");
    Serial.println(blueToothVal);    



// Bluetooth Section
// *********************************************************************************************************

 switch (blueToothVal) 
 {
      case 1:                                
        Serial.println("Reverse");
        Reverse();
        Stop();
        break;

      case 2:                 
        Serial.println("Forward");
        Forward();
        Stop();
        break;

      case 3:         
        Serial.println("Right");
        RightTurn();
        //Stop();
        break;
        
      case 4:                     
        Serial.println("Left");
        LeftTurn();
        //Stop();
        break;
        
      case 5:                                            
        Serial.println("Stop");
        Stop();
        break;      

      case 6:                                            
        Serial.println("Fire");
        Fire();
        break; 
 }                                                              
 }                                                             
 
                                                                
   if (Serial.available() < 0)                              
    {
     Serial.println("No Bluetooth Data ");          
    }
  
}

// Motor Control Section
// **********************************************************************************************************************************************************************

void Forward()
{
  Serial.println("Reverse");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);     
  
  motor1.run(FORWARD);                                                         
  motor2.run(FORWARD);

  delay(100);
}

// **********************************************************************************************************************************************************************


void Reverse()
{
  Serial.println("Forward");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);   
  
  motor1.run(BACKWARD);                                                        
  motor2.run(BACKWARD);

  delay(100);
}

// **********************************************************************************************************************************************************************

void LeftTurn()
{
  Serial.println("Right");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);
  
  motor1.run(BACKWARD);                                                        
  motor2.run(FORWARD);
  //delay(100);  
}

// **********************************************************************************************************************************************************************

void RightTurn()
{
  Serial.println("Left");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);

  motor1.run(FORWARD);                                              
  motor2.run(BACKWARD);
  //delay(100);                                                                      
}

// **********************************************************************************************************************************************************************
void Fire()
{
  Serial.println("Fire");
  loadServo.write(90);
  delay(servoDelay);
  loadServo.write(0);
  delay(350);                                                           
}

void Stop()
{ 
  motor1.run(RELEASE);                                                         
  motor2.run(RELEASE);
}
