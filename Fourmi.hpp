#ifndef FOURMI_HPP_INCLUDED
#define FOURMI_HPP_INCLUDED

#include "Coord.hpp"

const int NBFOURMI = 0;

struct Fourmi{
    Coord c;
    int indice;
    bool sucre, nid;
};




Fourmi creerFourmi(Coord c, int indice);

Coord coordFourmis(Fourmi f);
int numFourmi(Fourmi f);

bool porteSucre(Fourmi f);
bool rentreNid(Fourmi f);

void dechargerSucre(Fourmi &f);
void chargerSucre(Fourmi &f);
void deplaceFourmi(Fourmi &f, Coord c);

#endif // FOURMI_HPP_INCLUDED
