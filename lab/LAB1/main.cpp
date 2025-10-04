#include "calculator.cpp"
#include <cassert>
using namespace std;

int main()
{
  Calculator calc;
  int option;
  string expr;

  do
  {
    cout << "\n=== MENU CALCULADORA ===\n";
    cout << "1. Ingresar operacion\n";
    cout << "2. Mostrar historial\n";
    cout << "3. Leer operaciones desde archivo\n";
    cout << "4. Ejecutar pruebas unitarias\n";
    cout << "5. Salir\n";
    cout << "Elija opcion: ";
    cin >> option;
    cin.ignore();

    try
    {
      if (option == 1)
      {
        cout << "Ingrese una operacion: ";
        getline(cin, expr);
        double result = calc.calculate(expr);
        cout << expr << " = " << result << endl;
      }
      else if (option == 2)
      {
        calc.showHistory();
      }
      else if (option == 3)
      {
        string inFile, outFile;
        cout << "Ingrese el nombre del archivo de entrada: ";
        getline(cin, inFile);
        cout << "Ingrese el nombre del archivo de salida: ";
        getline(cin, outFile);
        calc.calculateFromFile(inFile, outFile);
        cout << "Operaciones procesadas. Resultados guardados en " << outFile << endl;
      }
      else if (option == 4)
      {
        cout << "Ejecutando pruebas unitarias..." << endl;
        Addition add;
        assert(add.execute({2, 3, 5}) == 10);

        Subtraction sub;
        assert(sub.execute({10, 4, 1}) == 5);

        Multiplication mul;
        assert(mul.execute({2, 3, 4}) == 24);

        Division div;
        assert(div.execute({20, 2, 2}) == 5);

        cout << "Todas las pruebas pasaron correctamente" << endl;
      }
      else if (option == 5)
      {
        cout << "Saliendo..." << endl;
      }
      else
      {
        cout << "Opcion no valida. Intente de nuevo." << endl;
      }
    }
    catch (const exception &e)
    {
      cout << "Error: " << e.what() << endl;
    }
  } while (option != 5);
  return 0;
}
