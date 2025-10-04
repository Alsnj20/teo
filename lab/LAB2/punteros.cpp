#include <iostream>
using namespace std;

class Persona {
public:
    string nombre;
    int edad;

    Persona(string n, int e) {
        nombre = n;
        edad = e;
    }

    void mostrar() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << endl;
    }
};

int main() {
    // Crear un objeto Persona
    Persona p1("Juan", 30);

    // Crear un puntero a Persona y apuntarlo al objeto p1
    Persona* ptr = &p1;

    // Acceder a miembros usando el puntero
    ptr->mostrar();

    // Modificar datos usando el puntero
    ptr->edad = 31;
    ptr->mostrar();

    return 0;
}