#ifndef GAME_H
#define GAME_H

#include "Structure.h"

#define diagonalMove 1.41421
#define linearMove 1

struct point
{
	point(){
		x = 0;
		y = 0;
		internalRound = 0;
	}

	point(int xT, int yT){
		x = xT;
		y = yT;
		internalRound = 0;
	}

	point(const point & p){
		x = p.x;
		y = p.y;
		internalRound = p.internalRound;
	}

	virtual ~point(){}

	int x;
	int y;

	//round para la generación de puntos
	int internalRound;

	point generateNextPoint(){
		point temporalPoint;
		switch (internalRound){
			case 0:
				temporalPoint.x = x + 1;
				temporalPoint.y = y;
				break;
			case 1:
				temporalPoint.x = x;
				temporalPoint.y = y + 1;
				break;
			case 2:
				temporalPoint.x = x - 1;
				temporalPoint.y = y;
				break;
			case 3:
				temporalPoint.x = x;
				temporalPoint.y = y - 1;
				break;
			case 4:
				temporalPoint.x = x + 1;
				temporalPoint.y = y + 1;
				break;
			case 5:
				temporalPoint.x = x + 1;
				temporalPoint.y = y - 1;
				break;
			case 6:
				temporalPoint.x = x - 1;
				temporalPoint.y = y + 1;
				break;
			case 7:
				temporalPoint.x = x - 1;
				temporalPoint.y = y - 1;
				break;
		}
		internalRound+=1;
		internalRound = internalRound % 8;
		return temporalPoint;
	}
};

#endif // GAME_H
