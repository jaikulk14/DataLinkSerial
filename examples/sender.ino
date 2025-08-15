#include <SerialLink.h>

SerialLink link(Serial);

void setup() {
  link.begin(); // default baud 115200
}

void loop() {
  link.send("temp", random(20, 30)); // send random temperature
  link.send("led", "ON");            // send LED state
  delay(1000);
}
