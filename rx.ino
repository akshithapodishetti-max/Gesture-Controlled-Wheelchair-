/*
  Gesture Controlled Wheelchair - RECEIVER SIDE
  RF 433MHz + L298N Motor Driver
*/

#include <VirtualWire.h>

// RF Receiver pin
const int rxPin = 11;

// Motor driver pins
const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 7;

// received data
char msg;

void setup() {
  Serial.begin(9600);

  // motor pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // RF setup
  vw_set_rx_pin(rxPin);
  vw_setup(2000);
  vw_rx_start();

  stopMotors();

  Serial.println("RX Ready...");
}

void loop() {

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {

    msg = buf[0];

    Serial.print("Received: ");

    // -------- MOTOR CONTROL --------

    if (msg == 'F') {
      Serial.println("FORWARD");
      forward();
    }

    else if (msg == 'B') {
      Serial.println("BACKWARD");
      backward();
    }

    else if (msg == 'R') {
      Serial.println("RIGHT");
      right();
    }

    else if (msg == 'L') {
      Serial.println("LEFT");
      left();
    }

    else {
      Serial.println("STOP");
      stopMotors();
    }
  }
}

// -------- MOTOR FUNCTIONS --------

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}