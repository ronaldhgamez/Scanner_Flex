#include <stdio.h>
#define ALTO 100 
#define ANCHO 200
int main() {
float _n = -.5e+12;
printf("%f \n", _n);
_n *= 2.e-1; printf("%f \n", _n);
int optal = 0x381; int optal_2 = 0X12; printf("Optal 1: %d\n", optal);
printf("Optal 2: %d\n", optal_2);
optal_2 ++;
optal += optal_2;
printf("resultado: %d\n", optal);
return 0;
}
