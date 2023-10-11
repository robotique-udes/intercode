#include "Interbot/Interbot.h"
#include "Arduino.h"
#include "Interbot/Direct.h"


Robot robot;

// Toujours public
Robot::Robot() : moteurGauche{Cote::GAUCHE}, moteurDroit{Cote::DROITE} {}



void Robot::avancer(int PourcentageVitesse)
{
    int PWM = floor(PourcentageVitesse*255/100);
    if (PWM == 0)
        arreter();
    else if (PWM < 20)
        PWM = 20;

    if (PWM > 0){
        analogWrite(PIN_MOTEUR_GAUCHE_VITESSE,PWM);
        digitalWrite(PIN_MOTEUR_GAUCHE_DIRECTION,HIGH);
        analogWrite(PIN_MOTEUR_DROITE_VITESSE,PWM);
        digitalWrite(PIN_MOTEUR_DROITE_DIRECTION,HIGH);
    }
}

void Robot::reculer(int PourcentageVitesse)
{
    int PWM = floor(PourcentageVitesse*255/100);
    if (PWM == 0){
        arreter();
    }  
    else if (PWM < 20)
        PWM = 20;
    if (PWM > 0){
        analogWrite(PIN_MOTEUR_GAUCHE_VITESSE,PWM);
        digitalWrite(PIN_MOTEUR_GAUCHE_DIRECTION,LOW);
        analogWrite(PIN_MOTEUR_DROITE_VITESSE,PWM);
        digitalWrite(PIN_MOTEUR_DROITE_DIRECTION,LOW);
    }
    
}

void Robot::arreter()
{
    analogWrite(PIN_MOTEUR_GAUCHE_VITESSE,0);
    analogWrite(PIN_MOTEUR_DROITE_VITESSE,0);
}

/*
Le suiveur de ligne possede 3 capteurs (a gauche, au milieu et a droite). Pour suivre une ligne, il faut utiliser 
les fonctions detecterLigneGauche(), detecterLigneDroite() et detecterLigneMilieu(). Il suffit d'avancer lorsque 
la ligne est detectee sous le capteur du milieu, de tourner a gauche lorsque la ligne est detectee par le
capteur gauche et a droite lorsqu'elle est detectee par le capteur de droite. La fonction prend en parametre le 
capteur a observer. La valeur 1 est retournee si une ligne est detectee et 0 dans le cas contraire.
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
    if (analogRead(PIN_SDL_GAUCHE) < SdlValeur)
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
    if (analogRead(PIN_SDL_MILIEU) < SdlValeur)
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
    if (analogRead(PIN_SDL_DROITE) < SdlValeur)
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
    int PWM = 75;

    if (cote == Cote::DROITE)
    {
        analogWrite(PIN_MOTEUR_GAUCHE_VITESSE,PWM);
        analogWrite(PIN_MOTEUR_DROITE_VITESSE,0);
        digitalWrite(PIN_MOTEUR_GAUCHE_DIRECTION,HIGH);
        digitalWrite(PIN_MOTEUR_DROITE_DIRECTION,HIGH);
    }
    else
    {
        analogWrite(PIN_MOTEUR_GAUCHE_VITESSE,0);
        analogWrite(PIN_MOTEUR_DROITE_VITESSE,PWM);
        digitalWrite(PIN_MOTEUR_GAUCHE_DIRECTION,HIGH);
        digitalWrite(PIN_MOTEUR_DROITE_DIRECTION,HIGH);
    } 
    delay(1000);
    arreter();   
 }
/*
Retourne Allumer si la lumière est allumer
*/
Lumiere Robot::detecterLumiere() const
{
    int sensorValue = analogRead(A4);
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
    int PWM = 75;
    analogWrite(PIN_MOTEUR_GAUCHE_VITESSE,PWM);
    analogWrite(PIN_MOTEUR_DROITE_VITESSE,PWM);
    digitalWrite(PIN_MOTEUR_GAUCHE_DIRECTION,LOW);
    digitalWrite(PIN_MOTEUR_DROITE_DIRECTION,HIGH);

    delay(2000);
    arreter(); 
}


Robot::Moteur::Moteur(Cote cote) : m_cote(cote) {}


