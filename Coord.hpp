#ifndef COORD_HPP_INCLUDED
#define COORD_HPP_INCLUDED

const int TAILLE = 20;
const int MAXENSCOORD = TAILLE * TAILLE;


struct Coord{
	int ligne = 0;
	int colonne = 0;
};

struct EnsCoord{
	Coord tab[MAXENSCOORD];
	int nbElts;
};

int max(int a, int b);
void testMax();
int min(int a, int b);
void testMin();

Coord nouvCoord(int lig, int col);
void afficheCoord(Coord aff);
bool egalCoord(Coord c1, Coord c2);
void testEgalCoord();
int rechercheCoordEnsCoord(EnsCoord ec, Coord c);
void afficheEnsCoord(EnsCoord coords);
EnsCoord nouvEnsCoord();
void ajouteEnsCoord(EnsCoord &ec, Coord c);
void supprimeEnsCoord(EnsCoord &ec, Coord c);
EnsCoord voisines(Coord c);
Coord choixCoordHasard(EnsCoord ec);

int Cardinal(EnsCoord ec);
Coord retourneElement(EnsCoord ec, int i);

void testCoord();


#endif // COORD_HPP_INCLUDED
