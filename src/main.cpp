#include <Arduino.h>

#define SERIAL_SPEED 115200

// Pins
#define ROTATE_CW_PIN 34    // Mini-DIN Pin 1
#define ROTATE_CCW_PIN 35   // Mini-DIN Pin 2
#define SPEED_IN_PIN 33     // Mini-DIN Pin 3
#define ANGLE_OUT_PIN 25    // Mini-DIN Pin 4


// ------------------------------------------------------------------
// SETUP ------------------------------------------------------------
// ------------------------------------------------------------------

void setup() {
  // Setup IO
  pinMode(ROTATE_CW_PIN, INPUT_PULLUP);
  pinMode(ROTATE_CCW_PIN, INPUT_PULLUP);
  dacWrite(ANGLE_OUT_PIN, 0);

  // Init Serial
  Serial.begin(SERIAL_SPEED);
  Serial.println("\n########## RotorEmulator ##########");
}


// ------------------------------------------------------------------
// LOOP -------------------------------------------------------------
// ------------------------------------------------------------------

int8_t dir = 0;
uint16_t speed = 0;
int angle = 0;
int step = 0;


void loop() {
  // Get speed
  speed = analogRead(SPEED_IN_PIN);
  if (speed == 0) {
    speed = 1;
  }
  
  // Get rotation direction
  dir = 0;
  if (digitalRead(ROTATE_CW_PIN) == LOW) {
    dir = 1;
  }
  if (digitalRead(ROTATE_CCW_PIN) == LOW) {
    dir = -1;
  }

  // Logging
  Serial.printf("Speed: %4d | Angle: %3d | Dir: %2d", speed, angle, dir);

  // Set angle
  if (dir != 0) {
    step = std::ceil(speed / 1024.0f) * dir;
    Serial.printf(" | ++ %3d", step);
    angle += step;
  }

  if (angle > 255) {
    angle = 255;
  }

  if (angle < 0) {
    angle = 0;
  }

  dacWrite(ANGLE_OUT_PIN, angle);
  
  Serial.println();
  delay(150);
}
