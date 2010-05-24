#ifndef valores_H
#define valores_H
#include <ctime>
#include <iostream>
//#include <cstdlib> 
//#include "estadoInterno.h"

using namespace std;

//para contar cuantos se tienen de cada que
static int tricoblastos = 0;
static int atricoblastos = 0;

// numeo de estados y tamaño de la gradilla
static const int states = 2;
static const  int xmax = 25, ymax = 25;


static int statesMatrix[xmax][ymax];
static int statesMatrixnt1[xmax][ymax];
static const int dimencions2D = 2;
static int dimSizes2D[dimencions2D] = {xmax, ymax};

//variables para sincronizar vista y modelo
static bool corre = false; 
static bool stop = true;
static bool clean = false;
static bool set = false;
static bool salir = false;

static int iteracion = 0;

static void init(){
	//printf("dominantes = %d, resesivos = %d\n", dominante, resesivo);
	//aca se guarda el valor generado al azar cuando es necesario
	int randomNumber = 0;
	
	time_t timer;
	int naa=0;
	 srand (time(NULL)); // seed random number generator by i
	for(int i = 0; i<xmax;++i){
		for(int j = 0; j<ymax;++j){
			// escoje un numero al azar de 100
			randomNumber = rand()%100;
			//crea una celula con tricoblastos
			if(randomNumber < 33){
				statesMatrix[i][j] = 1;
			}
			else if ( (33 <= randomNumber)&& (randomNumber < 66)) {
				statesMatrix[i][j] = 1;
			}
			else  {
				statesMatrix[i][j] = 2;
			}
			randomNumber = rand()%100;
			
		}//for j
	}// for i	
}
static void limpiaTodo(){
	for(int i = 0; i<xmax;++i)
		for(int j = 0; j<ymax;++j){
			statesMatrix[i][j] = 0;
		}
}

// este metodo cuenta cuantos bichos se tienen de cada tipo
static void calculaCantidades(){
	
	tricoblastos = 0;
	atricoblastos = 0;
	for(int i =0; i< xmax;++i)
		for(int j = 0; j < ymax; ++j){
			if(statesMatrix[i][j] == 1){
				tricoblastos += 1;
			}
			else if(statesMatrix[i][j] == 2){
				atricoblastos += 1;
			}
		}
	
}
#endif
