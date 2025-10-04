#include "Node.h"
#include "../Operation/operation.h"

Node::Node(double val) : isOperator(false), value(val), ope(nullptr), left(nullptr), right(nullptr) {}
Node::Node(Operation *ope, Node *l, Node *r) : isOperator(true), value(0), ope(ope), left(l), right(r) {}
Node::~Node()
{
  delete ope;
  delete left;
  delete right;
}