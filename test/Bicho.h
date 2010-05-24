#ifndef Bicho_H
#define Bicho_H

#include <windows.h>
#include <winbase.h>
class Bicho{

	
	
public:

	// esta variable representa hacia donde ve el bicho
	int direccion;
	// esta variable representa si tiene el pie derecho adelnate o no
	bool derecho;
	//esta variable representa el tipo del bicho
	int type;
	// para los bichos con estado juvenil se usa esta variable
	bool juvenil;
	//bandera para tener un rato juvenil a un bicho
	int banderaJuvenil;
	// para los bichos depredarores se usa esta otra
	bool comiendo;
	//bandera para tener un rato comiendo a un bicho
	int banderaComiendo;
	// esta bandera es para determinar que tipo comes
	bool lagartijaVerde;
	//para evitar que un bicho se aparee con muchos a la vez ( :-) puritanismo para evitar sobrepoblacion)
	bool apareandose;
	// bandera que alluda a determinar cuanto dura el apareamiento
	int banderaApareandose;
	// Para poder imitar la reproduccion sexual y el viaje mendeliano
	int alelo1;
	int alelo2;
	/*ya que el automaton que queremos utilizar es asincrono y las casillas las llamamos de manera
	azaroza puede suceder que al moverse un bicho y ya ocupando una casilla que no a sido llamada 
	sea llamado otra vez, si este es el caso ponemos esta bandera para decir que en esta iteracion
	este bicho ya se movio o hiso lo que se que le correspondio*/
	bool actuaste;
	//estos tres valores representa las casillas que ve el bicho
	//dependiendo hacia adonde apunte su direccion
	int frente, frenteDerecha, frenteIzquierda, derecha, izquierda, atras, atrasDerecha, atrasIzquierda;

	Bicho(int t): type(t){}
	Bicho(){}
	/**
	* este metodo modifica los valores frente, derecha, izquierda, segun la direccion
	* a la que apunte el bicho, para que den los valores que se deven de sumar al 
	* valor de inicio de vecindario en el vector contenedor de vecinos del automaton, 
	* y asi obtener los tres indices de los vecinos en el automaton
	*/
	void calculaVista(){
		switch(direccion) {
			case 1 : 
				frente = 4;
				frenteDerecha = 0;
				frenteIzquierda = 1;
				derecha = 6;
				izquierda = 7;
				atras = 5;
				atrasDerecha = 2;
				atrasIzquierda = 3;
				break;
			case 2 : 
				frente = 1;
				frenteDerecha = 4;
				frenteIzquierda = 7;
				derecha = 0;
				izquierda = 3;
				atras = 2;
				atrasDerecha = 6;
				atrasIzquierda = 5;
				break;
			case 3 : 
				frente = 7;
				frenteDerecha = 1;
				frenteIzquierda = 3;
				derecha = 4;
				izquierda = 5;
				atras = 6;
				atrasDerecha = 0;
				atrasIzquierda = 2;
				break;
			case 4 : 
				frente = 3;
				frenteDerecha = 7;
				frenteIzquierda = 5;
				derecha = 1;
				izquierda = 2;
				atras = 0;
				atrasDerecha = 4;
				atrasIzquierda = 6;
				break;
			case 5 : 
				frente = 5;
				frenteDerecha = 3;
				frenteIzquierda = 2;
				derecha = 7;
				izquierda = 6;
				atras = 4;
				atrasDerecha = 1;
				atrasIzquierda = 0;
				break;
			case 6 : 
				frente = 2;
				frenteDerecha = 5;
				frenteIzquierda = 6;
				derecha = 3;
				izquierda = 0;
				atras = 1;
				atrasDerecha = 7;
				atrasIzquierda = 4;
				break;
			case 7 : 
				frente = 6;
				frenteDerecha = 2;
				frenteIzquierda = 0;
				derecha = 5;
				izquierda = 4;
				atras = 7;
				atrasDerecha = 3;
				atrasIzquierda = 1;
				break;
			default: 
				frente = 0;
				frenteDerecha = 6;
				frenteIzquierda = 4;
				derecha = 2;
				izquierda = 1;
				atras = 3;
				atrasDerecha = 5;
				atrasIzquierda = 7;

		} //end switch

	}


};
#endif //Bicho_H