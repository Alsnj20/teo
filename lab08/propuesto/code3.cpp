#include <iostream>

template <class T = char, int N = 8>
class Common1
{
private:
  T data[N];

public:
  void set(int num, T value);
  T get(int num);
};

template <class T, int N>
void Common1<T, N>::set(int num, T value)
{
  if (num >= 0 && num < N)
  {
    data[num] = value;
  }
}

template <class T, int N>
T Common1<T, N>::get(int num)
{
  if (num >= 0 && num < N)
  {
    return data[num];
  }
}

int main()
{
  Common1<int, 5> objInt;
  objInt.set(0, 10);
  std::cout << "objInt[0]: " << objInt.get(0) << std::endl;
  std::cout << "objInt[4]: " << objInt.get(4) << std::endl;
  std::cout << "---------------------" << std::endl;
  Common1<float, 5> objFloat;
  objFloat.set(2, 3.1);
  std::cout << "objFloat[0]: " << objFloat.get(0) << std::endl;
  std::cout << "objFloat[1]: " << objFloat.get(2) << std::endl;

  return 0;
}