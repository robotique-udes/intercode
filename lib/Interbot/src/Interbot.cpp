#include "Interbot/Interbot.h"

#include "Interbot/Direct.h"

Robot robot;

// Toujours public
Robot::Robot() : moteurGauche{Cote::GAUCHE}, moteurDroit{Cote::DROITE} {}

// Suiveur de lignes
int capteurDroit = 2; // Left Sensor on Analog Pin 2
int capteurGauche = 1; // Right Sensor on Analog Pin 1
int capteurMilieu = 0; // Middle Sensor on Analog Pin 0
const int whiteLvl = 600; // reading level is white if <600
const int blackLvl = 850; // reading level is black if >850

// Sonar
int SonarEntree = 3;
int SonarSortie = 4;

void setup()
{
    Serial.begin(9600);
    pinMode(capteurDroit,INPUT);
    pinMode(capteurGauche,INPUT);
    pinMode(capteurMilieu,INPUT);
}


// Haut-niveau
void Robot::avancerJusquaLigne()
{
}

bool Robot::detecterLigne()
{
    if (digitalRead(capteurDroit) < whiteLvl || digitalRead(capteurGauche)> whiteLvl || digitalRead(capteurMilieu) < whiteLvl)
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
    pinMode(SonarSortie, OUTPUT);
    digitalWrite(SonarSortie, LOW);
    delayMicroseconds(2);
    digitalWrite(SonarSortie, HIGH);
    delayMicroseconds(10);
    digitalWrite(SonarSortie, LOW);

    pinMode(SonarEntree, INPUT);
    dureePulse = pulseIn(SonarEntree, HIGH);
    distanceCentimetre = convertionMsCm(dureePulse);

    return distanceCentimetre;
}

void Robot::avancerJusquaBoite()
{
    // TODO
}
void Robot::tourner(Cote cote)
{
    // TODO
}
bool Robot::lumiereAllumee() const
{
    // TODO
    return false;
}
bool Robot::estHumide() const
{
    // TODO
    return false;
}
bool Robot::pluieEnCours() const
{
    // TODO
    return false;
}
void Robot::allumerDel(bool)
{
    // TODO
}
void Robot::attendre(secondes s)
{
    // TODO
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
