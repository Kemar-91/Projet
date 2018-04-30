#include <iostream>
#include <cstdlib>

#include "Coord.hpp"

using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl


int max(int a, int b){
	if(b > a)
		return b;
    else
		return a;
}

void testMax(){
	ASSERT(max(4, 2) == 4);
	ASSERT(max(2, 4) == 4);

	ASSERT(max(4, 2) != 2);
	ASSERT(max(4, 10) != 4);
}

int min(int a, int b){
	if(b > a)
		return a;
    else
		return b;
}

void testMin(){
	ASSERT(min(4, 2) != 4);
	ASSERT(min(2, 4) != 4);

	ASSERT(min(4, 2) == 2);
	ASSERT(min(4, 10) == 4);
}

Coord nouvCoord(int lig, int col){
	Coord res;
	res.ligne = lig;
	res.colonne = col;
	return res;
}

void afficheCoord(Coord aff){
	cout << "c = (" << aff.ligne << ", " << aff.colonne << ")" << endl;
}

bool egalCoord(Coord c1, Coord c2){
	if(c1.ligne == c2.ligne && c1.colonne == c2.colonne)
		return true;
	else
		return false;
}

void testEgalCoord(){
	ASSERT(egalCoord(nouvCoord(2, 2), nouvCoord(2, 2)));
	ASSERT(egalCoord(nouvCoord(0, 0), nouvCoord(0, 0)));
	ASSERT(not egalCoord(nouvCoord(2, 1), nouvCoord(2, 0)));
	ASSERT(not egalCoord(nouvCoord(0, 0), nouvCoord(0 , 2)));
	ASSERT(not egalCoord(nouvCoord(0, 0), nouvCoord(0 , 2)));
	ASSERT(not egalCoord(nouvCoord(0, 0), nouvCoord(2 , 0)));
	ASSERT(not egalCoord(nouvCoord(10, 9), nouvCoord(9 , 10)));
	ASSERT(not egalCoord(nouvCoord(2, 0), nouvCoord(0 , 2)));
}

int rechercheCoordEnsCoord(EnsCoord ec, Coord c){
	for(int i = 0; i < ec.nbElts; i++){
		if(egalCoord(c, ec.tab[i]))
			return i;
    }
	return -1;
}


void afficheEnsCoord(EnsCoord coords){
	if(coords.nbElts > 0){
		for(int i = 0; i < coords.nbElts; i++){
			cout << "  -c" << i + 1 << " : (" << coords.tab[i].ligne << ", " << coords.tab[i].colonne << ")" << endl;
		}
	} else {
		cout << "Il n'y a pas de coordonnees !" << endl;
	}
}

EnsCoord nouvEnsCoord(){
	EnsCoord p;
	p.nbElts = 0;
	return p;
}

void ajouteEnsCoord(EnsCoord &ec, Coord c){
	if(ec.nbElts > MAXENSCOORD){
		cout << "Nombre de coordonnees pleins !!" << endl;
		exit(1);
	} else if(rechercheCoordEnsCoord(ec, c) != -1){
		cout << "La coordonnee a ajouter est deja presente dans le tableau !" << endl;
		exit(1);
	} else {
		ec.tab[ec.nbElts] = c;
		ec.nbElts ++;
	}
}

void supprimeEnsCoord(EnsCoord &ec, Coord c){
	if(rechercheCoordEnsCoord(ec, c) == -1){
		cout << "La coordonnee n'est pas dans l'ensemble !" << endl;
		exit(1);
	} else {
		int indice = rechercheCoordEnsCoord(ec, c);
		for(int i = indice; i < ec.nbElts; i++){
			ec.tab[i] = ec.tab[i + 1];
		}
		ec.nbElts --;
	}
}


EnsCoord voisines(Coord c){
	EnsCoord ev;
	ev = nouvEnsCoord();
	//cout << "entre dans voisines" << endl;
	int i_min = max(c.ligne - 1, 1);
	int i_max = min(c.ligne + 1, TAILLE);
	int j_min = max(c.colonne - 1, 1);
	int j_max = min(c.colonne + 1, TAILLE);

	for(int i = i_min; i <= i_max; i++){
		for(int j = j_min; j <= j_max; j++){
			if(not egalCoord(nouvCoord(i, j), c)){
                //cout << "ajout" << endl;
				ajouteEnsCoord(ev, nouvCoord(i, j));
			}
		}
	}

	return ev;
}

Coord choixCoordHasard(EnsCoord ec){
    return ec.tab[rand() % (ec.nbElts + 1)];;
}

int Cardinal(EnsCoord ec){
    //cout<<ec.nbElts;
    return ec.nbElts;
}

Coord retourneElement(EnsCoord ec, int i){
    return ec.tab[i];
}

void testCoord(){

	testMax();
	testMin();

	Coord c1 = nouvCoord(2, 1);
	Coord c2 = nouvCoord(3, 4);
	Coord c3 = nouvCoord(0, 0);

	afficheCoord(c1);
	cout << endl << endl << endl;

	// on construit un exemple d’ensemble
	EnsCoord exemple = nouvEnsCoord();
	ajouteEnsCoord(exemple, c1);
	ajouteEnsCoord(exemple, c2);
	ajouteEnsCoord(exemple, c3);
	afficheEnsCoord(exemple);

	// on ajoute encore un element
	cout << "ajout d’un element :" << endl;

	ajouteEnsCoord (exemple, nouvCoord(4,0));
	afficheEnsCoord(exemple);

	cout << endl << endl << endl;

	// on teste la fonction voisines
	EnsCoord v;
	int i;
	for (i = 0; i < exemple.nbElts; i++){
		v = voisines(exemple.tab[i]);
		cout << "les voisines de ";
		afficheCoord(exemple.tab[i]);
		cout << "sont " << endl;
		afficheEnsCoord(v);
	}

	cout << endl << endl;

	EnsCoord test = exemple;
	afficheEnsCoord(test);
	supprimeEnsCoord(test, c2);
	cout << test.nbElts << endl;
	afficheEnsCoord(test);

	cout << endl << endl;
	Coord p;


	//while(true){
		p = choixCoordHasard(exemple);
		cout << "p = ";
		afficheCoord(p);
		cout << endl;
	//}
}
