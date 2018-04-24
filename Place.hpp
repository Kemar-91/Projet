#ifndef PLACE_HPP_INCLUDED
#define PLACE_HPP_INCLUDED

#include "Coord.hpp"

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

#endif // PLACE_HPP_INCLUDED
