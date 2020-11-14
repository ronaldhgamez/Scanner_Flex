#include <stdio.h>

char * comandos[] = {
    "pdflatex latex.tex",           // comando para generar el pdf
    "evince -f presentation.pdf"    // comando para abrir el pdf generado en pantalla completa
};

int main(int argc, char** argv) {

    return 0;
}
