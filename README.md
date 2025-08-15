# SerialLink

**SerialLink** makes Arduino-to-Arduino (or Arduino-to-ESP32) serial communication as easy as snapping two boards together.

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

## Combined Example

```cpp
#include <SerialLink.h>

// Change this to MODE_SENDER or MODE_RECEIVER
#define MODE_SENDER 1
#define MODE_RECEIVER 2
#define MODE MODE_SENDER  // <-- set here

SerialLink link(Serial);

void setup() {
  Serial.begin(115200);
  link.begin();

#if MODE == MODE_RECEIVER
  link.on("temp", [](String value) {
    Serial.print("Temperature: ");
    Serial.println(value);
  });

  link.on("led", [](String value) {
    Serial.print("LED State: ");
    Serial.println(value);
  });
#endif
}

void loop() {
#if MODE == MODE_SENDER
  link.send("temp", random(20, 30));  // send random temperature
  link.send("led", "ON");
  delay(1000);
#elif MODE == MODE_RECEIVER
  link.listen(); // must be called to process incoming data
#endif
}
