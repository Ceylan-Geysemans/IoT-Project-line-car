#define groen 25
#define rood 33
#define geel 32
#define blauw 14

#define irr 34
#define irl 35

#define en1 12
#define motor1pin1 18
#define motor1pin2 19

#define en2 14
#define motor2pin1 26
#define motor2pin2 27

#define interruptPin 5

#define trigpin 23    // Trigger
#define echopin 4    // Echo

volatile byte state = LOW;

//Variables
long duration;
int  frontdist;

int setdist = 10;

int left_sensor_state;
int right_sensor_state;
int stopper = true;

void setup() {
  Serial.begin(115200);
  pinMode(irl, INPUT);
  pinMode(irr, INPUT);
  pinMode(en1, OUTPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(groen, OUTPUT);
  pinMode(rood, OUTPUT);
  pinMode(geel, OUTPUT);
  pinMode(blauw, OUTPUT);
  pinMode(interruptPin, INPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), loop, CHANGE);
}

void loop() {

  left_sensor_state = digitalRead(irl);
  right_sensor_state = digitalRead(irr);

  frontdist = data();
  Serial.print("front distance: ");
  Serial.println(frontdist);

  if (frontdist > setdist) {
    if (right_sensor_state == 0 && left_sensor_state == 1)
    {
      Serial.println("turning right");

      digitalWrite(groen, HIGH);
      digitalWrite(rood, LOW);
      digitalWrite(geel, LOW);
      digitalWrite(blauw, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
    }
    if (right_sensor_state == 1 && left_sensor_state == 0)
    {
      Serial.println("turning left");

      digitalWrite(groen, HIGH);
      digitalWrite(rood, LOW);
      digitalWrite(geel, LOW);
      digitalWrite(blauw, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);
    }

    if (right_sensor_state == 0 && left_sensor_state == 0)
    {
      Serial.println("going forward");

      digitalWrite(groen, HIGH);
      digitalWrite(rood, LOW);
      digitalWrite(geel, LOW);
      digitalWrite(blauw, LOW);

      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
    }

    if (right_sensor_state == 1 && left_sensor_state == 1)
    {
      Serial.println("stop");

      digitalWrite(groen, LOW);
      digitalWrite(rood, LOW);
      digitalWrite(geel, LOW);
      digitalWrite(blauw, HIGH);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      if (stopper == true) {
        delay(20000);
        stopper = false;
      }

      Serial.println("verder");

      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);


      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
      delay(250);
    }
  }
  else {
    Serial.println("collision warning!");

    digitalWrite(groen, LOW);
    digitalWrite(rood, LOW);
    digitalWrite(geel, HIGH);
    digitalWrite(blauw, LOW);

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
  }
}

long data() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn (echopin, HIGH);
  return duration / 29 / 2;
}

void advance() {
  stopper = true;
}
