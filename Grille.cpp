#include <iostream>
#include <iomanip>

#include "Grille.hpp"

using namespace std;


void chargerGrilleVide(Grille &g){
    Coord c;
    int lign = 0;
    int col = 1;
    for(int i = 0; i< NBCASE; i++){
        if(i % 20 == 0){
            lign ++;
            col = 1;
        }
        c = nouvCoord(lign, col);
        g.listePlace[i]= creerPlaceVide(c);
        g.listePlace[i].pheroNid = 0;
        col ++;
    }
}


void chargerPlace(Grille g, Coord c, Place &p){
     int i=0;
     bool test = false;
     do{
        test = egalCoord(g.listePlace[i].c, c);
        i++;
     }while(not test);
     p = g.listePlace[i-1];
}


void rangerPlace(Grille &g, Place p){
    for(int i = 0; i < NBCASE; i++){
        if(egalCoord(g.listePlace[i].c, p.c)){
            g.listePlace[i] = p;
            return;
        }
    }
}

void placerNid(Grille &g, EnsCoord ec){
    Place p;
    for(int i = 0; i < ec.nbElts; i++){
        chargerPlace(g, ec.tab[i], p);
        p.nid = true;
        p.pheroNid = 1;
        rangerPlace(g, p);
    }
}

void placerSucre(Grille &g, EnsCoord ec){
    Place p;
    for(int i = 0; i < ec.nbElts; i++){
        chargerPlace(g, ec.tab[i], p);
        p.sucre = true;
        rangerPlace(g, p);
    }
}

void placerFourmi(Grille &g, ensFourmi ef){
    Place p;
    for(int i = 0; i < ef.nbElts; i++){
        chargerPlace(g, ef.fourmi[i].c, p);
        p.fourmi = i;
        ef.fourmi[i].c = p.c;
        rangerPlace(g, p);
    }
}

void lineariserPheroNid(Grille &g){

}

void initialiserGrille(Grille &g, ensFourmi ef, EnsCoord sucre, EnsCoord nid){
    chargerGrilleVide(g);
    placerSucre(g, sucre);
    placerNid(g, nid);
    placerFourmi(g, ef);
    lineariserPheroNid(g);
}

void diminuerPheroSucreGrille(Grille &g){
    Place p;
    for(int i = 0; i < NBCASE; i++){
        chargerPlace(g, g.listePlace[i].c, p);
        diminuerPheroSucre(p);
        rangerPlace(g, p);
    }
}

void afficheGrille(Grille g){
    Place p;
    for(int i = 0; i < NBCASE; i++){
        if(i % 20 == 0){
            cout << endl;
            cout << "| ";
        }
        if(g.listePlace[i].fourmi != -1){
            cout << "F";
        } else if (g.listePlace[i].nid){
            cout << "N";
        } else if(g.listePlace[i].sucre){
            cout << "S";
        } else {
            cout << " ";
        }

        cout << " | ";

    }

    cout << endl << endl;
}
