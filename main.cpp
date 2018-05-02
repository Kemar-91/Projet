#include <iostream> // pour cout
#include <iomanip> // pour setfill, setw
#include <sstream> // pour ostringstream
#include <fstream> // pour ofstream
#include <string>
#include "SFML/Graphics.hpp"

#include "Fourmi.hpp"
#include "Grille.hpp"
#include "Place.hpp"
#include "Coord.hpp"

using namespace std;

const int echelle = 50;

void testglobal(){
    testFourmi();
    testCoord();
    testPlace();
    testGrille();
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

void dessinerGrille(Grille g, sf::RenderWindow &window){
    Place p;
    int x, y;
    sf::RectangleShape shape(sf::Vector2f(echelle, echelle));

    for(int i = 0; i < NBCASE; i++){
            chargerPlace(g, g.listePlace[i].c, p);
            x = (p.c.colonne - 1) * echelle;
            y = (p.c.ligne - 1) * echelle;
            if(numFourmiPlace(p) != -1){
                shape.setPosition(sf::Vector2f(x, y));
                shape.setFillColor(sf::Color::Black);
                window.draw(shape);
            } else if(contientSucrePlace(p)){
                shape.setPosition(sf::Vector2f(x, y));
                shape.setFillColor(sf::Color(250, 193, 0));
                window.draw(shape);
            } else if(contientNidPlace(p)){
                shape.setPosition(sf::Vector2f(x, y));
                shape.setFillColor(sf::Color::Blue);
                window.draw(shape);
            } else if(p.pheroSucre > 0){
                shape.setPosition(sf::Vector2f(x, y));
                shape.setFillColor(sf::Color(pheroSucrePlace(p),0, 0));
                window.draw(shape);
            } else {
                shape.setPosition(sf::Vector2f(x, y));
                shape.setFillColor(sf::Color(0, p.pheroNid * 255, 0));
                window.draw(shape);
            }

        }
}

void deplacementHasard(Grille &g, Fourmi &f){
    EnsCoord voisins;
    Place fourmi, dep;
    Coord c;

    chargerPlace(g, coordFourmis(f), fourmi);
    voisins = voisines(coordPlace(fourmi));

    do{
        c = choixCoordHasard(voisins);
        chargerPlace(g, c, dep);
    }while(not estVidePlace(dep));

    deplacerFourmi(f, fourmi, dep);
    rangerPlace(g, fourmi);
    rangerPlace(g, dep);
}


int main(){
    Grille jeu;
    ensFourmi tabFourmis;
    EnsCoord sucre, nid, voisins;
    Place p;
    sf::Vector2i positionSouris;
    int x, y;
    Coord c;

    testglobal();

      initialiserEmplacements(tabFourmis, sucre, nid);
//
      initialiserGrille(jeu, tabFourmis, sucre, nid);

    sf::RenderWindow window(sf::VideoMode(20 * echelle, 20 * echelle), "Fourmis");


    window.setFramerateLimit(15);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //GESTION EVENEMENT SOURIS : ajoute sucre
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                positionSouris = sf::Mouse::getPosition(window);
                cout << "x = " << positionSouris.x << ", y = " << positionSouris.y << endl;
                x = positionSouris.x;
                y = positionSouris.y;
                if(x >= 0 && x <= 20 * echelle && y >= 0 && y <= 20 * echelle){
                    cout << "x/echelle = " << x/echelle << endl;
                    x = (x / echelle) + 1;
                    y = (y / echelle) + 1;
                    c = nouvCoord(y, x);
                    chargerPlace(jeu, c, p);
                    if(not contientNidPlace(p))
                        poserSucre(p);
                    rangerPlace(jeu, p);
                }
            }

            //GESTION EVENEMENT SOURIS : enleve sucre
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                positionSouris = sf::Mouse::getPosition(window);
                cout << "x = " << positionSouris.x << ", y = " << positionSouris.y << endl;
                x = positionSouris.x;
                y = positionSouris.y;
                if(x >= 0 && x <= 20 * echelle && y >= 0 && y <= 20 * echelle){
                    cout << "x/echelle = " << x/echelle << endl;
                    x = (x / echelle) + 1;
                    y = (y / echelle) + 1;
                    c = nouvCoord(y, x);
                    chargerPlace(jeu, c, p);
                    if(contientSucrePlace(p))
                    enleveSucre(p);
                    rangerPlace(jeu, p);
                }
            }
        }

        window.clear();
          for(int j = 0; j < tabFourmis.nbElts; j++){
             deplacementHasard(jeu, tabFourmis.fourmi[j]);
          }

        dessinerGrille(jeu, window);


        window.display();
    }


    return 0;
}



