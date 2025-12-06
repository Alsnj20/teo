#include <iostream>

template <typename T>
class Container
{
private:
  T element;

public:
  Container(T elem) : element(elem) {}
  T add()
  {
    return ++element;
  }
};

template <>
class Container<char>
{
private:
  char element;

public:
  Container(char elem) : element(elem) {}
  char upperCase()
  {
    if (element >= 'a' && element <= 'z')
    {
      return element += ('A' - 'a');
    }
    return element;
  }
};

int main()
{
  Container<int> cint(5);
  std::cout << "Incremented integer: " << cint.add() << std::endl;

  Container<char> charContainer('b');
  std::cout << "Uppercase character: " << charContainer.upperCase() << std::endl;

  return 0;
}