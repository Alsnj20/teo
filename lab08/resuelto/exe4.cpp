#include <iostream>

template <typename T>
class Stack
{
private:
  int size;
  int top;
  T *arr;

public:
  Stack(int size)
  {
    this->size = size;
    this->top = -1;
    this->arr = new T[size];
  }
  ~Stack()
  {
    delete[] arr;
  }

  void push(T value)
  {
    if (top == size - 1)
    {
      std::cout << "Stack Overflow" << std::endl;
      return;
    }
    arr[++top] = value;
  }

  T pop()
  {
    if (top == -1)
    {
      std::cout << "Stack Underflow" << std::endl;
      return T(); // Return default value of T
    }
    return arr[top--];
  }

  void show()
  {
    for (int i = top; i >= 0; i--)
    {
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }
};

int main()
{
  Stack<int> intStack(5);
  intStack.push(10);
  intStack.push(20);
  intStack.push(30);
  intStack.show();
  std::cout << "Popped: " << intStack.pop() << std::endl;
  intStack.show();
  std::cout << "-----------------" << std::endl;
  Stack<std::string> stringStack(3);
  stringStack.push("Hello");
  stringStack.push("World");
  stringStack.show();
  std::cout << "Popped: " << stringStack.pop() << std::endl;
  stringStack.show();

  return 0;
}