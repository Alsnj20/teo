#ifndef OPERATION_H
#define OPERATION_H
#include <string>
using namespace std;

class Operation
{
public:
  virtual double execute(double left, double right) = 0;
  virtual string getSymbol() const = 0;
  virtual ~Operation() = default;
};

class Addition : public Operation
{
public:
  double execute(double left, double right) override;
  string getSymbol() const override;
};

class Subtraction
    : public Operation
{
public:
  double execute(double left, double right) override;
  string getSymbol() const override;
};

class Multiplication
    : public Operation
{
public:
  double execute(double left, double right) override;
  string getSymbol() const override;
};

class Division
    : public Operation
{
public:
  double execute(double left, double right) override;
  string getSymbol() const override;
};

#endif