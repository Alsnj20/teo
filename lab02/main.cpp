#include <iostream>
#include "./Tree/ExpressionTree.h"
#include "./History/History.h"
using namespace std;

int main()
{
  ExpressionTree tree;
  History history;

  string expr = "(12+(4*3))";
  tree = ExpressionTree(expr);

  cout << "Evaluacion paso a paso:\n";
  try
  {
    double result = tree.evaluateNode(true);
    cout << "Resultado final: " << result << endl;
    history.add(expr, result);
  }
  catch (const exception &e)
  {
    cout << "Error: " << e.what() << endl;
    return 1;
  }

  cout << "Preorden: ";
  tree.showPreorder();
  cout << "Inorden: ";
  tree.showInorder();
  cout << "Postorden: ";
  tree.showPostorder();

  history.show();

  return 0;
}
