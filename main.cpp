#include <iostream>

#include "Fourmi.hpp"
#include "Grille.hpp"
#include "Place.hpp"
#include "Coord.hpp"

using namespace std;

void testglobal(){
    testFourmi();
    testCoord();
    testPlace();
}

void initialiserEmplacements(ensFourmi &tabF,EnsCoord &sucre, EnsCoord &nid){

    sucre = nouvEnsCoord();
    ajouteEnsCoord(sucre, nouvCoord(1, 10));
    ajouteEnsCoord(sucre, nouvCoord(19, 19));
    //afficheEnsCoord(sucre);

    nid = nouvEnsCoord();
    ajouteEnsCoord(nid, nouvCoord(10,10));
    ajouteEnsCoord(nid, nouvCoord(10,11));
    ajouteEnsCoord(nid, nouvCoord(11,10));
    ajouteEnsCoord(nid, nouvCoord(11,11));
    //afficheEnsCoord(nid);

    EnsCoord fourmis = nouvEnsCoord();
    for(int i = 9; i <= 12; i++){
        ajouteEnsCoord(fourmis, nouvCoord(9, i));
    }
    ajouteEnsCoord(fourmis, nouvCoord(10,9));
    ajouteEnsCoord(fourmis, nouvCoord(10,12));
    ajouteEnsCoord(fourmis, nouvCoord(11,9));
    ajouteEnsCoord(fourmis, nouvCoord(11,12));
    for(int i = 9; i <= 12; i++){
        ajouteEnsCoord(fourmis, nouvCoord(12, i));
    }

    chargerTabFourmis(tabF, fourmis);
}

void dessinerGrille(Grille g){
    afficheGrille(g);
}

void mettreAJourEnsFourmi(Grille &g, ensFourmi &tabF){

}

int main(){
    Grille jeu;
    ensFourmi tabFourmis;
    EnsCoord sucre, nid;

    initialiserEmplacements(tabFourmis, sucre, nid);

    initialiserGrille(jeu, tabFourmis, sucre, nid);

    dessinerGrille(jeu);

    for(int i = 0; i < 30; i++){
        mettreAJourEnsFourmi(jeu, tabFourmis);
        dessinerGrille(jeu);
        diminuerPheroSucreGrille(jeu);
    }

    return 0;
}
