#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int pilaCreaVacia(Pila *p){
	if(NULL == p) 
        return -1;
	*p = NULL;
	return 0;
}

int pilaVacia(Pila *p){
	if(NULL == p) 
        return -1;

	return (NULL == *p);
}

int pilaInserta(Pila *p,tipoElemento elemento){
	if(NULL == p) 
        return -1;

	tipoCelda*c;
	if(NULL == (c = malloc(sizeof(tipoCelda))) ) 
        return -2;
    
	c->elemento = elemento;
	c->sig = NULL;

	if(NULL == *p) //Si la pila esta vacia el nuevo elemento es el primero y sino, el nuevo elemento es el siguiente.
		*p = c;
	else{
		c->sig = *p; 
		*p = c;
	}
	return 0; 
}

tipoElemento pilaSuprime(Pila *p){
	if(NULL == p) // Si la pila no existe no se puede suprimir
        return -1;
	if(NULL == *p) //Si la pila esta vacia no se puede suprimir
        return -2;
	
	tipoCelda *aBorrar = *p;
	tipoElemento c = aBorrar->elemento;

	*p = (*p)->sig;
	free(aBorrar);

	return c;
}
