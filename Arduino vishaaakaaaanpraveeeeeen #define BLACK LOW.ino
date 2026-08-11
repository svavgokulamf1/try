// Automatic Line-Following Robot Waiter
// Arduino UNO + 2 IR sensors + HC-SR04 + L298N


#define IR_LEFT 2
#define IR_RIGHT 3


#define TRIG_PIN 9
#define ECHO_PIN 10


#define ENA 5
#define IN1 6
#define IN2 7


#define ENB 11
#define IN3 8
#define IN4 12


int motorSpeed = 150;


// =================================================
// CHANGE THIS:
//
// LOW = IR gives LOW when it sees BLACK
// HIGH = IR gives HIGH when it sees BLACK
// =================================================
#define BLACK LOW


void setup() {
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);


  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);


  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


  stopRobot();
}


void loop() {


  // ---------- Obstacle Detection ----------
  long distance = getDistance();


  if (distance > 0 && distance < 20) {
    stopRobot();
    return;
  }


  // ---------- Read IR Sensors ----------
  bool leftBlack = (digitalRead(IR_LEFT) == BLACK);
  bool rightBlack = (digitalRead(IR_RIGHT) == BLACK);


  // ---------- Line Following ----------


  // Both sensors on black
  if (leftBlack && rightBlack) {
    forward();
  }


  // Left sensor on black
  else if (leftBlack && !rightBlack) {
    turnLeft();
  }


  // Right sensor on black
  else if (!leftBlack && rightBlack) {
    turnRight();
  }


  // Both sensors on white
  else {
    stopRobot();
  }
}


// =================================================
// MOTOR FUNCTIONS
// =================================================


void forward() {


  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);


  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);


  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void turnLeft() {


  analogWrite(ENA, 80);
  analogWrite(ENB, motorSpeed);


  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);


  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void turnRight() {


  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, 80);


  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);


  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void stopRobot() {


  analogWrite(ENA, 0);
  analogWrite(ENB, 0);


  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);


  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// =================================================
// ULTRASONIC SENSOR
// =================================================


long getDistance() {


  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);


  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  long duration = pulseIn(ECHO_PIN, HIGH, 30000);


  if (duration == 0)
    return -1;


  return duration * 0.034 / 2;
}