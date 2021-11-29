#ifndef POINT_H
#define POINT_H
#include "stdlib.h"

class Point
{

public:
	// constructeurs
	Point() : d_x{ 0 }, d_y{ 0 }, d_z{ 0 }, d_r{ 0 }, d_g{ 0 }, d_b{ 0 } {}
	Point(float x, float y, float z, float r, float g, float b) : d_x{ x }, d_y{ y }, d_z{z}, d_r{ r }, d_g{ g }, d_b{ b } {}
	// accesseurs
	float x() const { return d_x; }
	float y() const { return d_y; }
	float z() const { return d_z; }
	float r() const { return d_r; }
	float g() const { return d_g; }
	float b() const { return d_b; }
	// renvoie 1, -1 ou 0 selon que le point auquel la méthode est appliquée est
	// à gauche de, à droite de, ou sur la droite (ab) orientée de a vers b.
	int aGauche(const Point& a, const Point& b) const
	{
		int xDroite = b.x() - a.x();
		int yPointC = this->d_y - a.y();
		int xPointC = this->d_x - a.x();
		int yDroite = b.y() - a.y();

		int resultat = (xDroite * yPointC) - (xPointC * yDroite);
		int determinant;

		if (resultat > 0)
		{
			determinant = 1;
		}
		else if (resultat < 0)
		{
			determinant = -1;
		}
		else {
			determinant = 0;
		}

		return determinant;
	};


private:
	// coordonnées
	float d_x, d_y, d_z, d_r, d_g, d_b;
};

#endif
