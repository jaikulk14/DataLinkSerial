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
