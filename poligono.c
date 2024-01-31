//  poligonos.c
//  
//
//  Por: Citlalli Selene Avalos Montiel e Ivan Giovanni Valdespin Garcia
//  Entrega:31.10.2021
//

#include "poligonos.h"

//Lectura de archivo de caracteristica de poligonos
void LeerArchivo(FILE *fp, poligono *pol, listpol *lp,char **argv){
 	char buffer[SB],caracter;
 	punto p;
	poligono listapuntos;
	float arreglo[8];

 	fp=fopen(argv[1], "r");
 	iniciar_listpol(lp);

	int j=0;
    while ( fgets(buffer, SB, fp)!=NULL ) {
    	iniciar_poligono(pol);
        sscanf(buffer,"%d %d %f %f %f %f %f %f %f %f", &pol->clave,&pol->lados,&arreglo[0],&arreglo[1],&arreglo[2],
        	&arreglo[3],&arreglo[4],&arreglo[5],&arreglo[6],&arreglo[7]);
	iniciar_poligono(&listapuntos);
        for (int i=0;i<4;i++){
        	p.x = arreglo[i*2];
        	p.y = arreglo[i*2+1];
        	inserta_punto(&p,i,pol);
        }
        inserta_poligono(pol,j,lp);
        j++; 
    }
    fclose(fp);


}

//Lectura del archivo de puntos aleatorios
void LeerPuntos(FILE *fpp, poligono *lp, char **argv){
	int SBB=atoi(argv[3])*30;
	char buffer[SBB];
	fpp = fopen(argv[2],"r");
	iniciar_poligono(lp);
	punto p;
	int i = 0;
	
	while (fgets(buffer,SBB,fpp)!=NULL ) {
		sscanf(buffer,"%f %f",&p.x,&p.y);
		inserta_punto(&p,i,lp);
		i ++;
	}
    fclose(fpp);
}

//Inicializa la estrucuta poligono
void iniciar_poligono(poligono *pol){
	
	pol->lados = 0;
	pol->clave = 0;
	pol->tampuntos = 0;
	pol->primpunto = NULL;
	pol->siguiente = NULL;}

//Inicialziza lista de poligonos
void iniciar_listpol(listpol *lp){
	lp->primpol = NULL;
	lp->tampol = 0;
}

//Inicializa lista de puntos
void iniciar_listpuntos(listpuntos *lp){
	lp->primero = NULL;
	lp->tamano = 0;
}

//Funcion para insertar poligonos dentro de la lista de poligonos
void inserta_poligono(poligono *pol, int pos, listpol *lp){
	if (pos>lp->tampol) { printf("NO se puede insertar elemento\n");}

	else if(pos==0){
		poligono *tmp = lp->primpol;
		lp->primpol= (poligono*)malloc(sizeof(poligono));
		lp->primpol->lados = pol->lados;
		lp->primpol->clave = pol->clave;
		lp->primpol->tampuntos = pol->tampuntos;
		lp->primpol->primpunto= pol->primpunto;
		lp->primpol->siguiente = tmp;
		lp->tampol ++;
	}
	else{
    poligono *last = lp->primpol;
    poligono *iterador = last->siguiente;

   int i;
    for (i=1; i<pos; i++) {
        last = iterador;
        iterador=last->siguiente;
    }
    
    last->siguiente = (poligono *)malloc(sizeof(poligono));
    last->siguiente->clave = pol->clave;
    last->siguiente->lados = pol->lados;
    last->siguiente->tampuntos = pol->tampuntos;
    last->siguiente->primpunto = pol->primpunto;

    last->siguiente->siguiente = iterador;
    lp->tampol++;}
    	

}

//Inserta puntos dentro de la lista de puntos
void inserta_punto(punto *p,int pos,poligono *pol){
	
	if (pos>pol->tampuntos) { printf("No se puede insertar elemento\n");}
	else if(pos==0){
		punto *tmp = pol->primpunto;
		pol->primpunto = (punto*)malloc(sizeof(punto));
		pol->primpunto->x = p->x;
		pol->primpunto->y = p->y;
		pol->primpunto->siguiente = tmp;
		pol->tampuntos ++;
	}
	else{
    punto *last = pol->primpunto;
    punto *iterador = last->siguiente;

   int i;
    for (i=1; i<pos; i++) {
        last = iterador;
        iterador=last->siguiente;
    }
    
    last->siguiente = (punto *)malloc(sizeof(punto));
    last->siguiente->x = p->x;
    last->siguiente->y = p->y;
    last->siguiente->siguiente = iterador;
    pol->tampuntos++;}
}

