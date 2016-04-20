#ifndef GAME_H
#define GAME_H

#include "Structure.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>

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

//		setDeadBlocks();

		aAsterisk();

		window.printNode();
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
	void setDeadBlocks(){
		int posIX, posIY, posFX, posFY;

//bloque del punto 30,30 al 40,40
		posIX = 0;
		posIY = 10;
		posFX = 40;
		posFY = 40;

		for (int i = posIX; i < posFX; ++i)
		{
			for (int j = posIY; j < posFY; ++j)
			{
				window.turnOffData(i,j);
			}
		}


//bloque del punto 30,30 al 40,40
		posIX = 10;
		posIY = 10;
		posFX = 20;
		posFY = 20;

		for (int i = posIX; i < posFX; ++i)
		{
			for (int j = posIY; j < posFY; ++j)
			{
				window.turnOffData(i,j);
			}
		}


//bloque del punto 30,30 al 40,40
		posIX = 20;
		posIY = 20;
		posFX = 40;
		posFY = 40;

		for (int i = posIX; i < posFX; ++i)
		{
			for (int j = posIY; j < posFY; ++j)
			{
				window.turnOffData(i,j);
			}
		}

//bloque del 50,50 al 70,70
		posIX = 50;
		posIY = 50;
		posFX = 70;
		posFY = 70;

		for (int i = posIX; i < posFX; ++i)
		{
			for (int j = posIY; j < posFY; ++j)
			{
				window.turnOffData(i,j);
			}
		}

	}

// Method for the search of the answer
	
//structura adicional paara almacernar la posicion del punto actual y su costo hasta el momento de ese punto
struct node
{
	node(){
		currentPlot.x=0;
		currentPlot.y=0;
		cost=0;
		state = 0;
	}
	node(int x, int y, int value, bool valState){
		currentPlot.x = x;
		currentPlot.y = y;
		cost = value;
		state = valState;
	}
	node(int x, int y){
		currentPlot.x = x;
		currentPlot.y = y;
		cost = 0;
		state = 0;
	}
	node(const point & A){
		currentPlot.x = A.x;
		currentPlot.y = A.y;
		cost = 0;
		state = 0;
	}
	node(const node & A){
		currentPlot.x = A.currentPlot.x;
		currentPlot.y = A.currentPlot.y;
		state = A.state;
		cost = A.cost;
	}
	point currentPlot;
	int cost;
	bool state;
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


	ofstream stream;
	stream.open("LogOfMove.txt");
	string word;

	std::vector<node> resultWay;
	std::vector< std::vector<node> > treeSearch;

	point currentPlot = firstPoint;

	bool find;
	find = 0;

	int roundNumb;
	roundNumb = 0;

