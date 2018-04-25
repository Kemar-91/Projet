#include <iostream>
#include <iomanip>
#include <cstdlib>

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
    return p;
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
    }
}


void poserSucre(Place &p){
    p.sucre = true;
}

void poserNid(Place &p){
    p.nid = true;
}

void poserFourmi(Fourmi &f, Place &p){
    f.c = p.c;
    p.fourmi = f.indice;
}

void enleverFourmi(Place &p){
    p.fourmi = -1;
}

void poserPheroNid(Place &p, float intensite){
    p.pheroNid = intensite;
}

void poserPheroSucre(Place &p){
    p.pheroSucre = 255;
}

void diminuerPheroSucre(Place &p){
    if(p.pheroSucre > 0)
        p.pheroSucre = p.pheroSucre - 5;
}


void deplacerFourmi(Fourmi &f, Place &p1, Place &p2){
    if(p2.fourmi == -1){
        f.c = p2.c;
        p1.fourmi = -1;
        p2.fourmi = f.indice;
    } else {
        cout << "ERREUR : deplacerFourmi : Une fourmi est deja sur la place de déplacement " << endl;
        exit(1);
    }
}


bool estVidePlace(Place p){
    if(p.fourmi == -1){
        return p.nid && p.sucre;
    } else {
        return false;
    }
}

bool plusProcheNid(Place p1, Place p2){
    if(p1.pheroNid > p2.pheroNid)
        return true;
    else
        return false;
}

bool plusLoinNid(Place p1, Place p2){
    if(p1.pheroNid < p2.pheroNid)
        return false;
    else
        return true;
}