//Imprime la lista de poligonos
void imprime_listpol(listpol *lp){
    int i;
    poligono *imprime= lp->primpol;

    while(imprime!=NULL){
           printf("%d %d %d\n", imprime->clave,
                            	imprime->lados,
              					imprime->tampuntos); 
        imprime=imprime->siguiente;  
    }
}

//Imprime los puntos (vertices) de los poligonos
void imprime_puntos(poligono *pol){
    int i;

    punto *imprime= pol->primpunto;
    while(imprime!=NULL){
           printf("%f %f\n", imprime->x,
                              imprime->y);
        
        imprime=imprime->siguiente;  
    }
}

//Obtiene el mayor elemento entre val1 y val2
float max(float val1, float val2){
	return (val1>val2)?val1:val2;

}

//Obtiene el minimo elemento entre val1 y val2
float min(float val1, float val2){
	return (val1<val2)?val1:val2;
}

//Determina si un punto esta sobre una linea
int encontrarEnLinea(punto *p,punto *q1, punto *q2)
{
	if(p->x<=max(q1->x,q2->x)&& p->x>= min(q1->x,q2->x)&&p->y<=max(q1->y,q2->y)&&p->y>=min(q1->y,q2->y)){
		return SI;}
	return NO;
}

int giro(punto *q2, punto *q1, punto *p){

	float val = (q1->y - p->y) * (q2->x - q1->x) - (q1->x - p->x) * (q2->y - q1->y);

	if(val<=0.002 && val>=-0.002){return NO;}
	return(val>0.002)?DERECHA:IZQUIERDA;
}

//Nos dice si los puntos se intersectan
int encontrarIntersec(punto *q1, punto *p1, punto *p2, punto *q2){

    
    int giro1 = giro(p1, q1, p2);
    int giro2 = giro(p1, q1, q2);
    int giro3 = giro(p2, q2, p1);
    int giro4 = giro(p2, q2, q1);
      
    if (giro1 != giro2 && giro3 != giro4)
        return SI;
 
    if (giro1 == 0 && encontrarEnLinea(p1, p2, q1)) return SI;
    if (giro2 == 0 && encontrarEnLinea(p1, q2, q1)) return SI;
    if (giro3 == 0 && encontrarEnLinea(p2, p1, q2)) return SI;
    if (giro4 == 0 && encontrarEnLinea(p2, q1, q2)) return SI;
 
    return NO; 
}

//Determina dentro de que poligono se encuentra el punto ingresado
int decision(punto p, poligono *pol){
	punto rayo;
	rayo.y= p.y;
	rayo.x = LIMITE_CUADRADO;

	int contador = 0;
	int l=1;

	punto *primer,*tmp = pol->primpunto;
	primer=tmp;
	int inter;
	
	do{
		if (l==pol->lados) {
		tmp->siguiente=primer;
		}
		inter=encontrarIntersec(tmp,tmp->siguiente,&p,&rayo);
		if(inter==SI){
			if(giro(&p,tmp,tmp->siguiente)==0){
				if(encontrarEnLinea(&p,tmp,tmp->siguiente)==SI){}
				else {return NO;}
			}
			contador ++;
		} 
		if(l<pol->lados){
		tmp = tmp->siguiente;}
		l++;
	
	} while(l<=pol->lados);

	return contador%2;
}

//LIberacion de memoria, elimincacion de la lista de poligonos
void anular_listpol(listpol *lp){

    poligono *tmp, *tmp2;;
    
    tmp=lp->primpol;
    while (tmp!=NULL) {
        tmp2=tmp->siguiente;
        free(tmp);
        tmp = tmp2;
    }
    lp->tampol=0;
}

//Liberación de memoria, eliminacion de la lista de puntos
void anular_puntos(poligono *pol){
	punto *tmp, *tmp2;
    tmp=pol->primpunto;
    while (tmp!=NULL) {
        tmp2=tmp->siguiente;
        free(tmp);
        tmp = tmp2;
    }
    pol->tampuntos=0;
}
