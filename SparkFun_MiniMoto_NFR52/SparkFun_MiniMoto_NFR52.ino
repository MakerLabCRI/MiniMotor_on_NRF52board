#include "SparkFunMiniMoto.h"  // Include the MiniMoto library

MiniMoto motor0(0x65); // A1 = 1, A0 = clear      // 0xC4 by default 
MiniMoto motor1(0x60); // A1 = 1, A0 = 1 (default)  // 0xC0 by default


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  
  Wire.begin();
  delay(2000);
  Serial.println("default motor 1: "+String(motor1.getFault()));
  Serial.println("default motor 0: "+String(motor0.getFault()));
}

void loop()
{
  Serial.println("Forward!");
  motor0.drive(10);
  motor1.drive(10);
  delayUntil(10000);
  Serial.println("Stop!");
  motor0.stop();
  motor1.stop();
  delay(2000);
  Serial.println("Reverse!");
  motor0.drive(-10);
  motor1.drive(-10);
  delayUntil(10000);
  Serial.println("Brake!");
  motor0.brake();
  motor1.brake();
  delay(2000);
}

// delayUntil() is a little function to run the motor either for
//  a designated time OR until a fault occurs. Note that this is
//  a very simple demonstration; ideally, an interrupt would be
//  used to service faults rather than blocking the application
//  during motion and polling for faults.
void delayUntil(unsigned long elapsedTime)
{
  // See the "BlinkWithoutDelay" example for more details on how
  //  and why this loop works the way it does.
  unsigned long startTime = millis();
  while (startTime + elapsedTime > millis())
  {
   
      // We're going to check both motors; the logic is the same
      //  for each...
      byte result;
      result = motor0.getFault();
      Serial.println("default motor 0: "+String(motor0.getFault()));

      // If result masked by FAULT is non-zero, we've got a fault
      //  condition, and we should report it.
      if (result & FAULT)
      {
        Serial.print("Motor 0 fault: ");
        if (result & OCP) Serial.println("Chip overcurrent!");
        if (result & ILIMIT) Serial.println("Load current limit!");
        if (result & UVLO) Serial.println("Undervoltage!");
        if (result & OTS) Serial.println("Over temp!");
        //break; // We want to break out of the motion immediately,
               //  so we can stop motion in response to our fault.
      }
      
      result = motor1.getFault();
      Serial.println("default motor 1: "+String(motor1.getFault()));

      if (result & FAULT)
      {
        Serial.print("Motor 1 fault: ");
        if (result & OCP) Serial.println("Chip overcurrent!");
        if (result & ILIMIT) Serial.println("Load current limit!");
        if (result & UVLO) Serial.println("Undervoltage!");
        if (result & OTS) Serial.println("Over temp!");
        //break;
      }
  }
}
