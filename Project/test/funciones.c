int suma(int x, int y) {
    int z = x + y;
    return z;
}

int resta(int x, int y) {
    int z = x - y;
    return z;
}

int esOperando (char p) {
    if ((p == '0') || (p == '1') || (p == '2') || (p == '3') || (p == '4') ||
        (p == '5') || (p == '6') || (p == '7') || (p == '8') || (p == '9')) {
        return 1;
    }
    return 0;
}

int esOperador (char p) {
    if ((p == '+') || (p == '-') || (p == '*') || (p == '/')) {
        return 1;
    }
    return 0;
}