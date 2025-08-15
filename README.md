# SerialLink

**SerialLink** makes Arduino-to-Arduino (or Arduino-to-ESP32) serial communication as easy as plugging in two wires.  

Just connect:
- **TX → RX**
- **RX → TX**
- **GND → GND**

and you're ready to send and receive named variables without manual `Serial.read()` parsing.

---

## Features
- Send and receive variables by name (no parsing needed)
- Works with Arduino, ESP32, ESP8266, Mega, Nano, etc.
- Automatically separates messages
- Supports `String`, `int`, and `float`

---

## Installation
1. Download this repository as a ZIP  
2. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library**  
3. Select the downloaded ZIP file  

---

## Example: Sender Board
```cpp
#include <SerialLink.h>

SerialLink link(Serial);

void setup() {
  link.begin(); // default baud rate 115200
}

void loop() {
  link.send("temp", random(20, 30));  // send random temperature
  link.send("led", "ON");             // send LED state
  delay(1000);
}
```
##Example: Reciever Board(Arduino or ESP32)
  ```cpp
#include <SerialLink.h>

SerialLink link(Serial);

void setup() {
  Serial.begin(115200);
  link.begin();

  link.on("temp", [](String value) {
    Serial.print("Temperature: ");
    Serial.println(value);
  });

  link.on("led", [](String value) {
    Serial.print("LED State: ");
    Serial.println(value);
  });
}

void loop() {
  link.listen(); // must be called to process incoming data
}
