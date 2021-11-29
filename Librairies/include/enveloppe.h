#ifndef ENVELOPPE_H
#define ENVELOPPE_H

#include "point.h"
#include "polygone.h"
#include <vector>


using namespace std;

// Construit dans le polygone P l’enveloppe convexe des trois points a,b,c. On suppose P initialement vide.
// La fonction renvoie l’adresse du sommet de coordonnées c.
Sommet* enveloppe(const Point& a, const Point& b, const Point& c, Polygone& P) {

	Sommet* sommetC = nullptr;
	float determinant = c.aGauche(a, b);

	if (determinant == 1) {
		P.ajouteSommet(a, nullptr);
		P.ajouteSommet(c, P.premier());
		P.ajouteSommet(b, sommetC);

		sommetC = P.premier()->suivant();
	}
	else {
		P.ajouteSommet(a, nullptr);
		P.ajouteSommet(b, P.premier());
		P.ajouteSommet(c, P.premier()->suivant());

		sommetC = P.premier()->suivant()->suivant();
	}

	return sommetC;
};

// Construit dans le polygone P l’enveloppe convexe de l'ensemble de points donné dans T.
// On suppose P initialement vide.
void enveloppe(vector<Point>& T, Polygone& P) {

	Sommet* sommetDernier = enveloppe(T[0], T[1], T[2], P);
	Sommet* sommetPremier = P.premier();
	Sommet* sommetHaut = nullptr;
	Sommet* sommetBas = nullptr;

	if (T.size() > 3) {

		for (int i = 3; i < T.size(); i++) {

			Point pointNouveau = T[i];
			sommetDernier = P.ajouteSommet(pointNouveau, sommetDernier);
		}
	}
};
#endif
