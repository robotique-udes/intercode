#pragma once

#include <Arduino.h>
#include <ArduinoMotorCarrier.h>
#include <stdint.h>
namespace direct
{
    extern mc::Battery& batterie;
    extern mc::MotorController& controlleur;
    extern mc::DCMotor& moteurGauche;
    extern mc::DCMotor& moteurDroit;

    // TODO: adjust values
    constexpr int PIN_CAPTEUR_PLUIE = 2;
    constexpr int PIN_CAPTEUR_LUMIERE = A0;
    constexpr int PIN_CAPTEUR_HUMIDITE = 3;
    constexpr int PIN_BOUTON_INTERRUPT = 4;
}