	while(currentPlot != lastPoint && !find){

//cout<< endl << "iniciando"<< endl;
		++roundNumb;
/*
		if (!treeSearch.empty()){
			if ( treeSearch[treeSearch.size()].empty() ){
				treeSearch.pop_back();
			}
			if(( treeSearch[treeSearch.size()].crbegin() ) -> state == 1){
				treeSearch[treeSearch.size()].pop_back();
			}
		}
*/

//Falta implementar el stack para almacenar las rutas recorridas

 word += '\n';
 word = "Generando posibles movimientos para el round " + std::to_string(roundNumb);
 word += '\n';
 stream << word;
 word = "";

		std::vector<node> vectorMovement;
		//Generación de todos los posibles movimientos a realizar, se almacenan en un vetor de mayor a menor
		for (int i = 0; i < MaxMove; ++i){

//cout<<endl<<"Generando posibles movimientos para el round "<<roundNumb<<endl;

			point A;
			A = currentPlot.generateNextPoint();
			if(window.getData(A.x, A.y)){
				node currentPoint(A);
				currentPoint.cost = functionCost(currentPlot, currentPoint.currentPlot);
//cout <<"costo:\t"<< currentPoint.cost<<"\t Point:\t"<<currentPoint.currentPlot.x <<"\t"<< currentPoint.currentPlot.y <<endl;

 word += '\n';
 word = "costo: ";
 word += "\t";
 word += std::to_string(currentPoint.cost);
 word += "\t Point: \t";
 word += std::to_string(currentPoint.currentPlot.x);
 word += "\t";
 word += std::to_string(currentPoint.currentPlot.y);
 word += '\n';
 stream << word;
 word = "";
				//analizar parte del ordenamiento
				if (!vectorMovement.empty()){
					for(int i=0; i<vectorMovement.size(); ++i){
						if(vectorMovement[i].cost < currentPoint.cost){
							node b;
							b.cost = currentPoint.cost;
							b.currentPlot.x = currentPoint.currentPlot.x;
							b.currentPlot.y = currentPoint.currentPlot.y;
							b.state = currentPoint.state;

							currentPoint.currentPlot.x = vectorMovement[i].currentPlot.x;
							currentPoint.currentPlot.y = vectorMovement[i].currentPlot.y;
							currentPoint.cost = vectorMovement[i].cost;
							currentPoint.state = vectorMovement[i].state;

							vectorMovement[i].currentPlot.x = b.currentPlot.x;
							vectorMovement[i].currentPlot.y = b.currentPlot.y;
							vectorMovement[i].cost = b.cost;
							vectorMovement[i].state = b.state;
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

		//almacenar el rastro - track

 word = "\n Punto seleccionado \n";
 stream << word;
 word = "";

/*cout <<"costo:\t"<< vectorMovement[vectorMovement.size()-1].cost<<"\t Point:\t"<<currentPlot.x <<"\t"<< currentPlot.y <<endl;
cout<<endl;
*/
 word += '\n';
 word = "costo: ";
 word += "\t";
 word += std::to_string(vectorMovement[vectorMovement.size()-1].cost);
 word += "\t Point: \t";
 word += std::to_string(currentPlot.x);
 word += "\t";
 word += std::to_string(currentPlot.y);
 word += '\n';
 word += '\n';
 word += '\n';
 stream << word;
 word = "";

 		node tempNode(currentPlot);
 		tempNode.cost = vectorMovement[vectorMovement.size()-1].cost;
		resultWay.push_back(tempNode);

	}
	stream.close();

		cout <<endl <<"costo:\t"<< 0<<"\t Point:\t"<<firstPoint.x <<"\t"<< firstPoint.y <<endl;
	for (int i = 0; i < resultWay.size(); ++i){
		cout <<"costo:\t"<< resultWay[i].cost<<"\t Point:\t"<<resultWay[i].currentPlot.x <<"\t"<< resultWay[i].currentPlot.y <<endl;
	}



//Map of the game

	std::vector< std::vector<int> > mapGame;
	mapGame.resize(sizeTable);
	for (int i = 0; i < sizeTable; ++i){
		mapGame[i].resize(sizeTable,0);
	}

	for (int i = 0; i < sizeTable; ++i){
		for (int j = 0; j < sizeTable; ++j)	{
			mapGame[i][j] = (!(window.Matrix[i][j]))?1:0;
		}
	}



	for (int i = 0; i < resultWay.size(); ++i){
		mapGame[resultWay[i].currentPlot.x][resultWay[i].currentPlot.y] = 3;
	}

	mapGame[firstPoint.x][firstPoint.y] = 3;

		ofstream streamBox;
		streamBox.open("boxGameing.txt");
		if(streamBox.is_open()){
			string word;
			int it = 0;
			for (int i = 0; i < sizeTable; ++i){
				for (int j = 0; j < sizeTable; ++j){
					if (mapGame[i][j] == 3){
						word+=' ';
					} else{
						word += (mapGame[i][j] == 1)?'+':'0';
					}
				}
				word += '\n';
				streamBox << word;
				word = "";
			}
		} else{
			cout<<"archivo no se pudo escribir"<<endl;
		}
		streamBox.close();


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
