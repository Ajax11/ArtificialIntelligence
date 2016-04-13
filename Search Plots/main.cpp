#include <iostream>
#include "Game.h"
using namespace std;

#define diagonalMove 1.41421

int main()
{	
	//parametros PuntoInicial:posX,PosY Puntofinal:posX, PoxY Tamaño de la ventaja - numero de puntos o cuadrados
	boxGame Frame(1,1,24,14,30);

	cout<<endl<<Frame.window.Matrix.size()<<endl;
	cout<<Frame.window.Matrix[0].size()<<endl;

	cout << endl << diagonalMove << endl;
    return 0;
}
