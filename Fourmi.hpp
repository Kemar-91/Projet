#ifndef FOURMI_HPP_INCLUDED
#define FOURMI_HPP_INCLUDED

#include "Coord.hpp"

const int NBFOURMI = 12;

struct Fourmi{
    Coord c;
    int indice;
    bool sucre, nid;
};

struct ensFourmi{
    Fourmi fourmi[NBFOURMI];
    int nbElts = 0;
};


Fourmi creerFourmi(Coord c, int indice);

Coord coordFourmis(Fourmi f);
int numFourmi(Fourmi f);

bool porteSucre(Fourmi f);
bool rentreNid(Fourmi f);

void dechargerSucre(Fourmi &f);
void chargerSucre(Fourmi &f);
void deplaceFourmi(Fourmi &f, Coord c);

void chargerTabFourmis(ensFourmi &tabFourmis, EnsCoord ec);

void testFourmi();

#endif // FOURMI_HPP_INCLUDED
