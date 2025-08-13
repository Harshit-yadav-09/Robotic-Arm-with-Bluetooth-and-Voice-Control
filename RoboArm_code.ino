#include <Servo.h>

// Define servo objects for each part of the robotic arm
Servo baseServo;      // Base rotation
Servo shoulderServo;  // Shoulder joint
Servo elbowServo;     // Elbow joint
Servo wristServo;     // Wrist rotation
Servo gripperServo;   // Gripper open/close

// Assign pins for each servo (adjust these based on your actual wiring)
const int basePin = 8;
const int shoulderPin = 9;
const int elbowPin = 10;
const int wristPin = 11;
const int gripperPin = 12;

void setup() {
  // Initialize serial communication for Bluetooth module (e.g., HC-05 at 9600 baud)
  Serial.begin(9600);

  // Attach servos to their respective pins
  baseServo.attach(basePin);
  shoulderServo.attach(shoulderPin);
  elbowServo.attach(elbowPin);
  wristServo.attach(wristPin);
  gripperServo.attach(gripperPin);

  // Optional: Set initial positions (e.g., all to 90 degrees or home position)
  baseServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(90);
  wristServo.write(90);
  gripperServo.write(0);  // Closed by default
}

void loop() {
  // Check if data is available from Bluetooth
  if (Serial.available() > 0) {
    char command = Serial.read();  // Read the incoming command character

    // Process the command
    switch (command) {
      case 'A':  // OPEN gripper (from button)
        gripperServo.write(180);  // Adjust angle for open position
        break;
      case 'B':  // CLOSE gripper (from button)
        gripperServo.write(0);    // Adjust angle for closed position
        break;
      case 'C':  // W_LEFT (wrist left, from button)
        wristServo.write(0);      // Adjust angle for left position
        break;
      case 'D':  // W_CENTRE (wrist center, from button)
        wristServo.write(90);     // Center position
        break;
      case 'E':  // Possible E0 (elbow 0, if used in some blocks)
        elbowServo.write(0);
        break;
      case 'F':  // W_REVERSE (wrist reverse, from button)
        wristServo.write(180);    // Reverse position
        break;
      case 'G':  // W180 (wrist 180, from button)
        wristServo.write(180);
        break;
      case 'H':  // W0 (wrist 0, from button) or ELBOW at 0 (from voice) - Note: overlap, assuming elbow for voice priority
        elbowServo.write(0);
        break;
      case 'I':  // Wn180 (wrist -180 or alternate, from button) - Servos are 0-180, so mapping to 0 or custom
        wristServo.write(0);      // Adjust as needed
        break;
      case 'J':  // E0 or E45 (elbow 45 from voice, but button may differ) - Assuming 45
        elbowServo.write(45);
        break;
      case 'K':  // E45 or E90 (elbow 90 from voice)
        elbowServo.write(90);
        break;
      case 'L':  // E90 (elbow 90 or 135, from button)
        elbowServo.write(90);     // Adjust if different
        break;
      case 'M':  // E135 (elbow 135, from button/voice)
        elbowServo.write(135);
        break;
      case 'N':  // E180 (elbow 180, from button/voice)
        elbowServo.write(180);
        break;
      case 'O':  // S30 (shoulder 30, from button)
        shoulderServo.write(30);
        break;
      case 'P':  // S60 (shoulder 60, from button)
        shoulderServo.write(60);
        break;
      case 'Q':  // S90 (shoulder 90, from button)
        shoulderServo.write(90);
        break;
      case 'R':  // S120 (shoulder 120, from button)
        shoulderServo.write(120);
        break;
      case 'S':  // S150 (shoulder 150, from button)
        shoulderServo.write(150);
        break;
      case 'T':  // B0 (base 0, from button/voice)
        baseServo.write(0);
        break;
      case 'U':  // B90 (base 90, from button/voice)
        baseServo.write(90);
        break;
      case 'V':  // B180 (base 180, from button/voice)
        baseServo.write(180);
        break;
      case 'X':  // DEFAULT (from button/voice) - Reset to default positions
        baseServo.write(90);
        shoulderServo.write(90);
        elbowServo.write(90);
        wristServo.write(90);
        gripperServo.write(0);
        break;
      case 'Y':  // STOP (from button/voice) - Optional: could detach servos or hold position
        // For simplicity, do nothing or reset to default
        baseServo.write(baseServo.read());  // Hold current
        // Alternatively: detach() if you want to stop powering
        break;
      default:
        // Unknown command - do nothing or send error back via Serial
        Serial.println("Unknown command");
        break;
    }
  }
}