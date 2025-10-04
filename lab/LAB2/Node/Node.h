#ifndef NODE_H
#define NODE_H

#include <string>
#include "../Operation/operation.h"

struct Node
{
  bool isOperator;
  double value;
  Operation *ope;
  Node *left;
  Node *right;

  Node(double val);
  Node(Operation *ope, Node *l = nullptr, Node *r = nullptr);
  ~Node();
};

#endif