#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int creaVacia(Lista *l) {
    if (l == NULL)  //Si la lista no existe no se puede crear.
        return -1;
    if((l->raiz = (tipoCelda *)malloc(sizeof(tipoCelda))) == NULL) //Si la reserva falla, no se puede crear.
        return -2;
    l->raiz->sig = NULL; // Se crea la lista vacia.
    return 0;
}

int vacia(Lista *l) {
    if (l == NULL || l->raiz == NULL)  //Si la lista no existe o no tiene raiz, no se puede comprobar si esta vacia.
        return -1;
    else if (l->raiz->sig == NULL)  //Si la pos siguiente de la raiz apunta a NULL, la lista esta vacia.
        return 1;
    else 
        return 0; //Si no, no esta vacia.
}

int destruye(Lista *l) {
    if (l == NULL || l->raiz == NULL)  //Si la lista no existe o no tiene raiz, no se puede destruir la lista
        return -1;
    else if (l->raiz->sig != NULL)  //Si la pos siguiente de la raiz apunta a NULL, la lista no se puede destruir, porque no está vacia.
        return -2;
    else {
        free(l->raiz);
        l->raiz = l->ultimo = NULL;
        return 0;
    }
}

void imprime(Lista *l) {
    tipoCelda *aImprimir;
    
    if (l == NULL || l->raiz == NULL) //Si la lista no existe o no tiene raiz, no se puede imprimir.
        return;
    else {
        aImprimir = l->raiz->sig;
        while (aImprimir != NULL) {
            printf("%d ", aImprimir->elemento);
            aImprimir = aImprimir->sig;
        }
    }
}

tipoPosicion anterior(tipoPosicion p, Lista *l) {
    tipoCelda *anterior;
    
    if (l == NULL || l->raiz == NULL || p == NULL) //Si la lista no existe o no tiene raiz, o la posicion no existe, no se puede devolver la posicion anterior.
        return NULL;
    else if (p == l->raiz->sig)  //Si la posicion es el nodo después del ficticio, no tiene anterior,por lo que se devuelve NULL.
        return NULL;
    else {
        anterior = l->raiz; //Recorres la lista hasta encontrar la posicion anterior a la que se pasa como parametro (p).
        while (anterior->sig != p) 
            anterior = anterior->sig;
        return anterior;
    }
}

tipoPosicion primero(Lista *l) {
    if (l == NULL || l->raiz == NULL)  //Si la lista es null, error.
        return NULL;
    else  // Si la lista esta vacia, devolvemos la raiz.
        return l->raiz;
}

tipoPosicion fin(Lista *l) { 
    tipoPosicion aux = l->raiz;

    if (l == NULL || l->raiz == NULL) // Si la lista no existe o está vacía (no definida)
        return NULL;
    else {
        while (aux->sig != NULL)  //Buscamos el ultimo elemento.
            aux = aux->sig;
        return aux;
    }
}

int inserta(tipoElemento x, tipoPosicion p, Lista *l) {
    tipoCelda *temp;

    if (l == NULL || l->raiz == NULL || p == NULL) // Comprobamos que la lista no sea nula
        return -1;
    else {
        if ((temp = (tipoCelda *)malloc(sizeof(tipoCelda))) == NULL)  //Si falla la reserva de la variable temporal, devolvemos -2
            return -2;

        temp->elemento = x; // Asignamos el elemento a la variable temporal
        temp->sig = p->sig; // Asignamos el siguiente de la posicion a la variable temporal
        p->sig = temp; // Asignamos la variable temporal al siguiente de la posicion
    }
    return 0;
}

  int suprime(tipoPosicion p, Lista *l) {
    tipoPosicion aBorrar;
    aBorrar = p->sig;
    p->sig = aBorrar->sig;
    free(aBorrar);
    return 1;
}  

tipoPosicion siguiente(tipoPosicion p, Lista *l) {
    if (l == NULL || l->raiz == NULL || p == NULL) // Comprobamos que la lista no sea NULL.
        return NULL;
    else if (p == fin(l)){ // Si la posicion es la ultima, devolvemos la ultima.
        return fin(l);
    }
    else 
        return p->sig; 
}

tipoPosicion localiza(tipoElemento x, Lista *l) {
    tipoPosicion aux = l->raiz;

    if (l == NULL || l->raiz == NULL)  // Comprobamos que la lista no sea NULL.
        return NULL;
    else {
        while (aux->sig != NULL) { // Recorremos la lista hasta que encontremos el elemento buscado.
            if (aux->sig->elemento == x) 
                return aux;
            aux = aux->sig;
        }
        return aux;
    }	
}

tipoElemento recupera(tipoPosicion p, Lista *l) {
    if (l == NULL || l->raiz == NULL || p == NULL)  // Comprobamos que la lista no sea NULL
        return -1;
    else if (p == fin(l))  // Comprobamos que la posicion no sea la ultima
        return -2;
    else 
        return p->sig->elemento; 
}

int anula(Lista *l) {
    tipoPosicion aux = l->raiz->sig, aBorrar;
    l->raiz->sig = NULL;

    if (l == NULL || l->raiz == NULL)  // No se puede anular una lista vacia
        return -1;
    else {
        while (aux != NULL){ // Iteramos la lista y vamos borrando cada elemento de esta.
            aBorrar = aux; 
            aux = aux->sig;
            free(aBorrar);
        }
        return 0;
    }
}
int traspasarNodo(tipoPosicion p, Lista *la, tipoPosicion q, Lista *lb){
    if (la == NULL || la->raiz == NULL || lb == NULL || lb->raiz == NULL) // Comprobamos que las listas no sean NULL
        return -1;
    else {
        inserta(p->sig->elemento, q, lb); // Insertamos el elemento de la lista A en la posicion de la lista B
        suprime(p, la); // Borramos el elemento de la lista A
    }
    return 0;
}
int concatenarListas(Lista *la, Lista *lb) {

    if (la == NULL || la->raiz == NULL || lb == NULL || lb->raiz == NULL)  // Comprobamos que las listas no sean NULL 
        return -1;
    else {
        while (!vacia(lb)) { // Iteramos  la lista B hasta que esté vacia
            traspasarNodo(lb->raiz, lb, fin(la), la); // Traspasamos el nodo de la lista B a la lista A
        }
    }
    return 0;
}