# Dual-Mode-Servo-Controller.
Arduino-based joystick-controlled SG90 servo motor with HC-SR04 ultrasonic obstacle detection. Automatically blocks servo movement when an obstacle is detected within threshold distance and uses an LED as a warning indicator.
# Joystick-Controlled SG90 Servo Motor with Ultrasonic Obstacle Detection

## Project Overview

This project uses an Arduino Uno to control an SG90 servo motor through a joystick while monitoring nearby obstacles using an HC-SR04 ultrasonic sensor. When an obstacle is detected within the predefined safety distance of 5 cm, the Arduino blocks further servo movement and turns on an LED indicator.

The system demonstrates manual actuator control, ultrasonic distance measurement, and automatic obstacle-based movement blocking.

## Objectives

- Control the angular position of an SG90 servo motor using a joystick.
- Measure the distance to nearby objects using an HC-SR04 ultrasonic sensor.
- Automatically block servo movement when an obstacle is detected within 5 cm.
- Provide a visual warning using an LED.
- Implement a simple embedded control system using Arduino.

## Components Required

- Arduino Uno
- SG90 positional servo motor
- HC-SR04 ultrasonic sensor
- Analog joystick module
- LED
- 220 Ω resistor
- Breadboard
- Jumper wires
- USB cable for programming
- Regulated 5 V external power supply for the servo, if required

## Pin Connections

| Component Pin | Arduino Connection |
|---|---|
| Joystick VCC | 5V |
| Joystick GND | GND |
| Joystick VRx | A0 |
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| HC-SR04 TRIG | D3 |
| HC-SR04 ECHO | D4 |
| SG90 Signal | D9 |
| SG90 VCC | Regulated 5V supply |
| SG90 GND | Common GND |
| LED Anode (+) | D6 through a 220 Ω resistor |
| LED Cathode (−) | GND |

**Note:** The joystick's VRy and SW pins are not used in the current program. All components must share a common ground. Use an appropriate external supply for the servo when necessary.

## Working Principle

1. The joystick provides analog input to the Arduino.
2. The Arduino converts the joystick reading into a target servo angle.
3. The HC-SR04 measures the distance to an object using ultrasonic waves.
4. If a valid distance reading is below 5 cm, the Arduino holds the last commanded servo position and switches on the LED.
5. When the obstacle is no longer detected within the safety threshold, the LED turns off and joystick control resumes.

## Software Requirements

- Arduino IDE
- Arduino Uno board support (Arduino AVR Boards)
- Servo library by Arduino

The joystick, ultrasonic sensor, and LED are controlled using built-in Arduino functions.

## Applications

- Educational robotics
- Obstacle-aware robotic mechanisms
- Basic automated positioning systems
- Embedded systems and sensor-actuator experiments

## Limitations

- The HC-SR04 detects obstacles only within its sensing area.
- Ultrasonic readings at very short distances can be unreliable.
- A standard SG90 servo cannot guarantee an instantaneous emergency stop.
- The current program blocks all movement while an obstacle is detected; it does not independently verify whether reverse movement is safe.

This project is an educational prototype and is not intended to replace certified safety systems.

## Future Improvements

- Add directional movement blocking to allow controlled movement away from obstacles.
- Improve sensor filtering and obstacle detection reliability.
- Add a buzzer for audible alerts.
- Develop a more robust mechanical mounting system for the sensor.
- Explore additional sensors for wider obstacle coverage.

## Conclusion

This project demonstrates how an Arduino can combine joystick input, ultrasonic sensing, and servo control to create a simple obstacle-aware motion system. It provides practical experience in embedded programming, sensor integration, actuator control, and basic automation.

## License

This project is intended for educational and learning purposes.
