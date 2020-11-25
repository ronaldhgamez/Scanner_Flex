/* pruebas */
#define ALTO 100 /* VALOR 1 */
#define ANCHO 200/* VALOR 2 */

void multiplicar () {
    int d = 12;
    d /= ALTO;
    d+=ANCHO;
}

/**
 * Dado un número entero, imprimir una pirámide con el tamaño dado por el usuario.
 */
void piramide(int tam) {


    int esp = tam - 1;
    int ast = 1;
    for (int linea = 0; linea < tam; ++linea) {
        for (int i = 0; i < esp; ++i) // Imprime espacios...
            putchar(' ');
        for (int j = 0; j < ast; ++j) // Imprime dolares...
            putchar('$');
        esp--;
        ast += 2;
        puts("");
    }
}
