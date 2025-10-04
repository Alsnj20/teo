#include "History.h"

void History::add(const std::string &expr, double result)
{
  records.push_back(expr + " = " + std::to_string(result));
}

void History::show() const
{
  std::cout << "\nHistorial de operaciones:\n";
  for (const auto &r : records)
  {
    std::cout << r << std::endl;
  }
}