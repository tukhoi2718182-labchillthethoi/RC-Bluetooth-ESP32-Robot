#include <BluetoothSerial.h>
#include <ESP32Servo.h>

BluetoothSerial SerialBT;
Servo servo1, servo2, servo3, servo4, servo5;
int angleServo1 = 90, angleServo2 = 90, angleServo3 = 90, angleServo4 = 90, angleServo5 = 90;
unsigned long lastCommandTime = 0;
const unsigned long debounceDelay = 20; // Thời gian khử nhiễu (50ms)

// Chân điều khiển L298N
const int IN1 = 23;
const int IN2 = 22;
const int IN3 = 21;
const int IN4 = 19;

// Biến để theo dõi trạng thái động cơ
bool motorRunning = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Bluetooth"); // Tên Bluetooth của ESP32
  Serial.println("Bluetooth started!");

  // Thiết lập chân điều khiển động cơ
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Thiết lập servo
  servo1.attach(13);
  servo2.attach(12);
  servo3.attach(14);
  servo4.attach(27);
  servo5.attach(26);

  // Dừng động cơ ban đầu
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    unsigned long currentTime = millis();

    // Kiểm tra thời gian khử nhiễu
    if (currentTime - lastCommandTime >= debounceDelay) {
      lastCommandTime = currentTime;
      motorRunning = true;

      // Điều khiển động cơ
      if (command == 'a') {
        // Động cơ số 1 và số 2 quay theo chiều kim đồng hồ
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      } else if (command == 'b') {
        // Động cơ số 1 và số 2 quay ngược chiều kim đồng hồ
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      } else if (command == 'd') {
        // Động cơ số 1 quay ngược chiều kim đồng hồ, động cơ số 2 quay theo chiều kim đồng hồ
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      } else if (command == 'c') {
        // Động cơ số 1 quay theo chiều kim đồng hồ, động cơ số 2 quay ngược chiều kim đồng hồ
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      } else {
        motorRunning = false;
      }

      // Điều khiển servo số 1
      if (command == 'k') {
        angleServo1 = min(angleServo1 + 4, 180); // Điều chỉnh góc
        servo1.write(angleServo1);
      } else if (command == 'l') {
        angleServo1 = max(angleServo1 - 4, 0); // Điều chỉnh góc
        servo1.write(angleServo1);
      }

      // Điều khiển servo số 2
      if (command == 'q') {
        angleServo2 = min(angleServo2 + 4, 180); // Điều chỉnh góc
        servo2.write(angleServo2);
      } else if (command == 'w') {
        angleServo2 = max(angleServo2 - 4, 0); // Điều chỉnh góc
        servo2.write(angleServo2);
      }

      // Điều khiển servo số 3
      if (command == 'h') {
        angleServo3 = min(angleServo3 + 4, 180); // Điều chỉnh góc
        servo3.write(angleServo3);
      } else if (command == 'g') {
        angleServo3 = max(angleServo3 - 4, 0); // Điều chỉnh góc
        servo3.write(angleServo3);
      }

      // Điều khiển servo số 4
      if (command == 'i') {
        angleServo4 = min(angleServo4 + 4, 180); // Điều chỉnh góc
        servo4.write(angleServo4);
      } else if (command == 'f') {
        angleServo4 = max(angleServo4 - 4, 0); // Điều chỉnh góc
        servo4.write(angleServo4);
      }

      // Điều khiển servo số 5
      if (command == 'e') {
        angleServo5 = min(angleServo5 + 4, 180); // Điều chỉnh góc
        servo5.write(angleServo5);
      } else if (command == 'r') {
        angleServo5 = max(angleServo5 - 4, 0); // Điều chỉnh góc
        servo5.write(angleServo5);
      }
    }
  }

  // Dừng động cơ nếu không có lệnh điều khiển
  if (!motorRunning) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}
