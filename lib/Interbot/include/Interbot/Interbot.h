#pragma once
#include "Interbot/Direct.h"
#include "Interbot/Utils.h"

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

#define PIN_SDL_DROITE A1 // Left Sensor on Analog Pin 2
#define PIN_SDL_GAUCHE A2 // Right Sensor on Analog Pin 1
#define PIN_SDL_MILIEU A3 // Middle Sensor on Analog Pin 0
#define SdlValeur 600 // Le capteur detecte une ligne lorque la valeur est superieur

// Sonar //

#define SONAR_PIN_INPUT 3
#define SONAR_PIN_OUTPUT 4

// Simple DEL //

#define PIN_SIMPLE_DEL 5

// Capteur de lumiere //

#define PIN_LUM_CAP_DEL 6
#define PIN_LUM_DETECTEUR 7
#define SeuilLumiere 10

// capteur d'humidite //

#define PIN_HUMIDITE 8
#define SeuilHumidite 500

// capteur d'humidite //

#define PIN_CAPTEUR_EAU A0

// donnees de deplacement //

#define VitesseMoteur 15
#define DelaisPourTourner 1000



class Robot
{
public:
    Robot();
    // clang-format off

HAUT_NIVEAU:
    ;
    // clang-format on
    long detecterObjet();
    
    bool detecterLigne(EmplacementCapteur capteur); 
    bool detecterLigneDroite();
    bool detecterLigneMilieu();
    bool detecterLigneGauche();
    void tourner(Cote cote);
    // uint32_t obtenirLuminosite();
    bool lumiereAllumee() const;
    bool estHumide() const;
    // uint32_t obtenirHumidite();
    bool pluieEnCours() const;
    void allumerEteindreDel(bool entree);
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
extern Robot robot;

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



class RobotFacile
{
public:
    RobotFacile();
    // clang-format off

HAUT_NIVEAU:
    ;
    // clang-format on
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