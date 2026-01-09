#include <DabbleESP32.h>
#include <ESP32Servo.h> 

// Motor pins
const int motor1Pin1 = 16;
const int motor1Pin2 = 13;

// LED pins
const int leftHeadlightPin = 18;
const int rightHeadlightPin = 14;
const int leftBacklightPin = 22;
const int rightBacklightPin = 26;

// Speaker pin
const int speakerPin = 25;

// Servo pin
const int servoPin = 12;

// Servo object
Servo steeringServo; 
int servoPosition = 90;  // Default center position
bool leftPressedLast = false;
bool rightPressedLast = false;

// Turn signal logic
unsigned long previousBlinkTime = 0;
const int blinkInterval = 500; 
bool blinkState = false;

// Car state
bool carOn = false;

// Direction change timing
unsigned long lastDirectionChangeTime = 0;
const unsigned long directionChangeDelay = 50;

// Function declarations
void flashLightsAndBeep(int times, int duration);
void flashLights(int times, int duration);
void stopMotors();
void turnOffLights();

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(leftHeadlightPin, OUTPUT);
  pinMode(rightHeadlightPin, OUTPUT);
  pinMode(leftBacklightPin, OUTPUT);
  pinMode(rightBacklightPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  // Attach the servo
  steeringServo.attach(servoPin, 500, 2500);
  steeringServo.write(servoPosition);

  Dabble.begin("MyCarController");
}

void loop() {
  Dabble.processInput();  // Process GamePad input

  bool upPressed = GamePad.isUpPressed();
  bool downPressed = GamePad.isDownPressed();
  bool leftPressed = GamePad.isLeftPressed();
  bool rightPressed = GamePad.isRightPressed();
  bool trianglePressed = GamePad.isTrianglePressed();
  bool squarePressed = GamePad.isSquarePressed();
  bool circlePressed = GamePad.isCirclePressed();
  bool crossPressed = GamePad.isCrossPressed();
  bool startPressed = GamePad.isStartPressed();
  bool selectPressed = GamePad.isSelectPressed();

  // Handle car start
  if (startPressed && !carOn) {
    carOn = true;
    flashLightsAndBeep(2, 200);
  }

  // Handle car stop
  if (selectPressed && carOn) {
    carOn = false;
    flashLights(2, 200);
  }

  // If the car is off, skip the rest of the logic
  if (!carOn) {
    stopMotors();
    turnOffLights();
    return;
  }

  // Handle blinking logic
  unsigned long currentTime = millis();
  if (currentTime - previousBlinkTime >= blinkInterval) {
    previousBlinkTime = currentTime;
    blinkState = !blinkState;
  }

  // Hazard lights blinking logic
  if (trianglePressed) {
    digitalWrite(leftHeadlightPin, blinkState);
    digitalWrite(rightHeadlightPin, blinkState);
    digitalWrite(leftBacklightPin, blinkState);
    digitalWrite(rightBacklightPin, blinkState);
  } else {
    digitalWrite(leftHeadlightPin, LOW);
    digitalWrite(rightHeadlightPin, LOW);
    digitalWrite(leftBacklightPin, LOW);
    digitalWrite(rightBacklightPin, LOW);
  }

  // Left turn signal logic
  if (squarePressed) {
    digitalWrite(leftHeadlightPin, blinkState);
  } else if (!trianglePressed) {
    digitalWrite(leftHeadlightPin, LOW);
  }

  // Right turn signal logic
  if (circlePressed) {
    digitalWrite(rightHeadlightPin, blinkState);
  } else if (!trianglePressed) {
    digitalWrite(rightHeadlightPin, LOW);
  }

  // Prevent forward and backward from being active at the same time
  if (upPressed && downPressed) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
  } else if (upPressed) {
    if (millis() - lastDirectionChangeTime >= directionChangeDelay) {
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      lastDirectionChangeTime = millis();
    }
    digitalWrite(leftHeadlightPin, HIGH);
    digitalWrite(rightHeadlightPin, HIGH);
    digitalWrite(leftBacklightPin, LOW);
    digitalWrite(rightBacklightPin, LOW);
  } else if (downPressed) {
    if (millis() - lastDirectionChangeTime >= directionChangeDelay) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      lastDirectionChangeTime = millis();
    }
    digitalWrite(leftHeadlightPin, LOW);
    digitalWrite(rightHeadlightPin, LOW);
    digitalWrite(leftBacklightPin, HIGH);
    digitalWrite(rightBacklightPin, HIGH);
  } else {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
  }

  // Toggle left steering
  if (leftPressed && !leftPressedLast) {
    if (servoPosition == 60) {
      servoPosition = 96;  // Reset to center + 6° to compensate for design issue 
    } else {
      servoPosition = 60;  // Turn left
    }
    steeringServo.write(servoPosition);
  }
  leftPressedLast = leftPressed; // Update last state

  // Toggle right steering
  if (rightPressed && !rightPressedLast) {
    if (servoPosition == 120) {
      servoPosition = 90;  // Reset to center
    } else {
      servoPosition = 120;  // Turn right
    }
    steeringServo.write(servoPosition);
  }
  rightPressedLast = rightPressed; // Update last state

  // Speaker (car horn)
  if (crossPressed) {
    digitalWrite(speakerPin, HIGH); 
  } else {
    digitalWrite(speakerPin, LOW);
  }
}

// Helper function to flash all lights and beep at the same time
void flashLightsAndBeep(int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(leftHeadlightPin, HIGH);
    digitalWrite(rightHeadlightPin, HIGH);
    digitalWrite(leftBacklightPin, HIGH);
    digitalWrite(rightBacklightPin, HIGH);
    digitalWrite(speakerPin, HIGH); // Beep sound
    delay(duration);
    digitalWrite(leftHeadlightPin, LOW);
    digitalWrite(rightHeadlightPin, LOW);
    digitalWrite(leftBacklightPin, LOW);
    digitalWrite(rightBacklightPin, LOW);
    digitalWrite(speakerPin, LOW); // Stop beep
    delay(duration);
  }
}

// Helper function to flash all lights
void flashLights(int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(leftHeadlightPin, HIGH);
    digitalWrite(rightHeadlightPin, HIGH);
    digitalWrite(leftBacklightPin, HIGH);
    digitalWrite(rightBacklightPin, HIGH);
    delay(duration);
    digitalWrite(leftHeadlightPin, LOW);
    digitalWrite(rightHeadlightPin, LOW);
    digitalWrite(leftBacklightPin, LOW);
    digitalWrite(rightBacklightPin, LOW);
    delay(duration);
  }
}

// Helper function to stop motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
}

// Helper function to turn off lights
void turnOffLights() {
  digitalWrite(leftHeadlightPin, LOW);
  digitalWrite(rightHeadlightPin, LOW);
  digitalWrite(leftBacklightPin, LOW);
  digitalWrite(rightBacklightPin, LOW);
}
