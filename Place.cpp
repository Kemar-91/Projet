#include <iostream>
#include <iomanip>

#include "Place.hpp"

using namespace std;

Place creerPlaceVide(Coord c){
    Place p;
    p.c = c;
    p.fourmi = -1;
    p.sucre = false;
    p.nid = false;
    p.pheroNid = -1;
    p.pheroSucre = -1;
}


Coord coordPlace(Place p){
    return p.c;
}

float pheroNidPlace(Place p){
    return p.pheroNid;
}

float pheroSucrePlace(Place p){
    return p.pheroSucre;
}


int numFourmiPlace(Place p){
    return p.fourmi;
}

bool contientSucrePlace(Place p){
    return p.sucre;
}

bool contientNidPlace(Place p){
    return p.nid;
}

bool surUnePistePlace(Place p){
    if(p.pheroSucre == -1)
        return false;
    else if(p.pheroSucre >= 0)
        return true;
    else {
        cout << "ERREUR : Fonction surUnePistePlace --> pheroSucre" << endl;
        exit(1);
        return false;
    }
}


void poserSucre(Place &p){
    p.sucre = true;
}

