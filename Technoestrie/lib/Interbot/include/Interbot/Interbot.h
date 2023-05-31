#pragma once
#include "Interbot/Direct.h"
#include "Interbot/Utils.h"
//#include "Config.h"

struct secondes
{
    double valeur;
};

struct centimetre
{
    double valeur;
};

enum class EmplacementCapteur
{
    GAUCHE,
    MILIEU,
    DROITE
};
/*
Enumeration de luminosité
*/
enum class Lumiere
{
    Haute,
    Moyenne,
    Basse,
    Eteinte
};
enum class Cote
{
    GAUCHE,
    DROITE
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"
inline secondes operator""s(long double s)
{
    return secondes{static_cast<double>(s)};
}
inline secondes operator""s(unsigned long long s)
{
    return secondes{static_cast<double>(s)};
}
#pragma GCC diagnostic pop

#if defined(MOYEN)
    #define HAUT_NIVEAU  private
    #define MOYEN_NIVEAU public
    #define BAS_NIVEAU   public
#elif defined(DIFFICILE)
    #define HAUT_NIVEAU  private
    #define MOYEN_NIVEAU private
    #define BAS_NIVEAU   public
#else
    #define HAUT_NIVEAU  public
    #define MOYEN_NIVEAU private
    #define BAS_NIVEAU   private
#endif

// Suiveur de ligne //
#define PIN_MOTEUR_GAUCHE_DIRECTION 2
#define PIN_MOTEUR_GAUCHE_VITESSE 3
#define PIN_MOTEUR_DROITE_VITESSE 5
#define PIN_MOTEUR_DROITE_DIRECTION 4



// Suiveur de ligne //

#define PIN_SDL_DROITE A6 // Left Sensor on Analog Pin 2
#define PIN_SDL_GAUCHE A5 // Right Sensor on Analog Pin 1
#define PIN_SDL_MILIEU A7 // Middle Sensor on Analog Pin 0
#define SdlValeur 600 // Le capteur detecte une ligne lorque la valeur est superieur

// Sonar //

#define SONAR_PIN_INPUT 7
#define SONAR_PIN_OUTPUT 8

// Simple DEL //

#define PIN_SIMPLE_DEL 5

// Capteur de lumiere //

#define HauteLumiere 700
#define MoyenneLumiere 500
#define BasseLumiere 200

// capteur d'humidite //

#define PIN_HUMIDITE A1
#define SeuilHumidite 400

// capteur d'eau //

#define PIN_CAPTEUR_EAU A2
#define SeuilPluie 200

// donnees de deplacement //

#define VitesseMoteur 15
#define DelaisPourTourner 1000

//#ifdef ADVANCED
class Robot
{
public:
    Robot();
    // clang-format off

HAUT_NIVEAU:
    ;
    // clang-format on
    /*
        Cette fonction utilise le sonar pour détecter un objet. Elle retourne la distance en centimetres.
        @return Distance en centimetres
    */
    long detecterObjet();
    /*
    Cette fonction permet de faire avancer le robot.
    @param Le pourcentage de vitesse à utiliser
    @return void
    */
    void avancer(int PourcentageVitesse); // Changer pour mettre une distance
    /*
    Cette fonction permet de faire reculer le robot.
    @return void
    */
    void reculer(int PourcentageVitesse);
    /*
    Cette fonction permet d'arrêter le robot.
    @return void
    */
    void arreter();
    /*
    Cette fonction utilise les capteurs de ligne pour détecter une ligne. Elle retourne true si une ligne est détectée.
    @param capteur Le capteur à utiliser
    @return true si une ligne est détectée
    */
    bool detecterLigne(EmplacementCapteur capteur); 
    /*
    Cette fonction utilise les capteurs de ligne pour détecter une ligne. Elle retourne true si une ligne est détectée.
    @return true si une ligne est détectée
    */
    bool detecterLigneDroite(); /* Utiliser une seule fonction pour les trois*/
    bool detecterLigneMilieu();
    bool detecterLigneGauche();
    /*
    Cette fonction permet de tourner le robot sur lui-même.
    @param cote Le côté sur lequel le robot doit tourner
    */
    void tourner(Cote cote);
    // uint32_t obtenirLuminosite();
    /*Cette fonction détecte si une lumière est allumée.
    @return Luminosité
    */
    Lumiere detecterLumiere() const;
    /* 
    Cette fonction détecte si il y a de l'eau.
    @return true si il y a de l'eau
    */
    bool estHumide() const;
    // uint32_t obtenirHumidite();
    bool pluieEnCours() const;
    void allumerEteindreDel(bool entree);
    /*
        Cette fonction permet de faire attendre le robot.
        @param s Le nombre de secondes à attendre
        @return void
    */
    void attendre(secondes s);
    void demiTour();
    void sonor (int frequence, int duree);

