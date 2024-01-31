//  p2_main.c
//  
//
//  Por: Citlalli Selene Avalos Montiel e Ivan Giovanni Valdespin Garcia
//  Entrega:31.10.2021
//

#include "poligono.c"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	//se crea elemento poligono y lista de poligonos
	poligono pol;
	listpol lp;
	poligono puntos;//lista de puntos aleatorios
	int len= atoi(argv[3]);
	//Abrir archivos
	FILE *fp;
	FILE *fpp;
	
	//Lectura de archivos
	LeerArchivo(fp,&pol,&lp,argv);
	LeerPuntos(fpp,&puntos,argv);

	punto *tmp;
	poligono *tmp2;
	tmp = puntos.primpunto;
	tmp2 = lp.primpol;
	int cantidad[lp.tampol];
	int total,prueba;
	
	//Ubicación de los puntos dentro de los poligonos
	printf("\nUbicando los %d puntos en los poligonos...\n",len);
	for(int j=0;j<lp.tampol;j++){
		cantidad[j]=0;
		tmp = puntos.primpunto;
		for (int i=0;i<len;i++){
			cantidad[j]+=decision(*tmp,tmp2);
			tmp = tmp->siguiente;
		}
		tmp2 = tmp2->siguiente;
		printf("\n");
		total+=cantidad[j];
		//Se imprime la cantidad de puntos dentro de los poligonos
		printf("En poligono %d hay %d puntos\n",j+1,cantidad[j]);
	}
	printf("\n");
 	//Liberacion de memoria
	anular_listpol(&lp);
	anular_puntos(&puntos);

	return 0;
}
