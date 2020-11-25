
//#include <stdio.h>

#include "octal_hex_2.c"

/**
 * Probando numeros reales, octales
 * y hexadecimales
 * @return
 */
int main() {

    // Declaracion de un numero real
    float _n = -.5e+12;
    printf("%f \n", _n);

    _n *= 2.e-1;       /* multiplicado por  */
    printf("%f \n", _n);

    int hexadecimal = 0x31f;      /* representa 799 en decimal */
    int hexadecimal_2 = 0X1a2;     /* representa 418 en decimal */
    printf("hexadecimal 1: %d\n", hexadecimal);
    printf("hexadecimal 2: %d\n", hexadecimal_2);

    hexadecimal_2 ++;
    hexadecimal += hexadecimal_2;
    printf("resultado: %d\n", hexadecimal);
    // Salida 916

    int octal_1 = 023;/* representa 19 
    en decimal */
    int octal_2 = 0176; /* representa 126
    en decimal */
    printf("octal 1: %d\n", octal_1);
    printf("octal 2: %d\n", octal_2);
    printf("resultado: %d\n", (octal_1 + octal_2));

    multiplicar();
    piramide(10);

	return 0;
}
