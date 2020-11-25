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
    if(tempFile == NULL)
        tempFile = fopen("temp_file.c", "w");

    // Write the instruction into temporal file
    fputc(c, tempFile);
}

/**
 * Genera un nuevo archivo temporal preprocesado
 * @param file
 * @return
 */
int preprocesar (char * file) {

    FILE *arc_procesado = NULL;  // CODIGO FUENTE ORIGINAL

    // ABRE EL FUENTE ORIGINAL EN MODO LECTURA
    if ((arc_procesado = fopen(file, "r")) == NULL) {
        printf("No se encuentra la ruta del archivo: %s\n", file);
        return -1;
    }


    char line [250];
    do{
        // LECTURA DE LA LINEA
        fscanf (arc_procesado, "%[^\n]", line);

        // IGNORAR PRIMERAS LINEAS EN CASO DE QUE VENGAN EN BLANCO
        if(line[0] == '@')
            continue;

        // SI ES UN COMENTARIO CON "//" IGNORA EL RESTO DE LA LINEA
        if ( (line[0] == '/') && (line[1] == '/') )
            continue;


        int i = 0;      // PARA ITERAR LA LINEA
        int estado = i;
        int espacio = 0;    // para añadir espacio con defines

        // LA LINEA ES UNA DIRECTIVA DEL PREPROCESADOR
        if(line[i] == '#') {

            i++;
            // PARA SABER SI ES INCLUDE O DEFINE. SI ES CUALQUIER OTRA SE ESCRIBE LITERALMENTE.
            int esIncludeODef = 1; // TRUE INICIALMENTE

            // IGNORA (SI LOS HAY) ESPACIOS EN BLANCO DESPUES DEL CARACTER: #
            while(line[i] == ' ')
                i++;

            if (line[i] == 'i' && line[i + 1] == 'n') {   // VALIDA SI ES UNA DIRECTIVA INCLUDE

                // IGNORA CARACTERES HASTA VERIFICAR SI USA COMILLAS O BOQUITAS
                while(line[i] != '<' && line[i] != '"')
                    i++;

                // PARA VALIDAR SI EL ARCHIVO A INCLUIR ESTA EN DIRECTORIO ACTUAL O EN EL DE C
                int carpetaActual = 0;

                if(line[i] == '"') {
                    carpetaActual = 1; // TRUE
                }

                char buffer[] = "/usr/include/";
                char buffer2[] = "/home/ronaldhg/Escritorio/Proyecto_Flex/Project/test/";

                i++;
                // COPIA DEL NOMBRE DEL FICHERO A INCLUIR
                while(line[i] != '>' && line[i] != '"') {
                    if (carpetaActual == 0)
                        strncat(buffer, &line[i], 1);
                    else
                        strncat(buffer2, &line[i], 1);
                    i++;
                }

                // BUSCA EN EL DIRECTORIO ACTUAL
                if (carpetaActual == 1) {
                    printf("buffer 2: %s \n", buffer2);
                    preprocesar(buffer2);     // LLAMADA RECURSIVA CON LA DIRECTIVA
                } else {
                    //printf("buffer 1: %s \n\n", buffer);
                    //preprocesar(buffer);

                    // POR EL MOMENTO LA INCLUYE LITERALMETE...
                    i = estado;
                    esIncludeODef = 0;
                    espacio = 1;

                    /* EN PROCESO */
                }

            } else if(line[i] == 'd') {    // VALIDA SI ES UNA DIRECTIVA DEFINE
                // POR EL MOMENTO LA INCLUYE LITERALMETE...
                i = estado;
                esIncludeODef = 0;
                espacio = 1;

                /* EN PROCESO */

            } else {
                // CUALQUIER OTRA DIRECTIVA DIREFENTE A INCLUDE O DEFINE SE ESCRIBE LITERALMENTE
                i = estado;
                esIncludeODef = 0;  // INDICAMOS QUE NO ES NI INCLUDE NI DEFINE
            }
            if (esIncludeODef)
                continue;   // SIGUIENTE LINEA DEL ARCHIVO
        }

        int bool = 0;
        while (line[i] != '\0') {
            bool = 0;
            // IGNORA COMENTARIOS SEGUIDOS DE UNA INSTRUCCION
            if (line[i] == '/' && line[i+1] == '/') // <- POR EJEMPLO ESTE
                break;

            // Evitar espacios de mas
            else if(line[i] == ' ')
                while (line[i+1] == ' ')
                    i++;

            /* ELIMINA ESTOS COMENTARIOS INCLUYENDO CON SALTOS DE LINEA */
            else if (line[i] == '/' && line[i+1] == '*') {
                i+=2;

                if (line[i] == '\0') {
                    // Next line: valida que no sea el fin de linea
                    fscanf (arc_procesado, " %[^\n]", line);
                    // Si aun hay lineas continua
                    i = 0; // Como escaneo una nueva linea, se reinicia contador
                }
                do{
                    while(line[i] != '*') {
                        if (line[i] == '\0') {
                            // Next line: valida que no sea el fin de linea
                            fscanf (arc_procesado, " %[^\n]", line);
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

            // ESCRIBE EL CARACTER EN EL ARCHIVO TEMPORAL
            /////////////printf("%c", line[i]);
            insertIntoTempFile(line[i]);
            i++;
        }

        // Necesario para evitar que deje reglones en blanco en ciertas ocaciones
        if (bool == 0 || espacio == 1) {
            insertIntoTempFile('\n');
            /////////////printf("\n");
        }

    }while (fscanf (arc_procesado, " %[^\n]", line) != EOF);

    fclose(arc_procesado);   // FINALMENTE CIERRA EL ARCHIVO PROCESADO

    return 1;
}

int preprocesador(char * file) {
    int n = preprocesar(file);
    fclose(tempFile);
    tempFile = NULL;
    return n;
}