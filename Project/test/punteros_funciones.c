#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.c" /* INCLUSION DEL ARCHIVO */


typedef enum {OPERANDO, OPERADOR} Tipo;

struct Elemento {
    char dato;
    struct Elemento *sig;
};

struct Pila {
    struct Elemento *elemento;
    int contador;
};

struct Pila *pilaOperando = NULL;
struct Pila *pilaOperador = NULL;

struct Pila* crearPila() {
    struct Pila *pila = (struct Pila*) malloc(sizeof(struct Pila));
    pila->elemento = NULL;
    pila->contador = 0;
    return pila;
}

int isEmpty(struct Pila *pila) {
    if(pila->contador == 0) /* True: 1, False: 0 */
        return 1;
    return 0;
}

struct Elemento* top(struct Pila *p) { // devuelve ultimo elemento que entro en la pila.
    if(isEmpty(p) == 1)
        return NULL;
    return p->elemento;
}

struct Pila* pop(struct Pila *p) { // desencolar ultimo elemento que entro en la pila.
    if(isEmpty(p) == 1)
        return NULL;
    p->elemento = p->elemento->sig;
    p->contador--;
    return p;
}

struct Pila* push(struct Pila *pila, char dato) { // Encolar Ultimo en entrar, primero en salir (insercion al inicio).
    struct Elemento *nuevo = (struct Elemento*) malloc(sizeof(struct Elemento));

    nuevo->sig = NULL;
    nuevo->dato = dato;

    if(pila->elemento == NULL) {
        pila->elemento = nuevo;
    } else {
        nuevo->sig = pila->elemento;
        pila->elemento = nuevo;
    }
    pila->contador++;
    return pila;
}

void mostrarPila(struct Pila *p) {
    printf("\nMostrando pila");
    printf("\nTotal elementos %d\n", p->contador);

    struct Elemento *aux = p->elemento;
    while(aux != NULL) {
        printf("%c\n", aux->dato);
        aux = aux->sig;
    }
    printf("\nFin de pila\n");
}

int calculo (int x, int y, int (funcion)(int, int)) {
    int z = funcion(x, y);
    return z;
}

int recorrerExpPostfijo(char *p) {
    int z = 0;

    char expCopia[100];
    strcpy(expCopia, p);

    int i = 0;
    while(expCopia[i]) { // Recorrer expresion y crear postfijo.
        //printf("\nchar: %c", expCopia[i]);
        if(esOperando(expCopia[i]) == 1) {
            //printf("\nes numero...");
            pilaOperando = push(pilaOperando, expCopia[i]);
            //mostrarPila(pilaOperando);
        } else {
            //printf("\nes operador...");
            int x = top(pilaOperando)->dato - 0;
            printf("\nx: %d", x);
            pilaOperando = pop(pilaOperando);

            int y = top(pilaOperando)->dato - 0;
            printf("\ny: %d", y);
            pilaOperando = pop(pilaOperando);

            int resultado;
            if (expCopia[i] == '+') {
                resultado = calculo(x, y, suma);
                push(pilaOperando, (char) resultado);
            } else if (expCopia[i] == '-') {
                resultado = calculo(x, y, resta);
                push(pilaOperando, (char) resultado);
            }
        }
        i++;
    }

    return pilaOperando->elemento->dato;
}

int main() {

    char *exp = (char*) malloc(1);
    char *post;

    while(1) {
        pilaOperador = crearPila();
        pilaOperando = crearPila();
        puts("______________________________________________");
        puts("\nDigite la expresion (postfijo). \"close\" para salir: ");
        fflush(stdin);
        gets(exp);
        if(strcmp(exp, "close") == 0)
            break;

        //post = CrearExpPostfijo(exp);
        //printf("\nLa expresion en postfijo es: \n%s", post);

        printf("\nEl resultado de la evaluacion es: \n%d\n", recorrerExpPostfijo(exp));

        //free(post);
        free(pilaOperando);
        free(pilaOperador);
    }
    free(exp);
     return 0;
}