#include <stdio.h>
#include <stdlib.h>
#include "listas/lista.h"
#include "radixSort.h"
#include <math.h>

void radixSort(Lista* lista,int numGrupos,int numCifras){
    int i,j;
    Lista* grupos;
    tipoPosicion p;
    if(lista == NULL || lista->raiz ==NULL) return;

    grupos = malloc(sizeof(Lista)*numGrupos);

    for(i=0;i<numGrupos;i++){     
      creaVacia(&grupos[i]);      
    }

    //Rellenamos los grupos
    for(i=0;i<numCifras;i++){
        contadorExterno++;
        p = primero(lista);
        while(!(p == fin(lista))){  
            int grupo = recupera(p,lista)%(int)pow(10,i+1)/pow(10,i); //Obtenemos el grupo al que pertenece.
            inserta(recupera(p,lista),primero(&grupos[grupo]),&grupos[grupo]);
            p = siguiente(p,lista);
        }
        anula(lista); //Vaciamos la lista y volvemos a rellenarla con los elementos de los grupos.
        for(j=numGrupos-1;j>=0;j--){//Lo recorremos a la inversa porque se inserta siempre el primero (l.33).
            p = primero(&grupos[j]);
            while(!(p == fin(&grupos[j]))){
                contadorInterno++;
                inserta(recupera(p,&grupos[j]),primero(lista),lista);
                p = siguiente(p,&grupos[j]);        
            }
            anula(&grupos[j]); //Vaciamos los grupos.
        }
    }
    //Liberamos memoria
    for(i=0;i<numGrupos;i++)
        destruye(&grupos[i]);
    free(grupos); 
}