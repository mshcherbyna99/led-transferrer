# LED Transferrer

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue.svg)](https://www.arduino.cc/)

## About The Project

LED Transferrer is a simple Arduino-based project that demonstrates optical data transmission using two LEDs (red and blue).
It converts a text string ("Test" in a code) into a binary code, adds CRC-8 for a data integrity, applies Manchester Encoding for reliable signal synchronization, and transmits the data by blinking the LEDs.

Red LED represents the first bit of each Manchester pair and the blue LED the second.

Key features:
- **Data Conversion**: Text to binary.
- **Error Detection**: CRC-8.
- **Encoding**: Manchester Encoding to ensure clock recovery (0 becomes [0,1], 1 becomes [1,0]).
- **Transmission Protocol**: Starts with 3 sync blinks (100ms on/off), sends data at 10ms per bit-pair, and ends with a 2-second pause.
- **Optimization**: Pre-computes binary data in `setup()` for efficiency; reserves vector memory to avoid reallocations.

Built with Arduino IDE, tested on ESP32-WROVER-KIT, but compatible with any board supporting digital outputs.

## Getting Started

### Prerequisites

- Arduino IDE.
- A microcontroller board (ESP32) with at least two GPIO pins available.
- Two LEDs (red and blue) with appropriate resistors (I have used 220Ω) to prevent damage.
- Breadboard and jumper wires for prototyping.

### Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/led-transferer.git
   ```
2. Open the project in Arduino IDE.
3. Install your required boards:
   - For ESP32: In Arduino IDE, go to `Tools > Board > Boards Manager`, search for "esp32" and install.
4. Connect your board via USB and select the correct board/port under `Tools > Board` and `Tools > Port`.

### Hardware Setup

- Connect the red LED to GPIO pin 4 (with resistor to GND).
- Connect the blue LED to GPIO pin 14 (with resistor to GND).
- Power the board via USB or external supply.
- (Optional) For receiving: Use photodiodes or a camera/phone app to detect blinks and decode.

Wiring Diagram:
```
Board Pin 4 --[220Ω]-- Red LED -- GND
Board Pin 14 --[220Ω]-- Blue LED -- GND
```

## Contributing

Contributions are welcome! Fork the repo, create a feature branch (`git checkout -b feature/AmazingFeature`), commit changes (`git commit -m 'Add some AmazingFeature'`), push (`git push origin feature/AmazingFeature`), and open a Pull Request.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.
