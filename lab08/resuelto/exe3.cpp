#include <iostream>

template <typename T>
class Contenedor
{
private:
  T array[4];

public:
  T get(int x)
  {
    return array[x];
  }
  void set(int x, T value)
  {
    array[x] = value;
  }
  void show() const
  {
    for (int i = 0; i < 4; ++i)
    {
      std::cout << array[i] << " ";
    }
    std::cout << std::endl;
  }
};

int main()
{
  // invocar a clase template
  Contenedor<int> x;
  x.set(0, 5);
  x.set(1, 10);
  x.set(2, 15);
  x.set(3, 20);
  x.show();

  std::cout << "-----------------" << std::endl;
  // invocar a clase template
  Contenedor<double> y;
  y.set(0, 5.5);
  y.set(1, 10.1);
  y.set(2, 15.2);
  y.set(3, 20.3);
  y.show();
  return 0;
}
