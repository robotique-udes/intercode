#include "Interbot/Interbot.h"
#include "Arduino.h"
#include "Interbot/Direct.h"

Robot robot;



// Toujours public
Robot::Robot() : moteurGauche{Cote::GAUCHE}, moteurDroit{Cote::DROITE} {}

/*
Le suiveur de ligne possede 3 capteurs (a gauche, au milieu et a droite). Pour suivre une ligne, il suffit d'avancer droit 
lorsque la ligne est detectee sous le capteur du milieu, de tourner a gauche lorsque la ligne est detectee par le 
capteur gauche et a droite lorsqu'elle est detectee par le capteur de droite. La fonction prend en parametre le capteur 
a observer. La valeur 1 est retournee si une ligne est detectee et 0 dans le cas contraire.
*/
bool Robot::detecterLigne(EmplacementCapteur capteur)
{
    if ((capteur == EmplacementCapteur::GAUCHE && digitalRead(PIN_SDL_GAUCHE) < SdlValeur) ||
        (capteur == EmplacementCapteur::MILIEU && digitalRead(PIN_SDL_MILIEU) < SdlValeur) ||
        (capteur == EmplacementCapteur::DROITE && digitalRead(PIN_SDL_DROITE) < SdlValeur))
        return true;

    return false; 
}


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
    if(cote == Cote::GAUCHE)
    {
        M1.setDuty(-VitesseMoteur);
        M2.setDuty(VitesseMoteur);
    }
    else
    {
        M1.setDuty(VitesseMoteur);
        M2.setDuty(-VitesseMoteur);
    }
    delay(DelaisPourTourner);
    M1.setDuty(0);
    M2.setDuty(0);
    
}
/*
Retourne Allumer si la lumière est allumer
*/
Lumiere Robot::lumiereAllumee() const
{
    int sensorValue = analogRead(A0);
    if (sensorValue > HauteLumiere)
    {
         Serial.println("Lumiere haute");
        return Lumiere::Haute;
    }
    else if (sensorValue > MoyenneLumiere && sensorValue < HauteLumiere){
        Serial.println("Lumiere moyenne");
        return Lumiere::Moyenne;
    }
    else if (sensorValue > BasseLumiere && sensorValue < MoyenneLumiere)
     {
        Serial.println("Lumiere basse");
        return Lumiere::Basse;}
    else
    {
        Serial.println("Eteinte");
        return Lumiere::Eteinte;
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
    if(analogRead(PIN_CAPTEUR_EAU) < SeuilPluie)
        return true;
        
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
