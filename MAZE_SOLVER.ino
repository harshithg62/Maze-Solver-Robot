#define TRIG_FRONT 3
#define ECHO_FRONT 4

#define TRIG_SIDE 10
#define ECHO_SIDE 11

// Motor pins
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9

int safeDistance = 14;

long readDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.034 / 2;

  if(distance == 0) distance = 200;

  return distance;
}

void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  delay(80);   // small brake delay
}

void moveForward()
{
  Serial.println("Forward");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(120);
  stopMotors();
}

void moveBackward()
{
  Serial.println("Backward");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(150);
  stopMotors();
}

void turnLeft()
{
  Serial.println("Turn Left");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(500);
  stopMotors();
}

void turnRight()
{
  Serial.println("Turn Right");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(500);
  stopMotors();
}

void uTurn()
{
  Serial.println("U Turn");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(1050);
  stopMotors();
}

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);

  pinMode(TRIG_SIDE, OUTPUT);
  pinMode(ECHO_SIDE, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  Serial.println("Robot Ready");
}

void loop()
{
  long front = readDistance(TRIG_FRONT, ECHO_FRONT);

  Serial.print("Front: ");
  Serial.println(front);

  if(front > safeDistance)
  {
    moveForward();
  }
  else
  {
    Serial.println("Obstacle Ahead");

    moveBackward();   // move back a little

    long side = readDistance(TRIG_SIDE, ECHO_SIDE);

    Serial.print("Side: ");
    Serial.println(side);

    if(side > safeDistance)
    {
      turnLeft();
    }
    else
    {
      uTurn();
    }
  }

  Serial.println("----------------");
}
