#include <Interbot/Interbot.h>

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

// Ma version plus poussee
void implementation_reference()
{
    auto visiterBoites = [](Cote cote, auto&& func)
    {
        for (auto i = 0; i < 2; ++i)
        {
            allerBoite(cote);
            auto test = func();
            // if (test)
            // {
            //     robot.allumerEteindreDel(true);
            // }
            robot.attendre(1s);
            robot.allumerEteindreDel(false);
            revenirBoite(cote);
        }
    };
    //robot.avancerJusquaLigne();
    robot.tourner(Cote::DROITE);
    visiterBoites(Cote::GAUCHE, [] { return robot.lumiereAllumee(); });
    visiterBoites(Cote::DROITE, [] { return robot.estHumide(); });
    visiterBoites(Cote::GAUCHE, [] { return robot.pluieEnCours(); });
}

void faireParcours()
{
    // implementation_attendue();
    implementation_reference();
}

#endif // FACILE
