#include<stdio.h>
#include<string.h>

/**
 * El preprocesador en C
 * El preprocesador es un programa que forma parte del compilador y que “prepara” o modifica
 * el código fuente antes de ser traducido a código binario.
 * Recibe el archivo .c escrito y lo procesa y lo modifica para hacerle el trabajo más fácil
 * al compilador:
 *      1) Quita comentarios
 *      2) Quita espacios innecesarios
 *      3) Procesa las sentencias del preprocesador (include, define, etc)
 *
 * Lee linea a linea el archivo modifica el archivo. Cuando encuentra alguna directiva #include
 * quita esa línea y la reemplaza por el fuente original del archivo que está incluyendo
 * @return
 */

FILE *tempFile = NULL;  // CODIGO FUENTE TEMPORAL

/**
 * Escribe en el archivo temporal el caracter recibido.
 * @param instruction
 */
void insertIntoTempFile(char c) {
    // Crea el archivo temporal donde se almacenara el nuevo fuente del programa preprocesado
    if(tempFile == NULL) {
        tempFile = fopen("/home/ronaldhg/Escritorio/CProgram/temp_file.c", "w");
    }

    // Write the instruction into temporal file
    fputc(c, tempFile);
}

/**
 * Genera un nuevo archivo temporal preprocesado
 * @param file
 * @return
 */
int preprocesador (char * file) {

    FILE *origFile = NULL;  // CODIGO FUENTE ORIGINAL

    // ABRE EL FUENTE ORIGINAL EN MODO LECTURA
    if ((origFile = fopen(file, "r")) == NULL) {
        printf("Could not open source file\n");
        return -1;
    } else {
        char line [250];  // Salva temporalmente cada linea

        do{
            fscanf (origFile, "%[^\n]", line); // read line

            int i = 0;

            // Ignorar comentarios normales como este
            if (line[0] == '/' && line[1] == '/')
                continue;

            // Remplazar las directivas del preprocesador
            if(line[i] == '#') {
                i++;
                // Ignora los espacios despues de #
                while(line[i] == ' ')
                    i++;
                if (line[i] == 'i') { // include

                    while(line[i] != '<' && line[i] != '"')
                        i++;

                    int carpetaActual = 0;
                    if(line[i] == '"')
                        carpetaActual = 1;

                    // COPIA DEL NOMBRE DEL FICHERO A INCLUIR
                    char buffer[] = "/usr/include/";
                    char buffer2[] = "/home/ronaldhg/Escritorio/CProgram/";
                    //printf("buffer 1: %s \n\n", buffer);
                    //printf("buffer 2: %s \n\n", buffer2);

                    i++;
                    while(line[i] != '>' && line[i] != '"') {
                        if (carpetaActual == 0) {
                            strncat(buffer, &line[i], 1);
                        } else if(carpetaActual == 1) {
                            strncat(buffer2, &line[i], 1);
                        }
                        i++;
                    }

                    // LLAMADA RECURSIVA CON LA DIRECTIVA
                    if (carpetaActual == 1) {
                        printf("buffer 2: %s \n\n", buffer2);
                        preprocesador(buffer2);
                    } else {
                        printf("buffer 1: %s \n\n", buffer);
                        preprocesador(buffer2);
                    }
                } else {    // define
                    printf("define\n");
                }
                continue; // siguiente linea
            }

            int bool = 0;
            while (line[i] != '\0') {
                bool = 0;
                // Ignora comentarios que están seguidos de una instruccion (como este)
                if (line[i] == '/' && line[i+1] == '/') {
                    break;
                }
                // Evitar espacios de mas
                else if(line[i] == ' ') {
                    while (line[i+1] == ' ') {
                        //printf("-");
                        i++;
                    }
                }
                /* Eliminar estos comentarios incluyendo con salto de linea */
                else if (line[i] == '/' && line[i+1] == '*') {
                    i+=2;

                    if (line[i] == '\0') {
                        // Next line: valida que no sea el fin de linea
                        fscanf (origFile, " %[^\n]", line);
                        printf("\nnew line\n");
                        // Si aun hay lineas continua
                        i = 0; // Como escaneo una nueva linea, se reinicia contador
                    }
                    do{
                        while(line[i] != '*') {
                            if (line[i] == '\0') {
                                // Next line: valida que no sea el fin de linea
                                fscanf (origFile, " %[^\n]", line);
                                // Si aun hay lineas continua
                                i = 0; // Como escaneo una nueva linea, se reinicia contador
                                continue;
                            }
                            i += 1;
                        }
                        if (line[i] == '*' && line[i+1] == '/') {
                            i+=2;
                            break;
                        }
                        i++; // Ignora el '*'
                    } while(1);

                    // Ignora espacios en blanco que queden despues
                    while (line[i]==' ')
                        i++;
                    if (line[i]=='\0')
                        bool = 1;
                    continue;
                }
                printf("%c", line[i]);
                insertIntoTempFile(line[i]);
                i++;
            }
            // Necesario para evitar que deje reglones en blanco en ciertas ocaciones
            if (bool == 0) {
                insertIntoTempFile('\n');
                printf("\n");
            }

        }while (fscanf (origFile, " %[^\n]", line) != EOF);

        fclose(origFile);
    }
    return 1;
}

int main() {
//int main(int argc, char * argv[]) {
    preprocesador("/home/ronaldhg/Escritorio/CProgram/helloworld.c");
    fclose(tempFile);
    //preprocesador(argv[1]);
    //printf("%s", argv[1]);
    return 0;
}
