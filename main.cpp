#include <iostream>

#include "Fourmi.hpp"
#include "Grille.hpp"
#include "Place.hpp"
#include "Coord.hpp"

using namespace std;

void testglobal(){
    testFourmi();
    //testCoord();
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

bool condition_n(int regle, Fourmi f, Place p1, Place p2){
    if(regle == 1){
        return not porteSucre(f) && contientSucrePlace(p2);
    } else if(regle == 2){
        return rentreNid(f) && contientNidPlace(p2);
    } else if(regle == 3){
        return rentreNid(f) && estVidePlace(p2) && plusProcheNid(p2, p1);
    } else if(regle == 4){
        return not porteSucre(f) && surUnePistePlace(p1) && plusLoinNid(p2, p1) && surUnePistePlace(p2);
    } else if(regle == 5){
        return not porteSucre(f) && surUnePistePlace(p2) && estVidePlace(p2);
    } else if(regle == 6){
        return not porteSucre(f) && estVidePlace(p2);
    } else {
        cout << "ERREUR : Num de regle incorrecte" << endl;
        exit(1);
    }
}

void action_n(int regle, Fourmi &f, Place &p1, Place &p2){
    if(regle == 1){
        chargerSucre(f);
        poserPheroSucre(p1);
    } else if(regle == 2){
        dechargerSucre(f);
    } else if(regle == 3){
        deplacerFourmi(f, p1, p2);
        poserPheroSucre(p2);
    } else if(regle == 4){
        deplacerFourmi(f, p1, p2);
    } else if(regle == 5){
        deplacerFourmi(f, p1, p2);
    } else if(regle == 6){
        deplacerFourmi(f, p1, p2);
    } else {
        cout << "ERREUR : Num de regle incorrecte" << endl;
        exit(1);
    }
}

void mettreAJourUneFourmi(Grille &g, Fourmi &f){
    Place p1, p2;
    Coord c, voisins;
    bool mvt;
    int nbv, numVoisins, regle;
    EnsCoord CoordV = nouvEnsCoord();

    c = coordFourmis(f);
    chargerPlace(g, c, p1);
    regle = 1;
    mvt = false;
    CoordV = voisines(c);

    while(regle <= 6 && not mvt){
        //cout << regle << endl;
        nbv = Cardinal(CoordV);
        //cout << nbv << endl;
        numVoisins = 0;

        if(not mvt){
            voisins = choixCoordHasard(CoordV);
            chargerPlace(g, voisins, p2);

            if(condition_n(regle, f, p1, p2)){
                action_n(regle, f, p1, p2);
                mvt = true;
                rangerPlace(g, p1);
                rangerPlace(g, p2);
            }

        numVoisins ++;
        }

    regle ++;
    }
}

void mettreAJourEnsFourmi(Grille &g, ensFourmi &tabF){
    Fourmi f;
    for(int i = 0; i < tabF.nbElts; i++){
        f = tabF.fourmi[i];
        mettreAJourUneFourmi(g, f);
    }
}


int main(){
    Grille jeu;
    ensFourmi tabFourmis;
    EnsCoord sucre, nid;

    testglobal();
    int pause;
    initialiserEmplacements(tabFourmis, sucre, nid);

    initialiserGrille(jeu, tabFourmis, sucre, nid);

    dessinerGrille(jeu);

    for(int i = 0; i < 300; i++){
        //cin >> pause;
        mettreAJourEnsFourmi(jeu, tabFourmis);
        dessinerGrille(jeu);
        diminuerPheroSucreGrille(jeu);
    }

    return 0;
}
