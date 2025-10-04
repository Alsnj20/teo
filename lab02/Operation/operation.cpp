#include "operation.h"
#include <stdexcept>

// Addition
double Addition::execute(double left, double right)
{
  return left + right;
}
string Addition::getSymbol() const
{
  return "+";
}

// Subtraction
double Subtraction::execute(double left, double right)
{
  return left - right;
}
string Subtraction::getSymbol() const
{
  return "-";
}

// Multiplication
double Multiplication::execute(double left, double right)
{
  return left * right;
}
string Multiplication::getSymbol() const
{
  return "*";
}

// Division
double Division::execute(double left, double right)
{
  if (right == 0)
    throw invalid_argument("Division by zero");
  return left / right;
}
string Division::getSymbol() const
{
  return "/";
}