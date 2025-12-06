#include <iostream>
#include <string>

template <typename T>
struct Node
{
  T data;
  Node *next;
  Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
  Node<T> *head;

public:
  LinkedList() : head(nullptr) {}
  ~LinkedList()
  {
    Node<T> *current = head;
    while (current != nullptr)
    {
      Node<T> *next = current->next;
      delete current;
      current = next;
    }
  }
  void insert(T value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (head == nullptr)
    {
      head = newNode;
    }
    else
    {
      Node<T> *temp = head;
      while (temp->next != nullptr)
      {
        temp = temp->next;
      }
      temp->next = newNode;
    }
  }
  void show() const
  {
    Node<T> *temp = head;
    while (temp != nullptr)
    {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }
};

int main()
{
  LinkedList<int> ages;
  ages.insert(20);
  ages.insert(50);
  ages.insert(35);
  ages.show();
  std::cout << "-----" << std::endl;
  LinkedList<std::string> words;
  words.insert("Hello");
  words.insert("World");
  words.insert("!");
  words.show();
  return 0;
}