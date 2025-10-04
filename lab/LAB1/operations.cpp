#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// Abstract class for operations
class Operation
{
public:
  virtual double execute(const vector<double> &numbers) = 0;
  virtual string getSymbol() const = 0;
  virtual ~Operation() = default;
};

// Operations
class Addition : public Operation
{
public:
  double execute(const vector<double> &numbers) override
  {
    double sum = 0;
    for (const auto &num : numbers)
    {
      sum += num;
    }
    return sum;
  }
  string getSymbol() const override
  {
    return "+";
  }
};

class Subtraction : public Operation
{
public:
  double execute(const vector<double> &numbers) override
  {
    if (numbers.empty())
      throw invalid_argument("No numbers provided");
    double result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i)
    {
      result -= numbers[i];
    }
    return result;
  }
  string getSymbol() const override
  {
    return "-";
  }
};

class Multiplication : public Operation
{
public:
  double execute(const vector<double> &numbers) override
  {
    if (numbers.empty())
      return 0;
    double product = 1;
    for (const auto &num : numbers)
    {
      product *= num;
    }
    return product;
  }
  string getSymbol() const override
  {
    return "*";
  }
};

class Division : public Operation
{
public:
  double execute(const vector<double> &numbers) override
  {
    if (numbers.empty())
      throw invalid_argument("No numbers provided");
    double result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i)
    {
      if (numbers[i] == 0)
        throw invalid_argument("Division by zero");
      result /= numbers[i];
    }
    return result;
  }
  string getSymbol() const override
  {
    return "/";
  }
};
