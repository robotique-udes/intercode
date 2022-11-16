#include <Interbot/Interbot.h>

// Lib
enum class Cote
{
    GAUCHE,
    DROITE
};
void avancerJusquaLigne() {}
void avancerJusquaBoite() {}
void tourner(Cote) {}
// uint32_t obtenirLuminosite();
bool lumiereAllumee()
{
    return false;
}
bool estHumide()
{
    return false;
}
// uint32_t obtenirHumidite();
bool pluieEnCours()
{
    return false;
}
void allumerDel(bool) {}
void attendre(seconds) {}
void demiTour() {}

// Fait par les kids genre
void allerBoite(Cote s)
{
    avancerJusquaLigne();
    tourner(s);
    avancerJusquaBoite();
}
void revenirBoite(Cote s)
{
    demiTour();
    avancerJusquaLigne();
    tourner(s);
}

void implementation_attendue()
{
    avancerJusquaLigne();
    tourner(Cote::DROITE);
    for (auto i = 0; i < 2; ++i)
    {
        allerBoite(Cote::GAUCHE);
        auto lumiere = lumiereAllumee();
        if (lumiere)
        {
            allumerDel(true);
        }
        attendre(1s);
        allumerDel(false);
        revenirBoite(Cote::GAUCHE);
    }
    for (auto i = 0; i < 2; ++i)
    {
        allerBoite(Cote::DROITE);
        auto humide = estHumide();
        if (humide)
        {
            allumerDel(true);
        }
        attendre(1s);
        allumerDel(false);
        revenirBoite(Cote::DROITE);
    }
    for (auto i = 0; i < 2; ++i)
    {
        allerBoite(Cote::GAUCHE);
        auto pluie = pluieEnCours();
        if (pluie)
        {
            allumerDel(true);
        }
        attendre(1s);
        allumerDel(false);
        revenirBoite(Cote::DROITE);
    }
}

// Ma version plus poussee
void implementation_reference()
{
    auto visiterBoites = [](Cote cote, auto& func)
    {
        for (auto i = 0; i < 2; ++i)
        {
            allerBoite(cote);
            auto test = func();
            if (test)
            {
                allumerDel(true);
            }
            attendre(1s);
            allumerDel(false);
            revenirBoite(cote);
        }
    };
    avancerJusquaLigne();
    tourner(Cote::DROITE);
    visiterBoites(Cote::GAUCHE, lumiereAllumee);
    visiterBoites(Cote::DROITE, estHumide);
    visiterBoites(Cote::GAUCHE, pluieEnCours);
}

void faireParcours()
{
    // implementation_attendue();
    implementation_reference();
}
