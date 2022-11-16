#pragma once
#include "INterbot/Direct.h"

struct seconds
{
    double value;
};
seconds operator""s(long double s)
{
    return seconds{static_cast<double>(s)};
}
seconds operator""s(unsigned long long s)
{
    return seconds{static_cast<double>(s)};
}

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
    enum class Cote
    {
        Gauche,
        Droit
    } m_cote;
    Moteur(Cote cote);
};

class CapteurLumiere
{
    float getLuminosite() const;
};

class CapteurPluie
{
    bool isPluie() const;
};

class CapteurHumidite
{
    float getHumidite() const;
};

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
