#pragma once
#include <Arduino.h>

template <pin_size_t M_PIN>
class Pin
{
public:
    Pin(PinMode mode) { pinMode(M_PIN, mode); }
    void setMode(PinMode mode) { pinMode(M_PIN, mode); }
    void write(PinStatus status) { digitalWrite(M_PIN, status); }
    PinStatus read() const { return digitalRead(M_PIN); }
};

template <pin_size_t M_PIN>
class AnalogPin : public Pin<M_PIN>
{
public:
    int analogRead() const override { return analogRead(M_PIN); }
};
