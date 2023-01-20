#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"


int colaCreaVacia(Cola *c){
	if(NULL == c) return -1;
	//Establecemos ambos punteros a NULL.
	c->frente = c->fondo = NULL;
	return 0;
}

int colaVacia(Cola *c){
	if(NULL == c)  return -1;

	return (c->frente == NULL && c->fondo == NULL); // 0 si no esta vacia y 1 si esta vacia
}

int colaInserta(Cola *c, tipoElemento elemento){
	if(NULL == c) return -1;

	tipoCelda*celda;
	if(NULL == (celda = malloc(sizeof(tipoCelda))) )  return -2;

	celda->elemento = elemento;
	celda->sig = NULL;

	if(NULL == c->fondo) // La cola está vacia, insertamos el primer elemento.
		c->frente = c->fondo = celda;
	else // La cola no está vacia,insertamos en el siguiente.
		c->fondo = c->fondo->sig = celda;
	
	return 0;
}

tipoElemento colaSuprime(Cola *c){
	if(NULL == c) return -1;
	if(NULL==c->frente) return -2;

	tipoCelda*aBorrar = c->frente;
	tipoElemento valor = aBorrar->elemento;

	c->frente = aBorrar->sig; 
	if(aBorrar == c->fondo)
		c->fondo = c->frente;
	free(aBorrar);

	return valor;
}