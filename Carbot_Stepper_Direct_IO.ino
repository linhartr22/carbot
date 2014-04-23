/* Cardboarduino Robot Stepper Motor Control Direct I/O
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
//#define DEBUG

// 28BYJ-48 unipolar stepper motor, 8 steps per revolution w/ 1/64 reduction gear
#define stepsPerRevMax 512
// ULN2003 Controller
// IN1 = A = Blue
// IN2 = B = Pink
// IN3 = C = Yellow
// IN4 = D = Orange
// Step Sequences
#define stepSeqHalf 0  // Half Step Sequence Index
#define stepSeqFull 1  // Full Step Sequence Index
#define stepSeqMax 2   // Number of Step Seguences
const byte stepSeq[stepSeqMax][8] = { 
  {B0001, B0011, B0010, B0110, B0100, B1100, B1000, B1001}, 
  {B0011, B0110, B1100, B1001, B0011, B0110, B1100, B1001} 
};
// Stepper Motor(s) Status
#define stepperL 0                          // Stepper Motor Left Index
#define stepperR 1                          // Stepper Motor Right Index
#define stepperMax 2                        // Stepper Motor Max Index
#define stepperIOMax 4                      // Stepper Motor I/O Pins Max
byte stepperIO[stepperMax][stepperIOMax];   // Stepper Motor I/O Pins
int stepperLoc[stepperMax];                 // Stepper Motor Location
byte stepperSeqTyp[stepperMax];             // Stepper Motor Sequence Type
byte stepperSeqCnt[stepperMax];             // Stepper Motor Sequence Count
#define stepperDirCW 1                      // Stepper Motor Direction Clock Wise
#define stepperDirCCW -1                    // Stepper Motor Direction Counter-Clock Wise
byte stepperDir[stepperMax];                // Stepper Motor Direction
boolean stepperSpd = true;                  // Stepper Speed Max

// setup() runs once after RESET
void setup() {
  #ifdef DEBUG
  // Init Serial for DEBUG
  Serial.begin(9600);
  Serial.println("setup() Begin!");
  #endif

  // Init Stepper Motor Left I/O Pins
  stepperIO[stepperL][0] = 4;
  stepperIO[stepperL][1] = 5;
  stepperIO[stepperL][2] = 6;
  stepperIO[stepperL][3] = 7;
  // Init Stepper Motor Right I/O Pins
  stepperIO[stepperR][0] = 8;
  stepperIO[stepperR][1] = 9;
  stepperIO[stepperR][2] = 10;
  stepperIO[stepperR][3] = 11;
  // Init Stepper Motors
  for (byte stepperIndex = 0; stepperIndex < stepperMax; stepperIndex++) {
    // Init Stepper Motor I/O Pins
    for (byte stepperIOIndex = 0; stepperIOIndex < stepperIOMax; stepperIOIndex++) {
      pinMode(stepperIO[stepperIndex][stepperIOIndex], OUTPUT);
    }
    // Init Stepper Motor(s) Location
    stepperLoc[stepperIndex] = 0;
    // Init Stepper Motor(s) Step Sequence Count
    stepperSeqCnt[stepperIndex] = 0;    
  }
  // Init Step Sequence Type
  stepperSeqTyp[stepperL] = stepSeqHalf;
  stepperSeqTyp[stepperR] = stepSeqHalf;
  // Init Stepper Motor Direction
  stepperDir[stepperL] = stepperDirCCW;
  stepperDir[stepperR] = stepperDirCW;
  // Refresh Stepper Motor I/O Pins
  refreshStepperMotorIO(stepperL);
  refreshStepperMotorIO(stepperR);
  #ifdef DEBUG
  Serial.println("setup() End!");
  #endif
}

// loop() runs continuously after setup()
void loop() {
  // Alternate Speed
  long firstMillis = millis();
  while (firstMillis + 2000 > millis()) {
    // Step Left and Right Stepper Motors
    for (byte stepperIndex = 0; stepperIndex < stepperMax; stepperIndex++) {
      #ifdef DEBUG
      Serial.println("Stepper Motor=" + String(stepperIndex) + "!");
      Serial.println("  StepperSeqCnt=" + String(stepperSeqCnt[stepperIndex]) + "!");
      Serial.println("  StepperDir=" + String(stepperDir[stepperIndex]) + "!");
      #endif
      // Update Stepper Motor Sequence Count
      stepperSeqCnt[stepperIndex] = (stepperSeqCnt[stepperIndex] + (1 * stepperDir[stepperIndex])) & B111;
      // Refresh Stepper Motor I/O
      refreshStepperMotorIO(stepperIndex);
    }
    // Step Sequence Type = Full?
    if (stepperSeqTyp[stepperL] == stepSeqFull) {
      // Yes, stepSeqFull Delay
      if (stepperSpd) {
        // Top Speed
        delay(100);
      }
      else {
        // Visual Stepping Speed
        delay(2);
      }
    }
    else {
      // No, stepSeqHalf Delay
      if (stepperSpd) {
        // Top Speed
        delay(50);
      }
      else {
        // Visual Stepping Speed
        delay(1);
      }
    }
  }
  stepperSpd = !stepperSpd;
  // Full Stepper Speed Cycle?
  if (stepperSpd) {
    // Yes, Reverse Stepper Motor Direction
    stepperDir[stepperL] *= -1;
    stepperDir[stepperR] *= -1;
  }
}

// Refresh Stepper Motor I/O
void refreshStepperMotorIO(byte stepperIndex) {
  // Refresh Stepper Motor I/O with Current Step Sequence
  for (byte stepperIOIndex = 0; stepperIOIndex < stepperIOMax; stepperIOIndex++) {
    digitalWrite(stepperIO[stepperIndex][stepperIOIndex], stepSeq[stepperSeqTyp[stepperIndex]][stepperSeqCnt[stepperIndex]] >> stepperIOIndex & B0001);
  }
}
