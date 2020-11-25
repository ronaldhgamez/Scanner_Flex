#include <stdio.h>
#include <stdlib.h>

void piramide();
void modificar(); // Modificar datos de variables autilizando punteros.
void buscarChar(); // Buscar la primer ocurrencia de un char en una cadena utilizando punteros.
void buscarFrase(); // Lo mismo pero con palabras.
void agregarCalzado();
void zapateria();

struct Calzado {
    struct Calzado *sig;
    char *marca;
    int *precio;
    int *talla;
};

struct Calzado *primero = NULL;

int main() {
    //piramide();
    //modificar();
    //buscarChar();
    //buscarFrase();
    zapateria();
    return 0;
}

/**
 * Dado un número entero, imprimir una pirámide con el tamaño dado por el usuario.
 */
void piramide() {

    int *tam = NULL;
    tam = (int*) malloc(1);  // Ask for memory.

    puts("\nAltura de piramide: ");
    scanf("%i", tam);

    int esp = *tam - 1;
    int ast = 1;
    for (int linea = 0; linea < *tam; ++linea) {
        for (int i = 0; i < esp; ++i) // Imprime espacios...
            putchar(' ');
        for (int j = 0; j < ast; ++j) // Imprime dolares...
            putchar('$');
        esp--;
        ast += 2;
        puts("");
    }
}

void modificar() {

    int edad = 21;
    float alt = 1.69;
    char gen = 'M';

    puts("\n___________Datos____________");
    printf("edad: %i \t -> %p\n", edad, &edad);
    printf("altura: %f -> %p\n", alt, &alt);
    printf("genero: %c \t -> %p\n", gen, &gen);

    int *pEdad = &edad;
    float *pAlt = &alt;
    char *pGen = &gen;

    *pEdad = *pEdad + 1;
    *pAlt = *pAlt + 0.01;
    *pGen = 'F';

    puts("\n________Nuevos Datos________");
    printf("edad: %i \t -> %p\n", edad, &edad);
    printf("altura: %f -> %p\n", alt, &alt);
    printf("genero: %c \t -> %p\n", gen, &gen);

    puts("\n_____Direccion Punteros_____");
    printf("pEdad -> %p\n", pEdad);
    printf("pAlt: -> %p\n", pAlt);
    printf("pGen: -> %p\n", pGen);

    puts("\n_____Contenido Punteros_____");
    printf("pEdad -> %i\n", *pEdad);
    printf("pAlt: -> %f\n", *pAlt);
    printf("pGen: -> %c\n", *pGen);
}

void buscarChar() {

    char *cadena = "the way that I need you";
    //char *cadena = (char*) malloc(1000);
    //puts("Escriba cadena: ");
    //gets(cadena); // No lee mas de 19 si malloc(1)...

    char *c = "o";
    //char *c = (char*) malloc(1);
    //puts("Escriba char a buscar: ");
    //fflush(stdin);
    //*c = getchar();

    int i = 0;
    while(cadena[i]) {
        if(cadena[i] == *c) {
            printf("\nPrimera ocurrencia de \"%c\" en la posicion %i:", *c, i);
            printf("\n%s\n", cadena);
            for (int j = 0; j <= i; ++j) {
                if(j == i) {
                    putchar('^');
                    return;
                }
                putchar(' ');
            }
        }
        i++;
    }
    printf("\nEl char \"%c\" no existe en la cadena.", *c);
}

void buscarFrase() {

    char *frase = "and though you will no wait for me, I'll wait for you.";
    char *palab = "you";
    //char *frase = (char*) malloc(1000);
    //char *palab = (char*) malloc(1);

    int i = 0, t = 0, c = 0;

    while(frase[i]) {
        if(frase[i] != ' ') {
            if (frase[i] == palab[t]) {
                t++;
            }else {
                t = 0;
            }
        }else if(!palab[t]) {
            printf("La palabra existe a partir de la posicion %d.", c);
            return;
        }else {
            c = i;
            t = 0;
        }
        i++;
    }
    if(t > 0) { // Necesario para cuando la palabra está al final...
        printf("La palabra existe al final.");
        return;
    }
    puts("La no palabra existe dentro de la frase.");
}

void imprimirTodos() {
    puts("\n__________Lista de zapatos_________");
    struct Calzado *aux = primero;
    int c = 1;
    while(aux != NULL) {
        printf("%i) Marca: %s, Precio: %i, Talla: %i\n", c, aux->marca, aux->precio, aux->talla);
        aux = aux->sig;
        c++;
    }
}

void imprimirPorTalla(int *t) {
    printf("\n__________Lista Talla %i_________\n", *t);
    struct Calzado *aux = primero;
    int c = 1;
    while(aux != NULL) {
        if((int)aux->talla == *t) {
            printf("%i) Marca: %s, Precio: %i, Talla: %i\n", c, aux->marca, aux->precio, aux->talla);
        }
        aux = aux->sig;
        c++;
    }
    printf("\n____________Fin de lista_________\n");
}

void zapateria() {
    agregarCalzado("Adidas", 54000, 38);
    agregarCalzado("Converse", 40000, 38);
    agregarCalzado("DC", 24000, 39);
    agregarCalzado("Nike", 30000, 35);
    agregarCalzado("Nike", 55000, 39);
    agregarCalzado("DC", 28000, 41);
    agregarCalzado("Converse", 38000, 40);
    agregarCalzado("Adidas", 23000, 35);
    agregarCalzado("Carterpilar", 24000, 39);
    agregarCalzado("Nike", 25000, 37);

    while(1) {
        puts("\n****** Menu Zapateria, Bienvenido(a) *****");
        puts("1) Agregar zapato \n2) Ver por talla \n3) Inventario \n4) Salir");
        int option;
        printf("-> "); scanf("%i", &option);

        if(option == 4)
            break;

        switch (option) {
            case 1: {
                char *marca = (char*) malloc(1);
                int precio, talla;

                printf("Marca: "); fflush(stdin); gets(marca);
                printf("Precio: "); scanf("%i", &precio);
                printf("Talla: "); scanf("%i", &talla);

                if(34 > talla || 44 < talla) {
                    printf("Error en talla, unicamente de 34 a 44.\n");
                    break;
                }

                agregarCalzado(marca, precio, talla);
                puts("*** Agregado con exito! ***");
                break;
            }
            case 2: {
                puts("\nQue talla busca?");
                int talla; scanf("%i", &talla);
                imprimirPorTalla(&talla);
                break;
            }
            case 3: {
                imprimirTodos();
                break;
            }
            default:
                puts("Opcion invalida!");
        }
    }
}

void agregarCalzado(char *marca, int *precio, int *talla) {

    struct Calzado *nuevo = (struct Calzado*) malloc(sizeof(struct Calzado));
    nuevo->sig = NULL;

    nuevo->marca = (char*) malloc(1);
    nuevo->precio = (int*) malloc(1);
    nuevo->talla = (int*) malloc(1);

    nuevo->marca = marca;
    nuevo->precio = precio;
    nuevo->talla = talla;

    if(primero == NULL) {
        primero = nuevo;
    }else{
        nuevo->sig = primero;
        primero = nuevo;
    }
}
