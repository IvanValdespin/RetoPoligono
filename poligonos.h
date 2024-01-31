//  poligonos.h
//  
//
//  Por: Citlalli Selene Avalos Montiel e Ivan Giovanni Valdespin Garcia
//  Entrega:31.10.2021
//

#ifndef poligonos_h
#define poligonos_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO 0
#define SI 1
#define COLINEAL 0
#define DERECHA 1
#define IZQUIERDA 2
#define LIMITE_CUADRADO 11
#define SUBB 100
#define SB 90
//#define P 10
//#define SBB P*30
#define FUERA_DE_RANGO -1



//Estructura para generar puntos
typedef struct _punto{
	float x;// coordenada x
	float y;// coordenada y
	struct _punto *siguiente;
}punto;

//Estructura para generar poligonos
typedef struct _poligono{
	int lados;//numero de aristas o lados
	int clave;
	int tampuntos;
	punto *primpunto;
	struct _poligono *siguiente;
	
} poligono;

//Estructura para generar lista de poligonos
typedef struct _listpol{
	poligono *primpol;
	int tampol;

}listpol;

//Estructura para generar lista de puntos
typedef struct _listpuntos{
	punto *primero;
	int tamano;
}listpuntos;


//Funciones para leer archivos
void LeerArchivo(FILE *fp, poligono *pol, listpol *lp,char **argv);
void LeerPuntos(FILE *fpp, poligono *lp, char **argv);

// funciones para manejar listas
  //Funciones para la lista de poligonos 
void iniciar_poligono(poligono *pol);//Inicializa todos los atributos de la estructura poligono.
void iniciar_listpol(listpol *lp); //Inicializa todos los atributos de la estructura listpol (lista de poligonos).
void inserta_poligono(poligono *pol,int pos,listpol *lp); //Inserta un poligono dentro de la lista de poligonos.
void imprime_listpol(listpol *lp); //Imprime los atributos del poligono en cuestion.
void anular_listpol(listpol *lp);//Elimina todos los poligonos dentro de la lista de poligonos.Libera memoria
  //Funciones para lista de puntos
void iniciar_listpuntos(listpuntos *lp); //Inicializa todos los atributos de la estructura punto.
void inserta_punto(punto *p,int pos,poligono *pol); //Inserta un punto dentro de la estructura listpuntos (lista de puntos).
void imprime_puntos(poligono *pol); //Imprime el punto en cuestion.
void anular_puntos(poligono *pol); //Elimina todos los puntos dentro de la lista de puntos. Libera memoria

// funciones para encontrar si el punto esta dentro o fuera de poligono
float max(float val1, float val2); //Obtiene el valor maximo entre los dos valores de entrada.
float min(float val1, float val2); //Obtiene el valor minimo entre los dos valores de entrada.
int encontrarEnLinea(punto *p,punto *q1, punto *q2);//función para saber si un punto p esta en una linea formada por q1 y q2.
int giro(punto *p, punto *q1, punto *q2);// función que describe si el giro fue a la  drecha o izq o ninguno de los 2 si es colineal.
int encontrarIntersec(punto *p1, punto *p2, punto *q1, punto *q2);//funcipon que detecta ela cantidad de intersecciones.
int decision(punto p, poligono *pol);// retorna SI, si el punto p esta dentro del pol de n vertices,retorno NO en caso contrario.

#endif /* poligonos_h */
