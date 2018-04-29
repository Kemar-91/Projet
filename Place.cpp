#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Place.hpp"

using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl

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
    else if(p.pheroSucre >= 0 && p.pheroSucre <= 255)
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
        p2.fourmi = p1.fourmi;
        p1.fourmi = -1;
    } else {
        cout << "ERREUR : deplacerFourmi : Une fourmi est deja sur la place de déplacement " << endl;
        exit(1);
    }
}


bool estVidePlace(Place p){
    if(p.fourmi == -1 && not p.nid && not p.sucre){
        return true;
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

void testPlace(){
    Coord c;
    c.colonne = 10;
    c.ligne = 10;

    Place p = creerPlaceVide(c);
    ASSERT(egalCoord(c, coordPlace(p)));
    ASSERT(estVidePlace(p));

    ASSERT(pheroNidPlace(p) == -1);
    ASSERT(pheroSucrePlace(p) == -1);
    poserPheroSucre(p);
    ASSERT(pheroSucrePlace(p) == 255);
    diminuerPheroSucre(p);
    ASSERT(pheroSucrePlace(p) == 250);

    ASSERT(not contientNidPlace(p));
    ASSERT(not contientSucrePlace(p));
    poserNid(p);
    ASSERT(contientNidPlace(p));
    poserSucre(p);
    ASSERT(contientSucrePlace(p));

    poserPheroNid(p, 0.2);
    surUnePistePlace(p);

    Coord q;
    q.colonne = 20;
    q.ligne = 20;
    Fourmi f = creerFourmi(q, 2);
    poserFourmi(f, p);
    ASSERT(p.fourmi == 2);
    ASSERT(egalCoord(f.c, c));

}
