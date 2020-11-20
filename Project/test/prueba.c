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