#include "Interbot/Direct.h"

#include <Arduino.h>

// Prototype pour la fonction qui sera définie par l'utilisateur
void faireParcours();

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
        etat = Etat::ARRET_URGENCE;
        return;
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Hello World!");
    // put your setup code here, to run once:

    // bot.init();
    // attach interrupt bouton
    attachInterrupt(digitalPinToInterrupt(direct::PIN_BOUTON_INTERRUPT), boutonISR,
                    FALLING);
    etat = Etat::ATTENTE_BOUTON;
}

void loop()
{
    if (etat < Etat::DEPART_PARCOURS)
    {
        // En attente du bouton
        return;
    }
    if (etat >= Etat::PARCOURS_TERMINE)
    {
        // On est en arrêt d'urgence ou on a terminé le parcours
        // On recommence à attendre le bouton
        etat = Etat::ATTENTE_BOUTON;
        return;
    }

    faireParcours();
}
