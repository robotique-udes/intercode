#include "Interbot/Direct.h"
#include "Interbot/Interbot.h"
#include <Arduino.h>
#include <ArduinoMotorCarrier.h>

// Prototype pour la fonction qui sera définie par l'utilisateur
void faireParcours();

static float batteryVoltage;
//low battery limit (discharged)
static float batteryLimit; 

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
  //Serial port initialization
  Serial.begin(9600);
  while (!Serial);

    // Reboot the motor controller; brings every value back to default
    //Serial.println("reboot");
    delay(500);
    pinMode(PIN_MOTEUR_GAUCHE_DIRECTION, OUTPUT);
    pinMode(PIN_MOTEUR_GAUCHE_VITESSE, OUTPUT);
    pinMode(PIN_MOTEUR_DROITE_DIRECTION, OUTPUT);
    pinMode(PIN_MOTEUR_DROITE_VITESSE, OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(13, OUTPUT);
    batteryLimit = 6; //Around 9V for a 3S LiPo battery

}

bool b = false;

void loop() {
    faireParcours();
    // On éxecute la fonction faireParcours seulement une fois
    while(1)
    {

    }
}

