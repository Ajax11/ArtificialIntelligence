#ifndef GAME_H
#define GAME_H

#include "Structure.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>

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

//sobre carga de operadores
	bool operator == (const point & pointB){
		return ( (this->x == pointB.x) && (this->y == pointB.y) );
	}
	bool operator != (const point & pointB){
		return ( (this->x != pointB.x) || (this->y != pointB.y) );
	}

};

struct boxGame{

	boxGame(int posInitX, int posInitY, int posEndX, int postEndY, int size){
		firstPoint.x = posInitX;
		firstPoint.y = posInitY;
		lastPoint.x = posEndX;
		lastPoint.y = postEndY;
		window = Structure(size);
		sizeTable = size;
		aAsterisk();
	}
	virtual ~boxGame(){}

	Structure window;
	point firstPoint;
	point lastPoint;
	int sizeTable;

// erase a posible point for the search
	void blackenPoint(int x, int y){
		window.turnOffData(x,y);
		return;
	}

// Simulate a fixed boxes of dead mini boxes
	void setDeadBlocks(){}

// Method for the search of the answer
	
//structura adicional paara almacernar la posicion del punto actual y su costo hasta el momento de ese punto
struct node
{
	node(){
		currentPlot.x=0;
		currentPlot.y=0;
		cost=0;
	}
	node(int x, int y, int value){
		currentPlot.x = x;
		currentPlot.y = y;
		cost = value;
	}
	node(int x, int y){
		currentPlot.x = x;
		currentPlot.y = y;
		cost = 0;
	}
	node(const point & A){
		currentPlot = A;
	}
	point currentPlot;
	int cost;
};

	int functionCost(const point & pointStart, const point & pointEnd){
		int costStartEnd;
		if ( ( abs(pointStart.x - pointEnd.x) + abs(pointStart.y - pointEnd.y) ) == 1){
			costStartEnd = linearMove;
		}else{
			costStartEnd = diagonalMove;
		}
		return ( costStartEnd + sqrt( pow(pointEnd.x - lastPoint.x, 2) + pow(pointEnd.y - lastPoint.y, 2) ) );
	}

	void aAsterisk(){
#define MaxMove 8

	std::vector<node> resultWay;
	std::vector< std::vector<node> > treeSearch;

	point currentPlot = firstPoint;

	bool find;
	find = 0;

	int roundNumb;
	roundNumb = 0;

	while(currentPlot != lastPoint && !find){

		++roundNumb;

		std::vector<node> vectorMovement;
		//Generación de todos los posibles movimientos a realizar, se almacenan en un vetor de mayor a menor
		for (int i = 0; i < MaxMove; ++i){

cout<<endl<<"Generando posibles movimientos para el round "<<roundNumb<<endl;

			point A;
			A = currentPlot.generateNextPoint();

			if(window.getData(A.x, A.y)){
				node currentPoint(A);
				currentPoint.cost = functionCost(currentPlot, currentPoint.currentPlot);
				
cout <<"costo:\t"<< currentPoint.cost<<"\t Point:\t"<<currentPoint.currentPlot.x <<"\t"<< currentPoint.currentPlot.y <<endl;

				//analizar parte del ordenamiento
				if (!vectorMovement.empty()){
					for(int i=0; i<vectorMovement.size(); ++i){
						if(vectorMovement[i].cost < currentPoint.cost){
							node b;
							b.cost = currentPoint.cost;
							b.currentPlot.x = currentPoint.currentPlot.x;
							b.currentPlot.y = currentPoint.currentPlot.y;
							
							currentPoint.currentPlot.x = vectorMovement[i].currentPlot.x;
							currentPoint.currentPlot.y = vectorMovement[i].currentPlot.y;
							currentPoint.cost = vectorMovement[i].cost;

							vectorMovement[i].currentPlot.x = b.currentPlot.x;
							vectorMovement[i].currentPlot.y = b.currentPlot.y;
							vectorMovement[i].cost = b.cost;
						}
					}
				}
				vectorMovement.push_back(currentPoint);
				find = ( (currentPoint.currentPlot.x == lastPoint.x) && (currentPoint.currentPlot.y == lastPoint.y) )?1:0;
			}
		}
		//Actualizar el currentPlot
		currentPlot.x = vectorMovement[vectorMovement.size()-1].currentPlot.x;
		currentPlot.y = vectorMovement[vectorMovement.size()-1].currentPlot.y;

		//currentPlot = vectorMovement.crbegin();
		//almacenar el rastro - track

cout<<endl<<"Punto seleccionado"<<endl;		
cout <<"costo:\t"<< vectorMovement[vectorMovement.size()-1].cost<<"\t Point:\t"<<currentPlot.x <<"\t"<< currentPlot.y <<endl;
cout<<endl;

		resultWay.push_back(currentPlot);
	}

	for (int i = 0; i < resultWay.size(); ++i){
		cout <<"costo:\t"<< resultWay[i].cost<<"\t Point:\t"<<resultWay[i].currentPlot.x <<"\t"<< resultWay[i].currentPlot.y <<endl;
	}




/*
	Forma de realizar el A*
		se necesita un vector de vectores para simular la recurrencia de la pila
		sin embargo hay q analizar las posibilidades y si son factibles para analizar
		en caso no sea conveniene obiar el elemnto y continuar con el siguiente

		forma de evaluar el estado:
			f(x) = costo distacia abanzado + distancia del nuevo punto al punto final
			costo distancia avanzado
				linearMove
				diagonalMove
*/
	}
};

#endif // GAME_H
