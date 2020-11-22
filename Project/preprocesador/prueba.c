if (bool == 1) {
    char actual = line[i];
    char siguie = line[i+1];

    while (actual != '\0') {
        if (actual == '*' &&  siguie == '/') {
            i+=2;
            bool = 0;
            actual = line[i];
            siguie = line[i + 1];
            break;
        }

        i++;
        actual = line[i];
        siguie = line[i + 1];
    }
    if(actual == '\0') {
        break;
    }
}

else if (actual == '/' && siguie == '*') { // Eliminar estos comentarios incluyendo con salto de linea
    i+=2;
    bool = 1;
    continue;
}
