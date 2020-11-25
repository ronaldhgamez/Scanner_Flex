#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
char *expTelefonica = "(\\+[ ]*5[ -]*0[ -]*6[ -]*|5[ -]*0[ -]*6[ -]*)?([5678][ -]*)([0-9][ -]*){6}[0-9]";
char *expResidencia = "(\\+[ ]*5[ -]*0[ -]*6[ -]*|5[ -]*0[ -]*6[ -]*)?(2[ -]*)([0-9][ -]*){6}[0-9]";
regex_t regexTel;
regex_t regexRes;
struct Contacto *numTelefonicos = NULL;
struct Contacto *numResidenciales = NULL;
typedef enum {TELEFONO, RESIDENCIAL} Tipo;
struct Contacto {
char *tel;
Tipo tipo;
struct Contacto *sig;
};
char* getTipo(Tipo tipo) {
switch (tipo) {
case TELEFONO: return "telefono celular";
case RESIDENCIAL: return "residencial";
default: return "";
}
}
void insertar(char *tel, Tipo tipo) {
struct Contacto *nuevo = (struct Contacto*) malloc(sizeof(struct Contacto));
nuevo->sig = NULL;
nuevo->tel = (char*) malloc(100);
strcpy(nuevo->tel, tel);
nuevo->tipo = tipo;
if(tipo == TELEFONO) {
if (numTelefonicos == NULL)
numTelefonicos = nuevo;
else {
nuevo->sig = numTelefonicos;
numTelefonicos = nuevo;
}
} else if (tipo == RESIDENCIAL) {
if (numResidenciales == NULL)
numResidenciales = nuevo;
else {
nuevo->sig = numResidenciales;
numResidenciales = nuevo;
}
}
}
int clasificarCoincidencias (char *linea, regex_t regex, Tipo tipo) {
regmatch_t grupos;
while(1) {
if (regexec(&regex, linea, 1, &grupos, 0))
break; 
int inicio = 0;
inicio = grupos.rm_eo;
char copiaTel[strlen(linea) + 1];
strcpy(copiaTel, linea);
copiaTel[grupos.rm_eo] = 0;
linea += inicio;
insertar(copiaTel + grupos.rm_so, tipo);
}
return 0;
}
int leerArchivo(char *argv[]) {
FILE *txtFile = NULL;
txtFile = fopen(argv[1], "r"); 
if (txtFile == NULL)
return 0;
char linea [250]; 
do{
fscanf (txtFile, "%[^\n]", linea);
if (regexec(&regexTel, linea, 0, NULL, 0) != REG_NOMATCH) {
clasificarCoincidencias(linea, regexTel, TELEFONO);
}
if (regexec(&regexRes, linea, 0, NULL, 0) != REG_NOMATCH) {
clasificarCoincidencias(linea, regexRes, RESIDENCIAL);
}
}while (fscanf (txtFile, " %[^\n]", linea) != EOF);
fclose(txtFile); 
return 1;
}
int compilarRegexExpresions() {
int bool = regcomp(&regexTel, expTelefonica, REG_EXTENDED);
if (bool) {
printf("ERROR AL COMPILAR LA EXPRESION (expTelefonica)\n");
return bool;
}
bool = regcomp(&regexRes, expResidencia, REG_EXTENDED);
if (bool) {
printf("ERROR AL COMPILAR LA EXPRESION (expResidencial)\n");
return bool;
}
return bool;
}
void imprimir(struct Contacto *aux) {
puts("-----------------------------------------------------");
while(aux != NULL) {
printf("%s (%s)\n", aux->tel, getTipo(aux->tipo));
puts("-----------------------------------------------------");
aux = aux->sig;
}
}
void mostrarClasificacion() {
if(numResidenciales == NULL && numTelefonicos == NULL) {
puts("~ NO SE HA DETECTADO NINGUN NUMERO DE COSTA RICA.");
return;
}
puts("~ MOSTRANDO CLASIFICACION ENCONTRADA EN EL ARCHIVO ~");
if(numTelefonicos != NULL) {
puts("\nNUMEROS TELEFONICOS --->");
imprimir(numTelefonicos);
}
if(numResidenciales != NULL) {
puts("\nNUMEROS RESIDENCIALES --->");
imprimir(numResidenciales);
}
}
int main(int argc, char *argv[]) {
puts("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
puts("CLASIFICADOR DE NUMEROS DE COSTA RICA \nUSO DE EXPRESIONES REGULARES");
puts("DESARROLLADOR: RONALD HERRERA GAMEZ \nCORREO: RONALDHGAMEZ@GMAIL.COM");
puts("FECHA INICIO: 15/03/2020");
puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
if(compilarRegexExpresions() != 0) {
puts("\n~~~~~~~~~~~~~~~~~~ FIN DE PROGRAMA ~~~~~~~~~~~~~~~~~~\n\n");
exit(1); 
}
int leido = leerArchivo(argv); 
if (leido == 1) {
mostrarClasificacion();
} else {
printf("~ Error al abrir archivo. Ingrese ruta valida.\n");
}
puts("\n~~~~~~~~~~~~~~~~~~ FIN DE PROGRAMA ~~~~~~~~~~~~~~~~~~\n\n");
return 0;
}
