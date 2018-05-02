#include <iostream>

#include "Fourmi.hpp"

using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl

//Constructeur
Fourmi creerFourmi(Coord c, int indice){
    Fourmi f;
    f.c = c;
    f.indice = indice;
    f.sucre = false;
    f.nid = false;

    return f;
}


//ACCES
Coord coordFourmis(Fourmi f){
    return f.c;
}

int numFourmi(Fourmi f){
    return f.indice;
}


//PREDICATS
bool porteSucre(Fourmi f){
    return f.sucre;
}

bool rentreNid(Fourmi f){
    return f.nid;
}


//MODIFICATIONS
void dechargerSucre(Fourmi &f){
    f.sucre = false;
}

void chargerSucre(Fourmi &f){
    f.sucre = true;
}

void deplaceFourmi(Fourmi &f, Coord c){
    f.c = c;
}

void chargerTabFourmis(ensFourmi &tabFourmis, EnsCoord ec){
     for(int i =0; i < ec.nbElts; i++){
        tabFourmis.fourmi[i] = creerFourmi(ec.tab[i], i);
        tabFourmis.nbElts ++;
    }
}


//TEST
void testFourmi(){

    ensFourmi tabFourmis;
    Coord c;
    c.ligne = 0;
    for(int i = 0; i < NBFOURMI; i++){
            c.colonne = i;
        tabFourmis.fourmi[i] = creerFourmi(c, i);
        if(porteSucre(tabFourmis.fourmi[i]) || rentreNid(tabFourmis.fourmi[i])){
            cout << "ERREUR : Initialisation fourmi " << i << endl;
            exit(1);
        }
    }

    Coord nul;
    nul = nouvCoord(0, 0);
    ASSERT(egalCoord(coordFourmis(tabFourmis.fourmi[0]), nul));

    for(int o = 0; o < NBFOURMI; o++){
        ASSERT(numFourmi(tabFourmis.fourmi[o]) == o);
    }

    chargerSucre(tabFourmis.fourmi[0]);
    ASSERT(porteSucre(tabFourmis.fourmi[0]));
    dechargerSucre(tabFourmis.fourmi[0]);
    ASSERT(not porteSucre(tabFourmis.fourmi[0]));

    Coord deplace;
    deplace = nouvCoord(200,10);
    deplaceFourmi(tabFourmis.fourmi[0], deplace);
    ASSERT(egalCoord(coordFourmis(tabFourmis.fourmi[0]), deplace));
    cout << "TEST FOURMI OK" << endl;
}
