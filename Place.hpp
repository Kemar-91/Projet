#ifndef PLACE_HPP_INCLUDED
#define PLACE_HPP_INCLUDED

#include "Coord.hpp"
#include "Fourmi.hpp"


struct Place{
    Coord c;
    int fourmi;
    bool sucre, nid;
    float pheroNid, pheroSucre;
};

Place creerPlaceVide(Coord c);

Coord coordPlace(Place p);
float pheroNidPlace(Place p);
float pheroSucrePlace(Place p);

int numFourmiPlace(Place p);
bool contientSucrePlace(Place p);
bool contientNidPlace(Place p);
bool surUnePistePlace(Place p);

void poserSucre(Place &p);
void poserNid(Place &p);
void poserFourmi(Fourmi &f, Place &p);
void enleverFourmi(Place &p);
void poserPheroNid(Place &p, float intensite);
void poserPheroSucre(Place &p);
void diminuerPheroSucre(Place &p);

void deplacerFourmi(Fourmi &f, Place &p1, Place &p2);

bool estVidePlace(Place p);
bool plusProcheNid(Place p1, Place p2);
bool plusLoinNid(Place p1, Place p2);

void testPlace();

#endif // PLACE_HPP_INCLUDED