    // clang-format off
MOYEN_NIVEAU:
    ;
    // clang-format on
    class Batterie
    {
        float getTension() const;
    };
    class Moteur
    {
        enum class Sens
        {
            Avant,
            Arriere
        };

        void setVitesse(float vitesse);
        float getVitesse() const;
        Sens getSens() const;
        void arreter();

    private:
        float m_vitesse;
        Cote m_cote;
        Moteur(Cote cote);
        friend class Robot;
    };
    Moteur moteurGauche;
    Moteur moteurDroit;
    class CapteurLumiere
    {
    public:
        float getLuminosite() const;
    };
    CapteurLumiere capteurLumiere;

    class CapteurPluie
    {
    public:
        CapteurPluie() : m_pin{PinMode::INPUT} {}
        bool isPluie() const;

    private:
        Pin<0> m_pin;
    };
    CapteurPluie capteurPluie;

    class CapteurHumidite
    {
    public:
        float getHumidite() const;
    };
    CapteurHumidite capteurHumidite;
};
extern Robot robot;
//#endif

//#ifdef SIMPLE
class RobotFacile
{
public:
    RobotFacile();
    // clang-format off

HAUT_NIVEAU:
    ;
    // clang-format on
    void avancer();
    void arreter();
    void AvancerDistanceCm(centimetre distance);
    void AvancerJusquaObjet();
    long DistanceObjet();
    void AvancerJusqualigne();
    void tourner(Cote cote);
    uint32_t obtenirLuminosite();
    bool lumiereAllumee() const;
    bool estHumide() const;
    uint32_t obtenirHumidite();
    bool pluieEnCours() const;
    void allumerDel();
    void eteindreDel();
    void attendre(secondes s);
    void demiTour();

    // clang-format off
MOYEN_NIVEAU:
    ;
    // clang-format on
    class Batterie
    {
        float getTension() const;
    };
    class Moteur
    {
        enum class Sens
        {
            Avant,
            Arriere
        };

        void setVitesse(float vitesse);
        float getVitesse() const;
        Sens getSens() const;
        void arreter();

    private:
        float m_vitesse;
        Cote m_cote;
        Moteur(Cote cote);
        friend class Robot;
    };
    Moteur moteurGauche;
    Moteur moteurDroit;
    class CapteurLumiere
    {
    public:
        float getLuminosite() const;
    };
    CapteurLumiere capteurLumiere;

    class CapteurPluie
    {
    public:
        CapteurPluie() : m_pin{PinMode::INPUT} {}
        bool isPluie() const;

    private:
        Pin<0> m_pin;
    };
    CapteurPluie capteurPluie;

    class CapteurHumidite
    {
    public:
        float getHumidite() const;
    };
    CapteurHumidite capteurHumidite;
};
//#endif

// class Batterie
// {
//     float getTension() const;
// };


// class CapteurLumiere
// {
//     float getLuminosite() const;
// };

// class CapteurPluie
// {
//     bool isPluie() const;
// };

// class CapteurHumidite
// {
//     float getHumidite() const;
// };

// class Interbot
// {
// public:
//     struct LightSensor
//     {
//         float getIntensity() const;
//     };

//     class MoistureSensor
//     {
//         float getMoisture() const;
//     };

//     class RainSensor
//     {
//     public:
//         bool init();
//         bool isRaining() const;

//     private:
//         bool m_initialise = false;
//         static constexpr int M_PIN = 2;
//     };

//     struct Del
//     {
//         bool isOn() const;
//         void turnOn();
//         void turnOff();
//         void setOn(bool on);

//     private:
//         bool m_isOn;
//     };

//     struct Button
//     {
//         bool isPressed() const;
//         // void attachInterrupt(void (*callback)());
//     };

//     LightSensor& getLightSensor();

//     Interbot();

//     bool init();

//     const Battery& getBattery();
//     Motor& getLeftMotor();
//     Motor& getRightMotor();
//     const LightSensor& getLightSensor() const;
//     const MoistureSensor& getMoistureSensor() const;
//     const RainSensor& getRainSensor() const;
//     Del& getDel();

// private:
//     Battery m_battery;
//     Motor m_leftMotor;
//     Motor m_rightMotor;
//     LightSensor m_lightSensor;
//     MoistureSensor m_moistureSensor;
//     RainSensor m_rainSensor;
// };