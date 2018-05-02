#include <iostream>
#include <iomanip>

#include "Grille.hpp"

using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl


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
    Place p1, p2;
    float p, m = -1.;
    EnsCoord vois;
    for(int repet = 0; repet < NBLIGNE; repet++){
            m = -1;
            p = 0;
            //cout << endl <<endl<<endl;

        for(int i = 0; i < NBCASE; i++){
            m = -1;
            chargerPlace(g, g.listePlace[i].c, p1);
            p = pheroNidPlace(p1);
            vois = voisines(coordPlace(p1));
            for(int j = 0; j < vois.nbElts; j++){
                chargerPlace(g, vois.tab[j], p2);
                if(pheroNidPlace(p2) > m){
                    m = pheroNidPlace(p2);
                    //cout << m << endl;
                }
                rangerPlace(g, p2);
            }

            if(p < 1){
                p = max(m - (1./NBLIGNE), 0.);

            }
            poserPheroNid(p1, p);
            rangerPlace(g, p1);

        }
    }
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
            for(int i = 0; i < NBLIGNE; i++){
                cout << "+----";
            }
            cout << "+" << endl;
              cout << "| ";
          }
        if(g.listePlace[i].fourmi != -1){
            cout << setw(2) << g.listePlace[i].fourmi;
        } else if (g.listePlace[i].nid){
            cout << " N";
        } else if(g.listePlace[i].sucre){
            cout << " S";
        } else {
            cout << "  ";
        }

        //cout << setw(2) << setprecision(2) << g.listePlace[i].pheroNid; //affichage des pheroNid
        cout << " | ";

    }
    cout << endl;
    for(int i = 0; i < NBLIGNE; i++){
                cout << "+----";
            }
            cout << "+" << endl;

    cout << endl << endl;
}

void testGrille(){
    Grille a;
    bool testliste=false;
	Coord c1 = nouvCoord(4, 1);
	Coord c2 = nouvCoord(6, 4);
	Coord c3 = nouvCoord(2, 2);
	Coord c4 = nouvCoord(1,1);
	Coord c5 = nouvCoord(3,3);
	Coord c6 = nouvCoord(3,4);
	Coord c7 = nouvCoord(3,5);

	EnsCoord TestSucre, TestNid, TestF;
	ensFourmi ensFtest;

     chargerGrilleVide(a);
     for(int i=0; i<NBCASE; i++){
         ASSERT(estVidePlace(a.listePlace[i]));
     }
     cout << "ChargerGrilleVide OK"<< endl;


     TestNid = nouvEnsCoord();
     ajouteEnsCoord(TestNid, c1);
     ajouteEnsCoord(TestNid, c2);
     placerNid(a, TestNid);
     int i=0;
     do{
        testliste = egalCoord(a.listePlace[i].c, c1);
        i++;
     }while(not testliste && i<NBCASE);
     ASSERT(a.listePlace[i-1].nid == true && a.listePlace[i-1].sucre == false);

     i=0;
     testliste = false;
     do{
        testliste = egalCoord(a.listePlace[i].c, c2);
        i++;
     }while(not testliste && i<NBCASE);
     ASSERT(a.listePlace[i-1].nid == true && a.listePlace[i-1].sucre == false);
     cout << "placerNid OK"<< endl;


     TestSucre = nouvEnsCoord();
     ajouteEnsCoord(TestSucre, c3);
     ajouteEnsCoord(TestSucre, c4);
     placerSucre(a, TestSucre);
     int d=0;
     testliste=false;
     do{
        testliste = egalCoord(a.listePlace[d].c, c3);
        d++;
     }while(not testliste && d<NBCASE);
     ASSERT(a.listePlace[d-1].sucre == true);
     ASSERT(a.listePlace[d-1].nid == false);

     int j=0;
     testliste=false;
     do{
        testliste= egalCoord(a.listePlace[j].c, c4);
        j++;
     }while(not testliste && j<NBCASE);
     ASSERT(a.listePlace[j-1].sucre == true);
     ASSERT(a.listePlace[j-1].nid == false);
     cout << "placerSucre OK"<<endl;


    TestF=nouvEnsCoord();
    ajouteEnsCoord(TestF, c5);
    ajouteEnsCoord(TestF, c6);
    ajouteEnsCoord(TestF, c7);
    cout << "les coordonnees ont ete ajoutees "<< endl;
    //cout << "element 1 de coord" << TestF.tab[0].ligne<<"   "<<TestF.tab[0].colonne<<endl;
    //cout << "element 2 de coord" << TestF.tab[1].ligne<<"   "<<TestF.tab[1].colonne<<endl;
    //cout << "le nb de coord est de "<<TestF.nbElts<<endl;

    chargerTabFourmis(ensFtest, TestF);
    cout << "l ensemble fourmis a ete charge"<<endl;
    //cout << "fourmi 1 coord "<<ensFtest.fourmi[0].c.ligne<< ensFtest.fourmi[0].c.colonne<<endl;
    //cout << "fourmi 2 coord "<<ensFtest.fourmi[1].c.ligne<<ensFtest.fourmi[1].c.colonne<<endl;
    placerFourmi(a, ensFtest);
    cout << "les fourmis sont dans la grille"<<endl;


    initialiserGrille(a,ensFtest, TestSucre, TestNid);
    cout<<"initialiserGrille OK"<<endl;


    afficheGrille(a);
    cout<<"afficheGrille OK"<<endl;


    cout <<"pheroSucre = "<<a.listePlace[d-1].pheroSucre<<endl;
    diminuerPheroSucre(a.listePlace[d-1]);
    cout <<"maintenant pheroSucre = "<<a.listePlace[d-1].pheroSucre<<endl;

    cout << "TEST GRILLE OK" << endl;
}
