#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <vector>

#include <fstream>

using namespace std;

/*
	#define diagonalMove 1.41421
	#define linearMove 1
*/

struct Structure
{
public:

	Structure(){}

	Structure(int size){
		Matrix.resize(size);
		for (int i = 0; i < size; ++i)
		{
			Matrix[i].resize(size,1);
		}
	}

	Structure(const Structure & struc){
		int size = struc.Matrix.size();
		Matrix.resize(size);
		for (int i = 0; i < size; ++i)
		{
			Matrix[i].resize(size);
		}
		for(int i = 0; i < size; ++i){
			for (int j = 0; j < size; ++j)
			{
				Matrix[i][j] = struc.Matrix[i][j];
			}
		}
	}

	~Structure(){}

	vector< vector<bool> > Matrix;

//Matrix of turn light - boxes. When a box is turn, internally is turn off the light of the box
	bool getData(int x, int y){
		//  if x<0 or y<0 means that the point is out of the window
		if (x<0 || y<0)
			return false;
		return Matrix[x][y];
	}

//turn on the box
	void turnOffData(int x, int y){
		Matrix[x][y]=0;
	}
//kill the box, turn off the box
	void turnOnData(int x, int y){
		Matrix[x][y]=1;
	}

//change value of the data
	void changeValue(int x, int y){
		Matrix[x][y] = !Matrix[x][y];
	}

//To make a log off the box or the current state of the box
	void printNode(){
		//llenar un archivo con + y " "
		ofstream stream;
		stream.open("box.txt");
		if(stream.is_open()){
			string word;
			for(vector< vector<bool> >::iterator it=Matrix.begin(); it!=Matrix.end(); ++it){
				for (vector<bool>::iterator iter = it->begin(); iter != it->end(); ++iter){
					word += (*iter)?'+':' ';
				}
				word += '\n';
				stream << word;
				word = "";
			}
		} else{
			cout<<"archivo no se pudo escribir"<<endl;
		}
		stream.close();
	}
};

#endif // STRUCTURE_H
