#include "Interbot/Direct.h"
#include "Interbot/Interbot.h"
#include <Arduino.h>
#include <Interbot/suiveurLigne.h>
#include <ArduinoMotorCarrier.h>


static float batteryVoltage;
//low battery limit (discharged)
static float batteryLimit; 
//Variable to change the motor speed and direction
int duty = 50;

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

  //Establishing the communication with the motor shield
  if (controller.begin())
  {
    Serial.print("MKR Motor Shield connected, firmware version ");
    Serial.println(controller.getFWVersion());
  }
  else
  {
    Serial.println("Couldn't connect! Is the red led blinking? You may need to update the firmware with FWUpdater sketch");
    while (1);
  }

  // Reboot the motor controller; brings every value back to default
  Serial.println("reboot");
  controller.reboot();
  delay(500);

  //Take the battery status
  float batteryVoltage = (float)battery.getRaw() / 77;
  Serial.print("Battery voltage: ");
  Serial.println(batteryVoltage);

  M1.setDuty(0);
  M2.setDuty(0);
  M3.setDuty(0);
  M4.setDuty(0);

  batteryLimit = 9.50; //Around 9V for a 3S LiPo battery

}

// void loop()
// {
//     Serial.print("Droite : ");
//     Serial.println(analogRead(PIN_SDL_DROITE));
//     Serial.print("Gauche : ");
//     Serial.println(analogRead(PIN_SDL_GAUCHE));
//     Serial.print("Milieu : ");
//     Serial.println(analogRead(PIN_SDL_MILIEU));
//     Serial.println("----------------- ");
//     delay(2000);
//     delay(200);
//     Serial.println("RunMotor");
    
//     M2.setDuty(50);
// }
void loop() {

  //Take the battery status
  batteryVoltage = (float)battery.getRaw() / 77;

  //Reset to the default values if the battery levels are lower than 11V
  if (batteryVoltage < batteryLimit)
  {
    Serial.println(" ");
    Serial.println("WARNING: LOW BATTERY");
    Serial.println("ALL SYSTEMS DOWN");
    M1.setDuty(0);
    M2.setDuty(0);
    M3.setDuty(0);
    M4.setDuty(0);
    while (batteryVoltage < batteryLimit) 
    {
      batteryVoltage = (float)battery.getRaw() / 77;
      controller.ping();
      //wait
      delay(50);
    }
  }
  else
  {
    //Motor test
    M1.setDuty(duty);
    delay(500);

    float batteryVoltage = (float)battery.getRaw() / 77;
    Serial.print("Battery voltage: ");
    Serial.println(batteryVoltage);

    //Keep active the communication MKR1000 & MKRMotorCarrier
    //Ping the samd11
    controller.ping();
    //wait
    delay(50);
  }
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

