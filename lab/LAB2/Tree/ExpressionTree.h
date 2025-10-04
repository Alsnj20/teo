#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include "../Node/Node.h"
#include <string>

class ExpressionTree
{
private:
  Node *root;

  // Input a string expression
  Node *buildTree(const string &expr);
  double evaluate(Node *node, bool showSteps);
  // Recorridos
  void inorder(Node *node);
  void preorder(Node *node);
  void postorder(Node *node);

  void deleteTree(Node *node);

public:
  ExpressionTree();
  ExpressionTree(const std::string &expr);
  ~ExpressionTree();

  double evaluateNode(bool showSteps = false);
  // Recorridos
  // I R D
  void showInorder();
  // R I D
  void showPreorder();
  // I D R
  void showPostorder();

  void clearTree();
};

#endif