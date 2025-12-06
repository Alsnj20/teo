#include <iostream>

template <typename T>
T greater(T a, T b)
{
  return (a > b) ? a : b;
}

int main()
{
  std::cout << "Mayor entre 5 y 10: " << greater(5, 10) << std::endl;                // int
  std::cout << "Mayor entre 3.14 y 2.71: " << greater(3.14, 2.71) << std::endl;      // double
  std::cout << "Mayor caracter entre 'A' y 'B': " << greater('A', 'B') << std::endl; // char
  return 0;
}
