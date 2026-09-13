#include <VirtualWire.h>

const int xPin = A0;
const int yPin = A1;
const int txPin = 12;

int xVal, yVal;
int xCenter, yCenter;

int threshold = 60;

void setup() {
  Serial.begin(9600);

  vw_set_tx_pin(txPin);
  vw_setup(2000);

  delay(2000);

  // calibration
  xCenter = analogRead(xPin);
  yCenter = analogRead(yPin);

  Serial.println("TX Ready (STOP reduced mode)");
}

void loop() {

  xVal = analogRead(xPin);
  yVal = analogRead(yPin);

  int xDiff = xVal - xCenter;
  int yDiff = yVal - yCenter;

  char dir;

  // -------- MORE RESPONSIVE LOGIC --------

  if (yDiff > threshold) {
    dir = 'F';
  }
  else if (yDiff < -threshold) {
    dir = 'B';
  }
  else if (xDiff > threshold) {
    dir = 'R';
  }
  else if (xDiff < -threshold) {
    dir = 'L';
  }
  else {
    dir = 'S';
  }

  vw_send((uint8_t *)&dir, 1);
  vw_wait_tx();

  Serial.print("X=");
  Serial.print(xVal);
  Serial.print(" Y=");
  Serial.print(yVal);
  Serial.print(" → ");

  if (dir == 'F') Serial.println("FORWARD");
  else if (dir == 'B') Serial.println("BACKWARD");
  else if (dir == 'L') Serial.println("LEFT");
  else if (dir == 'R') Serial.println("RIGHT");
  else Serial.println("STOP");

  delay(70);
}