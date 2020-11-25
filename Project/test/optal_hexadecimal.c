
#include <stdio.h>

#define ALTO 100 /* VALOR 1 */
#define ANCHO 200/* VALOR 2 */

/**
 * Probando numeros reales, optales
 * y hexadecimales
 * @return
 */
int main() {

    // Declaracion de un numero real
    float _n = -.5e+12;
    printf("%f \n", _n);

    _n *= 2.e-1;       /* multiplicado por  */
    printf("%f \n", _n);

    int optal = 0x381;      /* representa 897 en decimal */
    int optal_2 = 0X12;     /* representa 18 en decimal */
    printf("Optal 1: %d\n", optal);
    printf("Optal 2: %d\n", optal_2);

    optal_2 ++;
    optal += optal_2;
    printf("resultado: %d\n", optal);
    // Salida 916

	return 0;
}
