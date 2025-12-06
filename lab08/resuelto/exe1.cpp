#include <iostream>
using namespace std;

template <typename T>
T suma(T a, T b)
{
  return (a + b);
}

int main()
{
  cout << "Suma entre 5 y 10: " << suma(5, 10) << endl;           // int
  cout << "Suma entre 3.14 y 2.71: " << suma(3.14, 2.71) << endl; // double
  cout << "Suma entre 6.5f y 2.5f: " << suma(6.5f, 2.5f) << endl; // float
  return 0;
}
