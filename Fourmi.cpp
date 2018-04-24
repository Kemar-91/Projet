#include <iostream>

#include "Fourmi.hpp"

using namespace std;

Fourmi tabFourmis[NBFOURMI];

Fourmi creerFourmi(Coord c, int indice){
    Fourmi f;
    f.c = c;
    f.indice = indice;
    f.sucre = false;
    f.nid = false;

    return f;
}


Coord coordFourmis(Fourmi f){
    return f.c;
}

int numFourmi(Fourmi f){
    return f.indice;
}


bool porteSucre(Fourmi f){
    return f.sucre;
}

bool rentreNid(Fourmi f){
    return f.nid;
}


void dechargerSucre(Fourmi &f){
    f.sucre = false;
}

void chargerSucre(Fourmi &f){
    f.sucre = true;
}

void deplaceFourmi(Fourmi &f, Coord c){
    f.c = c;
}
