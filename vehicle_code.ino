#include <DIYables_IRcontroller.h> // DIYables_IRcontroller library
#define IR_RECEIVER_PIN 9         // The Arduino pin connected to IR controller
#include <AFMotor.h>

#define TRIG_PIN A4               // Trigger pin for ultrasonic sensor
#define ECHO_PIN A5               // Echo pin for ultrasonic sensor
#define MAX_DISTANCE 200         // Maximum distance to consider (in cm)
#define MIN_SAFE_DISTANCE 15     // Minimum safe distance for parking (in cm)

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200); // debounce time is 200ms

void setup() {
  Serial.begin(9600);
  irController.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

long getDistance() {
  // Trigger the sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance (speed of sound * duration / 2)
  return duration * 0.034 / 2;
}

void do_przodu() {
  motor3.run(FORWARD);
  motor3.setSpeed(120);
  motor4.run(FORWARD);
  motor4.setSpeed(120);
}

void do_tylu() {
  motor3.run(BACKWARD);
  motor3.setSpeed(120);
  motor4.run(BACKWARD);
  motor4.setSpeed(120);
}

void lewo() {
  motor3.run(BACKWARD);
  motor3.setSpeed(120);
  motor4.run(FORWARD);
  motor4.setSpeed(120);
}

void prawo() {
  motor3.run(FORWARD);
  motor3.setSpeed(120);
  motor4.run(BACKWARD);
  motor4.setSpeed(120);
}

void parkowanie() {
  bool jo = true;
  while (jo) {
    long distance = getDistance();
    if (distance <= MIN_SAFE_DISTANCE) {
      Serial.println("Obstacle detected! Stopping...");
      zatrzymaj();
      break; // Zatrzymuje pętlę, gdy wykryto przeszkodę
    } else {
      motor3.run(BACKWARD);
      motor3.setSpeed(90);
      motor4.run(BACKWARD);
      motor4.setSpeed(90);
    }
    delay(100); // Opóźnienie przed kolejnym odczytem odległości
    
    Key21 command = irController.getKey();
    if (command != Key21::NONE) {
      // Obsługa innych poleceń podczas poruszania się do tyłu
      switch (command) {
        case Key21::KEY_VOL_MINUS:
        Serial.println("–");
        parkowanie_lewo();
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("+");
        parkowanie();
        jo = false;
        break;

      case Key21::KEY_EQ:
        Serial.println("EQ");
        parkowanie_prawo();
        jo = false;
        break;

        case Key21::KEY_0:
          Serial.println("0");
          zatrzymaj();
          jo = false;
          break;

        case Key21::KEY_1:
        Serial.println("1");
        przod_lewo();
        jo = false;
        break;

        case Key21::KEY_2:
          Serial.println("2");
          do_przodu();
          jo = false;
          break;

        case Key21::KEY_3:
          Serial.println("3");
          przod_prawo();
          jo = false;
          break;

        case Key21::KEY_4:
          Serial.println("4");
          lewo();
          jo = false;
          break;

        case Key21::KEY_5:
          Serial.println("5");
          zatrzymaj();
          jo = false;
          break;

        case Key21::KEY_6:
          Serial.println("6");
          prawo();
          jo = false;
          break;

        case Key21::KEY_7:
          Serial.println("7");
          tyl_lewo();
          jo = false;
          break;

        case Key21::KEY_8:
          Serial.println("8");
          do_tylu();
          jo = false;
          break;

        case Key21::KEY_9:
          Serial.println("9");
          tyl_prawo();
          jo = false;
          break;
          
        default:
          Serial.println("Exiting parking...");
          //return; // Wyjście z funkcji, jeśli zostanie naciśnięty inny przycisk
          break;
        }
    }
  }
}

void parkowanie_lewo() {
  bool jo = true;
  while (jo) {
    long distance = getDistance();
    if (distance <= MIN_SAFE_DISTANCE) {
      Serial.println("Obstacle detected! Stopping...");
      zatrzymaj();
      break; // Zatrzymuje pętlę, gdy wykryto przeszkodę
    } else {
      motor3.run(RELEASE);
      motor4.run(BACKWARD);
      motor4.setSpeed(150);
    }
    delay(100); // Opóźnienie przed kolejnym odczytem odległości
    
    Key21 command = irController.getKey();
    if (command != Key21::NONE) {
      // Obsługa innych poleceń podczas poruszania się do tyłu
      switch (command) {
        case Key21::KEY_VOL_MINUS:
        Serial.println("–");
        parkowanie_lewo();
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("+");
        parkowanie();
        jo = false;
        break;

      case Key21::KEY_EQ:
        Serial.println("EQ");
        parkowanie_prawo();
        jo = false;
        break;
        case Key21::KEY_0:
          Serial.println("0");
          zatrzymaj();
          jo = false;
          break;

        case Key21::KEY_1:
        Serial.println("1");
        przod_lewo();
        jo = false;
        break;

        case Key21::KEY_2:
          Serial.println("2");
          do_przodu();
          jo = false;
          break;

        case Key21::KEY_3:
          Serial.println("3");
          przod_prawo();
          jo = false;
          break;

        case Key21::KEY_4:
          Serial.println("4");
          lewo();
          jo = false;
          break;

        case Key21::KEY_5:
          Serial.println("5");
          zatrzymaj();
          jo = false;
          break;

        case Key21::KEY_6:
          Serial.println("6");
          prawo();
          jo = false;
          break;

        case Key21::KEY_7:
          Serial.println("7");
          tyl_lewo();
          jo = false;
          break;

        case Key21::KEY_8:
          Serial.println("8");
          do_tylu();
          jo = false;
          break;

        case Key21::KEY_9:
          Serial.println("9");
          tyl_prawo();
          jo = false;
          break;
          
        default:
          Serial.println("Exiting parking...");
          //return; // Wyjście z funkcji, jeśli zostanie naciśnięty inny przycisk
          break;
        }
    }
  }
}

void parkowanie_prawo() {
  bool jo = true;
  while (jo) {
    long distance = getDistance();
    if (distance <= MIN_SAFE_DISTANCE) {
      Serial.println("Obstacle detected! Stopping...");
      zatrzymaj();
      break; // Zatrzymuje pętlę, gdy wykryto przeszkodę
    } else {
      motor3.run(BACKWARD);
      motor3.setSpeed(150);
      motor4.run(RELEASE);
    }
    delay(100); // Opóźnienie przed kolejnym odczytem odległości
    
    Key21 command = irController.getKey();
    if (command != Key21::NONE) {
      // Obsługa innych poleceń podczas poruszania się do tyłu
      switch (command) {
        case Key21::KEY_VOL_MINUS:
        Serial.println("–");
        parkowanie_lewo();
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("+");
        parkowanie();
        jo = false;
        break;

      case Key21::KEY_EQ:
        Serial.println("EQ");
        parkowanie_prawo();
        jo = false;
        break;

        case Key21::KEY_0:
          Serial.println("0");
          zatrzymaj();
          jo = false;
          break;

        case Key21::KEY_1:
        Serial.println("1");
        przod_lewo();
        jo = false;
        break;

        case Key21::KEY_2:
          Serial.println("2");
          do_przodu();
          jo = false;
          break;

        case Key21::KEY_3:
          Serial.println("3");
          przod_prawo();
          jo = false;
          break;

        case Key21::KEY_4:
          Serial.println("4");
          lewo();
          jo = false;
          break;

        case Key21::KEY_5:
          Serial.println("5");
          zatrzymaj();
          jo = false;
          break;

        case Key21::KEY_6:
          Serial.println("6");
          prawo();
          jo = false;
          break;

        case Key21::KEY_7:
          Serial.println("7");
          tyl_lewo();
          jo = false;
          break;

        case Key21::KEY_8:
          Serial.println("8");
          do_tylu();
          jo = false;
          break;

        case Key21::KEY_9:
          Serial.println("9");
          tyl_prawo();
          jo = false;
          break;
          
        default:
          Serial.println("Exiting parking...");
          //return; // Wyjście z funkcji, jeśli zostanie naciśnięty inny przycisk
          break;
        }
    }
  }
}

void tyl_lewo(){
  motor3.run(RELEASE);
  motor4.run(BACKWARD);
  motor4.setSpeed(120);
}

void tyl_prawo(){
  motor3.run(BACKWARD);
  motor3.setSpeed(120);
  motor4.run(RELEASE);
}

void przod_lewo(){
  motor3.run(RELEASE);;
  motor4.run(FORWARD);
  motor4.setSpeed(120);
}

void przod_prawo(){
  motor3.run(FORWARD);
  motor3.setSpeed(120);
  motor4.run(RELEASE);
}


void zatrzymaj() {
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}


void loop() {
  Key21 command = irController.getKey();
  if (command != Key21::NONE) {
    switch (command) {
      case Key21::KEY_CH_MINUS:
        Serial.println("CH-");
        break;

      case Key21::KEY_CH:
        Serial.println("CH");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_CH_PLUS:
        Serial.println("CH+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_PREV:
        Serial.println("<<");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_NEXT:
        Serial.println(">>");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_PLAY_PAUSE:
        Serial.println(">||");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_VOL_MINUS:
        Serial.println("–");
        parkowanie_lewo();
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("+");
        parkowanie();
        break;

      case Key21::KEY_EQ:
        Serial.println("EQ");
        parkowanie_prawo();
        break;

      case Key21::KEY_100_PLUS:
        Serial.println("100+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_200_PLUS:
        Serial.println("200+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_0:
        Serial.println("0");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_1:
        Serial.println("1");
        przod_lewo();
        break;

      case Key21::KEY_2:
        Serial.println("2");
        do_przodu();
        break;

      case Key21::KEY_3:
        Serial.println("3");
        przod_prawo();
        break;

      case Key21::KEY_4:
        Serial.println("4");
        lewo();
        break;

      case Key21::KEY_5:
        Serial.println("5");
        zatrzymaj();
        break;

      case Key21::KEY_6:
        Serial.println("6");
        prawo();
        break;

      case Key21::KEY_7:
        Serial.println("7");
        tyl_lewo();
        break;

      case Key21::KEY_8:
        Serial.println("8");
        do_tylu();
        break;

      case Key21::KEY_9:
        Serial.println("9");
        tyl_prawo();
        break;

      default:
        Serial.println("WARNING: undefined command:");
        break;
    }
  }
}