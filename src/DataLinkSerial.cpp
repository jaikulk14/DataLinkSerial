#include "SerialLink.h"

SerialLink::SerialLink(HardwareSerial &serialPort) : serial(serialPort) {}

void SerialLink::begin(unsigned long baud) {
    serial.begin(baud);
    buffer.reserve(64);
}

void SerialLink::send(const String &name, const String &value) {
    serial.print(name);
    serial.print(":");
    serial.print(value);
    serial.print(";");
}

void SerialLink::send(const String &name, float value) {
    send(name, String(value, 2)); // send with 2 decimal places
}

void SerialLink::send(const String &name, int value) {
    send(name, String(value));
}

void SerialLink::on(const String &name, Callback cb) {
    callbacks[name] = cb;
}

void SerialLink::listen() {
    while (serial.available()) {
        char c = serial.read();
        if (c == ';') {
            processLine(buffer);
            buffer = "";
        } else {
            buffer += c;
        }
    }
}

void SerialLink::processLine(const String &line) {
    int sepIndex = line.indexOf(':');
    if (sepIndex > 0) {
        String key = line.substring(0, sepIndex);
        String value = line.substring(sepIndex + 1);
        if (callbacks.count(key)) {
            callbacks[key](value);
        }
    }
}
