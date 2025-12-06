#include <iostream>
using namespace std;

// Plantilla de función para devolver el máximo de dos valores
template <typename T>
T suma(T a, T b)
{
  return (a + b);
}

int main()
{
  cout << "Suma entre 5 y 10: " << suma(5, 10) << endl;               // int
  cout << "Suma entre 3.14f y 2.71f: " << suma(3.14f, 2.71f) << endl; // float
  cout << "Suma entre 'a' y 'z': " << suma('a', 'z') << endl;         // char
  return 0;
}
