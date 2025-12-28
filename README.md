# AntBot Robot Controller - Arduino Sketches

Arduino code for controlling a tank-tread robot with Bluetooth, ultrasonic sensor, and servo-mounted camera tilt.

## Hardware
- Arduino Uno
- L298N motor driver
- HC-05 Bluetooth module
- HC-SR04 ultrasonic sensor
- Servo motor (tilt mechanism)
- 4x DC motors (tank treads, wired in pairs)
- 7.4V 2S LiPo battery

## Pin Assignments
**Motors (L298N):**
- IN1 → Pin 5
- IN2 → Pin 6
- IN3 → Pin 10
- IN4 → Pin 11
- ENA → Pin 9
- ENB → Pin 4

**Bluetooth (HC-05):**
- TX → Pin 2 (Arduino RX via SoftwareSerial)
- RX → Pin 3 (Arduino TX via SoftwareSerial)

**Servo:**
- Signal → Pin 7

**Ultrasonic Sensor (HC-SR04):**
- Trig → Pin 8
- Echo → Pin 12

## Sketches
- `integrated/` - Full robot controller (motors + servo + sensor + Bluetooth)
- `motor_test/` - Basic motor testing
- `servo_test/` - Servo tilt testing
- `sensor_test/` - Ultrasonic distance measurement

## Bluetooth Commands
Send via serial at 9600 baud:

- `F<speed>` - Forward (e.g., `F200`)
- `B<speed>` - Backward
- `L<speed>` - Turn left
- `R<speed>` - Turn right
- `STOP` - Stop all motors
- `S<angle>` - Servo tilt (e.g., `S90` for center)

## Sensor Data
Arduino sends distance readings every 500ms:
- Format: `D:<inches>` (e.g., `D:15`)

## Setup
1. Wire components according to pin assignments
2. Upload `integrated/integrated.ino` to Arduino Uno
3. Pair HC-05 Bluetooth module (default PIN: 1234)
4. Connect via serial terminal or companion Android app

## Companion App
Android control app available in separate repository.

## License
MIT License - See LICENSE file
