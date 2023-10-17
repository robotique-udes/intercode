#include "Interbot/Direct.h"
#include "Interbot/Interbot.h"
#include <Arduino.h>
#include <ArduinoMotorCarrier.h>

void demonstrationMoteurs();
void faireParcours();

static float batteryVoltage;
// low battery limit (discharged)
static float batteryLimit;
// Variable to change the motor speed and direction
int duty = -15;

Robot robot1;

enum class Etat
{
    INIT,
    ATTENTE_BOUTON,
    DEPART_PARCOURS,
    PARCOURS_EN_COURS,
    PARCOURS_TERMINE,
    ARRET_URGENCE
};
volatile Etat etat = Etat::INIT;

void boutonISR()
{
    if (etat == Etat::ATTENTE_BOUTON)
    {
        etat = Etat::DEPART_PARCOURS;
        return;
    }

    if (etat == Etat::PARCOURS_EN_COURS || etat == Etat::DEPART_PARCOURS)
    {
        Serial.println("Le parcourt est terminé");
        etat = Etat::ARRET_URGENCE;
        return;
    }
}

void setup()
{
    delay(500);
    pinMode(PIN_MOTEUR_GAUCHE_DIRECTION, OUTPUT);
    pinMode(PIN_MOTEUR_GAUCHE_VITESSE, OUTPUT);
    pinMode(PIN_MOTEUR_DROITE_DIRECTION, OUTPUT);
    pinMode(PIN_MOTEUR_DROITE_VITESSE, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(13, OUTPUT);
    batteryLimit = 6; // Around 9V for a 3S LiPo battery
    Serial.begin(9600);
}

bool b = false;

void loop()
{
    if (robot.detecterObjet()> 50 )
    {
        robot.avancer(50);
    }
    if(robot.detecterLigneDroite())
    {
        robot.tourner(Cote::DROITE);
    }

    
    
}