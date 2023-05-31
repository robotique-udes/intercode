#include <Arduino.h>
#include "interbot/Interbot.h"
#define FACILE

// Fait par les kids genre
#ifdef FACILE


void allerBoite(Cote s)
{
   // robot.avancerJusquaLigne();
    robot.tourner(s);
    //robot.avancerJusquaBoite();
}
void revenirBoite(Cote s)
{
    robot.demiTour();
    //robot.avancerJusquaLigne();
    robot.tourner(s);
}

void implementation_attendue()
{
    //robot.avancerJusquaLigne();
    robot.tourner(Cote::DROITE);
    for (auto i = 0; i < 2; ++i)
    {
        allerBoite(Cote::GAUCHE);
        // auto lumiere = robot.lumiereAllumee();
        // if (lumiere)
        // {
        //     robot.allumerEteindreDel(true);
        // }
        robot.attendre(1s);
        robot.allumerEteindreDel(false);
        revenirBoite(Cote::GAUCHE);
    }
    for (auto i = 0; i < 2; ++i)
    {
        allerBoite(Cote::DROITE);
        auto humide = robot.estHumide();
        if (humide)
        {
            robot.allumerEteindreDel(true);
        }
        robot.attendre(1s);
        robot.allumerEteindreDel(false);
        revenirBoite(Cote::DROITE);
    }
    for (auto i = 0; i < 2; ++i)
    {
        allerBoite(Cote::GAUCHE);
        auto pluie = robot.pluieEnCours();
        if (pluie)
        {
            robot.allumerEteindreDel(true);
        }
        robot.attendre(1s);
        robot.allumerEteindreDel(false);
        revenirBoite(Cote::DROITE);
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

void faireParcours()
{
    //Serial.println(robot.detecterObjet());
    digitalWrite(3,LOW);
    analogWrite(PIN_A1,100);
    while(1)
    {
        /*Serial.println("Test");
        Serial.println("LOW");
        digitalWrite(14,LOW);
        delay(10);
        Serial.println("HIGH");
        digitalWrite(14,HIGH);
        delay(10);*/
    }
   /*robot.avancer(50);
   if(robot.detecterLigne())
   {
    robot.arreter();
    robot.allumerEteindreDel(true); 
   }*/
}

#endif // FACILE
