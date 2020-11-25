typedef unsigned char bit;
struct Nodo *primero = NULL; 
struct Persona {
char * nombre;
int edad;
bit id;
};
struct Nodo {
struct Persona persona;
struct Nodo * sig;
};
void agregarPersona(const char *nombre, int edad, bit id) {
struct Nodo * nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
nuevo->sig = NULL; 
nuevo->persona.nombre = (char*)malloc(1); strcpy(nuevo->persona.nombre, nombre);
nuevo->persona.edad = edad;
nuevo->persona.id = id;
if(primero == NULL) {
primero = nuevo;
} else{
nuevo->sig = primero;
primero = nuevo;
}
}
unsigned char aislarBit(int n, unsigned char ID) {
unsigned char bit = ID;
bit = bit << (n-1);
bit = bit >> 7;
return bit;
}
void imprimir() {
puts("\nLista de personas:\n");
struct Nodo * aux = primero;
while(aux != NULL) {
printf("Nombre: %s, Edad: %i, ID: %i, Bit2: %d\n", aux->persona.nombre, aux->persona.edad, aux->persona.id, aislarBit(2, aux->persona.id));
aux = aux->sig;
}
}
int main() {
agregarPersona("Ronald", 21, 12);
agregarPersona("Rose", 18, 13);
agregarPersona("Ashly", 17, 12);
agregarPersona("Jack", 14, 18);
agregarPersona("Chester", 13, 21);
agregarPersona("Mike", 12, 32);
agregarPersona("Jen", 38, 21);
imprimir();
return 0;
}
