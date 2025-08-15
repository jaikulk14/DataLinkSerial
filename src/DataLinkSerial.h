#ifndef SERIAL_LINK_H
#define SERIAL_LINK_H

#include <Arduino.h>
#include <map>
#include <functional>

class SerialLink {
public:
    typedef std::function<void(String)> Callback;

    SerialLink(HardwareSerial &serialPort);
    void begin(unsigned long baud = 115200);
    void send(const String &name, const String &value);
    void send(const String &name, float value);
    void send(const String &name, int value);
    void on(const String &name, Callback cb);
    void listen();

private:
    HardwareSerial &serial;
    String buffer;
    std::map<String, Callback> callbacks;
    void processLine(const String &line);
};

#endif
