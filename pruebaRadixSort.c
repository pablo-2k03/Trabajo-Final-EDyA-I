#include <stdio.h>
#include <stdlib.h>
#include "listas/lista.h"
#include "radixSort.h"
#include <time.h>
int purga(Lista *l);  // No lo he usado, lo he dejado por si acaso
long int contadorExterno, contadorInterno;

int main(int argc, char *argv[])
{   Lista miLista;
    tipoPosicion p;
    int numElementos = 20, codigoError,i;
    clock_t t_ini, t_fin;
    double t_medio;
    srand(time(NULL));
    FILE *fp;
	if (argc > 2) {
            printf("\n Uso: ./pruebaRadixSort <número de elementos de la lista>\n\n");
            return -1;
        }
       if (argc==2) 
		numElementos=atoi(argv[1]); 

    printf("Creando lista vacia: %d\n", creaVacia(&miLista));

    printf("Se crea una lista de %d elementos\n", numElementos);
    anula(&miLista);	
    p = primero(&miLista);
    for (i = 0; i < numElementos; i++) { 
    	codigoError = inserta(rand()%100000,p,&miLista);
    	p = siguiente(p,&miLista);
    }
    imprime(&miLista);
    t_ini = clock();
    radixSort(&miLista,10,5);
    t_fin = clock();
    t_medio = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    printf("\nLista Ordenada \n");
    imprime(&miLista);
    //Exportar al fichero

    
    fp = fopen("radixSort.txt","w");
    if(fp == NULL){
        printf("Error al abrir el fichero");
        return -1;
    }
    else{
        fprintf(fp,"n|tiempoMedio|contadorExterno|contadorInterno\n");
        printf("\n\nGuardando datos de la prueba inicial en el fichero radixSort.txt...\n");
        fprintf(fp,"%d|%lf|%ld|%ld\n",numElementos,t_medio,contadorExterno,contadorInterno);
        int i = 0,valorInicial,numIncremento;
        printf("\nPruebas para guardar datos en el fichero (10 repeticiones minimas) con 5s por repeticion.\n");
        do{
            printf("Introduce el valor inicial de la lista (min 1000, max 10000): ");
            scanf("%d",&valorInicial);    
        }  
        while(valorInicial < 1000 || valorInicial > 10000);
        do{
            printf("Introduce el incremento (2500,10000): ");
            scanf("%d",&numIncremento);
        }
        while(numIncremento < 2500 || numIncremento > 10000);
        printf("Valor inicial: %d\tIncremento: %d\n",valorInicial,numIncremento);
        for(i=valorInicial; i<valorInicial+numIncremento*10; i+=numIncremento){ //valorInicial+ Incremento * numero de veces q queremos q se ejecute.
            anula(&miLista);
            p = primero(&miLista);
            int j;
            for (j = 0; j < i; j++) { 
                codigoError = inserta(rand()%100000,p,&miLista);
                p = siguiente(p,&miLista);
            }
            t_fin =t_ini = clock();
            clock_t tiempoMinimo = 5*CLOCKS_PER_SEC;
            int numRepeticiones = contadorExterno = contadorInterno = 0;
            while(t_fin - t_ini < tiempoMinimo){
                radixSort(&miLista,10,5);
                t_fin = clock();
                numRepeticiones++;
            }
            t_medio = (double)(t_fin - t_ini) / CLOCKS_PER_SEC / numRepeticiones;
            printf("%d|%e|%ld|%ld\n",i,t_medio,contadorExterno/numRepeticiones,contadorInterno/numRepeticiones);
            fprintf(fp,"%d|%e|%ld|%ld\n",i,t_medio,contadorExterno/numRepeticiones,contadorInterno/numRepeticiones);
        }
    }
    anula(&miLista);
    destruye(&miLista); 
    return 0;
}