#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int suma(int x, int y) {
    int z = x + y;
    return z;
}

int resta(int x, int y) {
    int z = x - y;
    return z;
}

int esOperando (char p) {
    if ((p == '0') || (p == '1') || (p == '2') || (p == '3') || (p == '4') ||
        (p == '5') || (p == '6') || (p == '7') || (p == '8') || (p == '9')) {
        return 1;
    }
    return 0;
}

int esOperador (char p) {
    if ((p == '+') || (p == '-') || (p == '*') || (p == '/')) {
        return 1;
    }
    return 0;
}

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

/*
char* CrearExpPostfijo (char *exp) {
    char expCopia[100];
    strcpy(expCopia, exp);

    char postfijo[100]; // Expresion postfijo a retornar.
    strcpy(postfijo, "");

    // Crear pila para meter operadores.
    struct Pila *pila = crearPila();

    int i = 0;
    while(expCopia[i]) { // Recorrer expresion y crear postfijo.

        if (esOperador(expCopia[i]) == 1) {
            while (isEmpty(pila) == 0) {
                strcat(postfijo, ",");
                //postfix += ",";

                strcat(postfijo, top(pila)->dato);
                //postfix += pila.top();

                pila = pop(pila);
                //pila.pop();
            }

            strcat(postfijo, ",");
            // postfix += ",";

            pila = push(pila, &expCopia[i]);
            // pila.push(expresion[i]);
        }
            // VALIDA SI EL CHAR ES UN OPERANDO(NUMERO).
        else if(esOperando(expCopia[i])) {
            strncpy(postfijo, expCopia, 1);
            //postfix +=expresion[i];
        } else if (expCopia[i] == '(') {
            pila = push(pila, &expCopia[i]);
            //pila.push(expresion[i]);
        } else if (expCopia[i] == ')') {
            // while(!pila.empty() && pila.top() !=  '(')
            while(isEmpty(pila) == 0 && strcmp(top(pila)->dato, "(") != 0) {
                strcat(postfijo, ",");
                // postfix+= ",";
                strcat(postfijo, top(pila)->dato);
                // postfix += pila.top();
                pila = pop(pila);
                // pila.pop();
            }
            pila = pop(pila);
        }
        i++;
    }

    while(isEmpty(pila) == 0)
    {
        strcat(postfijo, ",");
        // postfix+= ",";
        strcat(postfijo, top(pila)->dato);
        // postfix += pila.top();
        pila = pop(pila);
        // pila.pop();
    }
    // Lo hice así porque dio problemas...
    char *r = (char*) malloc(1);
    strcpy(r, postfijo);
    return r;
}*/

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