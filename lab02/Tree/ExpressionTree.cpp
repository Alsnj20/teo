#include "ExpressionTree.h"
#include "../Operation/operation.h"
#include <iostream>
#include <cctype>
#include <stdexcept>

// Initialization
ExpressionTree::ExpressionTree() : root(nullptr) {}

ExpressionTree::ExpressionTree(const string &expr) : root(nullptr)
{
  root = buildTree(expr);
}
ExpressionTree::~ExpressionTree()
{
  clearTree();
}

void ExpressionTree::clearTree()
{
  deleteTree(root);
  root = nullptr;
}

void ExpressionTree::deleteTree(Node *node)
{
  delete node;
}

Node *ExpressionTree::buildTree(const string &expr)
{
  if (expr.empty())
    return nullptr;

  if (isdigit(expr[0]) || (expr[0] == '-' && expr.size() > 1 && isdigit(expr[1])))
  {
    return new Node(stod(expr));
  }

  char op = expr[0];
  Operation *operation = nullptr;

  switch (op)
  {
  case '+':
    operation = new Addition();
    break;
  case '-':
    operation = new Subtraction();
    break;
  case '*':
    operation = new Multiplication();
    break;
  case '/':
    operation = new Division();
    break;
  default:
    throw std::invalid_argument("Invalid operator");
  }

  int balance = 0;
  size_t splitPos = string::npos;

  for (size_t i = 1; i < expr.size(); ++i)
  {
    if (expr[i] == '(')
      balance++;
    else if (expr[i] == ')')
      balance--;
    else if (balance == 0 && (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'))
    {
      splitPos = i;
      break;
    }
  }

  if (splitPos == string::npos)
    throw std::invalid_argument("Invalid expression format");

  string leftExpr = expr.substr(1, splitPos - 1);
  string rightExpr = expr.substr(splitPos + 1, expr.size() - splitPos - 2);

  Node *leftNode = buildTree(leftExpr);
  Node *rightNode = buildTree(rightExpr);

  return new Node(operation, leftNode, rightNode);
}

double ExpressionTree::evaluate(Node *node, bool showSteps)
{
  if (!node)
    throw std::invalid_argument("Invalid node");

  if (!node->isOperator)
    return node->value;

  double leftVal = evaluate(node->left, showSteps);
  double rightVal = evaluate(node->right, showSteps);
  double result = node->ope->execute(leftVal, rightVal);

  if (showSteps)
  {
    std::cout << leftVal << " " << node->ope->getSymbol() << " " << rightVal << " = " << result << std::endl;
  }

  return result;
}

double ExpressionTree::evaluateNode(bool showSteps)
{
  return evaluate(root, showSteps);
}

// Recorridos
void ExpressionTree::inorder(Node *node)
{
  if (node)
  {
    if (node->isOperator)
      std::cout << "(";
    inorder(node->left);
    if (node->isOperator)
      std::cout << " " << node->ope->getSymbol() << " ";
    else
      std::cout << node->value;
    inorder(node->right);
    if (node->isOperator)
      std::cout << ")";
  }
}

void ExpressionTree::preorder(Node *node)
{
  if (node)
  {
    if (node->isOperator)
      std::cout << node->ope->getSymbol() << " ";
    else
      std::cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
  }
}

void ExpressionTree::postorder(Node *node)
{
  if (node)
  {
    postorder(node->left);
    postorder(node->right);
    if (node->isOperator)
      std::cout << node->ope->getSymbol() << " ";
    else
      std::cout << node->value << " ";
  }
}

void ExpressionTree::showInorder()
{
  inorder(root);
}
void ExpressionTree::showPreorder()
{
  preorder(root);
}
void ExpressionTree::showPostorder()
{
  postorder(root);
}
