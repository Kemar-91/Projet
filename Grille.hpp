#ifndef GRILLE_HPP_INCLUDED
#define GRILLE_HPP_INCLUDED

#include "Coord.hpp"
#include "Place.hpp"

const int NBLIGNE = 20;
const int NBCASE = NBLIGNE * NBLIGNE;

struct Grille{
    Place listePlace[NBCASE];
};

void chargerGrilleVide( Grille &g);

void chargerPlace( Grille g, Coord c, Place &p);

void rangerPlace(Grille &g, Place p);

void placerNid(Grille &g, EnsCoord ec);

void placeSucre(Grille &g, EnsCoord ec);

void placerFourmi(Grille &g, ensFourmi ef);

void lineariserPheroNid(Grille &g);

void initialiserGrille(Grille &g, ensFourmi ef, EnsCoord sucre, EnsCoord nid);

void diminuerPheroSucreGrille(Grille &g);

void afficheGrille(Grille g);

#endif // GRILLE_HPP_INCLUDED
