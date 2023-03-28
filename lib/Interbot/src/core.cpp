#include "Interbot/Direct.h"
#include "Interbot/Interbot.h"
#include <Arduino.h>
#include <ArduinoMotorCarrier.h>

void demonstrationMoteurs();

static float batteryVoltage;
//low battery limit (discharged)
static float batteryLimit; 
//Variable to change the motor speed and direction
int duty = -15;

// Prototype pour la fonction qui sera définie par l'utilisateur
//void faireParcours();

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

// void setup()
// {
//     Serial.begin(115200);
//     Serial.println("Hello World!");
//     // put your setup code here, to run once:
    
//     // bot.init();
//     // attach interrupt bouton
//     attachInterrupt(digitalPinToInterrupt(direct::PIN_BOUTON_INTERRUPT), boutonISR,
//                     FALLING);
//     etat = Etat::ATTENTE_BOUTON;
//     pinMode(PIN_SDL_DROITE,INPUT);
//     pinMode(PIN_SDL_GAUCHE,INPUT);
//     pinMode(PIN_SDL_MILIEU,INPUT);
//     pinMode(PIN_SIMPLE_DEL, OUTPUT);
//     pinMode(PIN_LUM_CAP_DEL,OUTPUT);
    
// }
void setup()
{
  //Serial port initialization
  Serial.begin(115200);
  while (!Serial);

  

    // Reboot the motor controller; brings every value back to default
    Serial.println("reboot");
    delay(500);

 

    pinMode(PIN_MOTEUR_GAUCHE_AVANCER, OUTPUT);
    pinMode(PIN_MOTEUR_GAUCHE_RECULER, OUTPUT);
    pinMode(PIN_MOTEUR_DROITE_AVANCER, OUTPUT);
    pinMode(PIN_MOTEUR_DROITE_RECULER, OUTPUT);

  batteryLimit = 6; //Around 9V for a 3S LiPo battery

}

bool b = false;

void loop() {
    demonstrationMoteurs();
    while(1)
    {
    }
}

void demonstrationMoteurs(){
  secondes delai;
  delai.valeur = 2;
  Serial.println("Avancer");
  robot.avancer(50);
  robot.attendre(delai);
  Serial.println("Reculer");
  robot.reculer(50);
  robot.attendre(delai);
  Serial.println("Stop");
  robot.arreter();
  robot.attendre(delai);
  Serial.println("Demi-tour");
  robot.demiTour();
  robot.attendre(delai);
  Serial.println("Quart de tour");
  robot.tourner(Cote::DROITE);
}
      


    // if (etat < Etat::DEPART_PARCOURS)
    // {
    //     // En attente du bouton
    //     return;
    // }
    // if (etat >= Etat::PARCOURS_TERMINE)
    // {
    //     // On est en arret d'urgence ou on a termine le parcours
    //     // On recommence a attendre le bouton
    //     etat = Etat::ATTENTE_BOUTON;
    //     return;
    // }

    // faireParcours();

