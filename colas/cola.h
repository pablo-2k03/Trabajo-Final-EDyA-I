#ifndef __COLA_H
#define __COLA_H

#ifndef __TIPO_ELEMENTO
#define __TIPO_ELEMENTO
typedef int tipoElemento;
#endif

#ifndef __TIPO_CELDA
#define __TIPO_CELDA
typedef struct tipoCelda {
	tipoElemento elemento; // tipoElemento -> int
	struct tipoCelda * sig;
	} tipoCelda; // tipoCelda -> Nodo
#endif

#define MAX 100
typedef struct {
        tipoCelda *frente, *fondo;
		int tamaño,frenteTam,fondoTam;
} Cola; // 2 Nodos (Frente y Fondo)

int colaCreaVacia(Cola *c);

// En vacía no sería necesario el paso por referencia,
// se hace por mantener la misma interfaz con la implementación
// de matrices
int colaVacia(Cola *c);

int colaInsertaC(Cola *c, tipoElemento elemento);

tipoElemento colaSuprime(Cola *c);

#endif
