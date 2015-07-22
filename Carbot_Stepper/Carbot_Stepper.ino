/* Cardboarduino Robot Stepper Motor Control
 *
 * Test Cardboarduino Robot Stepper Motors.
 *
 * If you found this fun or interesting please make a small donation to my PayPal account 
 * at: https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=U48JEW8HSQFM2 
 * I have many more Arduino projects in mind and appreciate your support.
 *
 * No commercial use without prior consent.
 *
 */

// Comment the line below to remove DEBUG code
#define DEBUG

// Acceleration Stepper Motor Library
#include <AccelStepper.h>
// 28BYJ-48 unipolar stepper motor, 8 steps per revolution w/ 1/64 reduction gear
#define stepsPerRev 512
// ULN2003 Controller
// IN1 = A = Blue
// IN2 = B = Pink
// IN3 = C = Yellow
// IN4 = D = Orange
// Left Stepper Motor
AccelStepper stepperL(AccelStepper::FULL4WIRE, 4, 6, 5, 7);
// Right Stepper Motor
AccelStepper stepperR(AccelStepper::FULL4WIRE, 8, 10, 9, 11);

void setup() {
  #ifdef DEBUG
  // Init Serial for DEBUG
  Serial.begin(9600);
  Serial.println("setup() Begin!");
  #endif
  // Init Stepper Motors
  // Stepper Motor Max Speed
  #define stepperMaxSpeed 8000.0
  stepperL.setMaxSpeed(stepperMaxSpeed);
  stepperR.setMaxSpeed(stepperMaxSpeed);
  // Stepper Motor Acceleration steps/sec/sec
  #define stepperAcceleration 100.0
  stepperL.setAcceleration(stepperAcceleration);
  stepperR.setAcceleration(stepperAcceleration);
  // Stepper Motor Speed
  #define stepperSpeed 8000
  stepperL.setSpeed(stepperSpeed);
  stepperR.setSpeed(stepperSpeed);
  // Movement = One Revolution
  stepperL.moveTo(stepsPerRev);
  stepperR.moveTo(-stepsPerRev);
  #ifdef DEBUG
  Serial.println("setup() End!");
  #endif
}

void loop() {
  #ifdef DEBUG
  //Serial.print("stepperL.distanceToGo()=" + String(stepperL.distanceToGo()) + "   ");
  //Serial.println("stepperR.distanceToGo()=" + String(stepperR.distanceToGo()));
  #endif
  // Change Direction?
  if (stepperL.distanceToGo() == 0 & stepperR.distanceToGo() == 0) {
    // Yes
    stepperL.moveTo(-stepperL.currentPosition());
    stepperR.moveTo(-stepperR.currentPosition());
  }
  // Refresh Stepper Motors
  stepperL.run();
  stepperR.run();
  //delay(1000);
}

