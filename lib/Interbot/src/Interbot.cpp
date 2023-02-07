#include "Interbot/Interbot.h"
#include "Arduino.h"
#include "Interbot/Direct.h"

Robot robot;


// Toujours public
Robot::Robot() : moteurGauche{Cote::GAUCHE}, moteurDroit{Cote::DROITE} {}

bool Robot::detecterLigneGauche()
{
    if (digitalRead(PIN_SDL_GAUCHE) < SdlValeur)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::detecterLigneMilieu()
{
    if (digitalRead(PIN_SDL_MILIEU) < SdlValeur)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::detecterLigneDroite()
{
    if (digitalRead(PIN_SDL_DROITE) < SdlValeur)
    {
        return true;
    }
    else
    {
        return false;
    }
}


long convertionMsCm(long microseconds)
{
    return microseconds / 29 / 2;
}

long Robot::detecterObjet()
{
    long dureePulse, distanceCentimetre;
    pinMode(SONAR_PIN_OUTPUT, OUTPUT);
    digitalWrite(SONAR_PIN_OUTPUT, LOW);
    delayMicroseconds(2);
    digitalWrite(SONAR_PIN_OUTPUT, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_PIN_OUTPUT, LOW);

    pinMode(SONAR_PIN_INPUT, INPUT);
    dureePulse = pulseIn(SONAR_PIN_INPUT, HIGH);
    distanceCentimetre = convertionMsCm(dureePulse);

    return distanceCentimetre;
}

void Robot::tourner(Cote cote)
{
    // TODO
}
bool Robot::lumiereAllumee() const
{
    int sensorValue = analogRead(PIN_LUM_DETECTEUR); 
    float resistance = (float)(1023.0-sensorValue)*10.0/sensorValue;
    if(resistance>SeuilLumiere)
    {
        digitalWrite(PIN_LUM_CAP_DEL,HIGH);
    }
    else
    {
        digitalWrite(PIN_LUM_CAP_DEL,LOW);
    }
}
bool Robot::estHumide() const
{
    if (analogRead(PIN_HUMIDITE) > SeuilHumidite)
        return true;
        
    return false;
}
bool Robot::pluieEnCours() const
{
    // TODO
    return false;
}
void Robot::allumerEteindreDel(bool entree)
{
    if (entree)
        digitalWrite(PIN_SIMPLE_DEL, HIGH);
    else
        digitalWrite(PIN_SIMPLE_DEL, LOW);
}

void Robot::attendre(secondes s)
{
    delay(s.valeur*1000);
}
void Robot::demiTour()
{
    // TODO
}

// Moyen-niveau


// #include "LowLevel.hpp"

// #include "Direct.hpp"

// using namespace low_level;

// Interbot::Interbot() : m_leftMotor(Motor::Side::Left), m_rightMotor(Motor::Side::Right)
// {}

// bool Interbot::init()
// {
//     return static_cast<bool>(direct::controller.begin());
// }

// const Interbot::Battery& Interbot::getBattery()
// {
//     return m_battery;
// }

// float Interbot::Battery::getVoltage() const
// {
//     return direct::battery.getRaw() / 77.0f;
// }

// Interbot::Motor& Interbot::getLeftMotor()
// {
//     return m_leftMotor;
// }

// Interbot::Motor& Interbot::getRightMotor()
// {
//     return m_rightMotor;
// }

// void Interbot::Motor::setSpeed(float speed)
// {
//     auto motor = [this] { return m_side == Side::Left ? direct::M1 : direct::M2; }();
//     auto naturalDirectionScale = [this] { return m_side == Side::Left ? 1.0f : -1.0f;
//     }(); m_speed = speed;

//     // TODO
//     int pwm = static_cast<int>(abs(speed * 255.0f));
//     motor.setDuty(pwm);
// }

// float Interbot::Motor::getSpeed() const
// {
//     return m_speed;
// }

// Interbot::Motor::Direction Interbot::Motor::getDirection() const
// {
//     return m_speed > 0.0f ? Direction::Forward : Direction::Backward;
// }

// void Interbot::Motor::stop()
// {
//     setSpeed(0.0f);
// }

Robot::Moteur::Moteur(Cote cote) : m_cote(cote) {}

// const Interbot::LightSensor& Interbot::getLightSensor() const
// {
//     return m_lightSensor;
// }

// const Interbot::MoistureSensor& Interbot::getMoistureSensor() const
// {
//     return m_moistureSensor;
// }

// const Interbot::RainSensor& Interbot::getRainSensor() const
// {
//     return m_rainSensor;
// }
