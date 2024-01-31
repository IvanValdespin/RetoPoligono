#include <iostream>
#include <stdlib.h>
#include<random>

using namespace std;
const int fil =1000;
const int col = 2;

constexpr int FLOAT_MIN = 10;
constexpr int FLOAT_MAX = 100;
class Matriz{
public:
	float _Matriz[fil][col];
	Matriz(){
		for(int f=0;f<fil;f++){
			for (int c=0;c<col;c++){
				_Matriz[f][c] = 0;
			}
		}
	}
	void llenar(){

		srand( time( NULL ) );



		for(int f=0;f<fil;f++){
			for (int c=0;c<col;c++){
				_Matriz[f][c] = (( rand( ) % 10000 ) / 1000.0f );
			}
		}
	}
	void Mostrar(){
		for(int f=0;f<fil;f++){
			for (int c=0;c<col;c++){
				cout << _Matriz[f][c]<<" ";
			} cout<<endl;
		}

	}
};


int main(){


 Matriz mat;
 mat.llenar();
 mat.Mostrar();

}