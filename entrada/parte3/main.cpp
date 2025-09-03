#include <iostream>
using namespace std;

int invertir(int n);

int main()
{
    int numero;
    cout << "Ingrese un numero entero positivo: ";
    cin >> numero;

    cout << "Numero invertido: " << invertir(numero) << endl;

    return 0;
}