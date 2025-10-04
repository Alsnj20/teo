#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class History
{
private:
  vector<string> records;

public:
  void add(const string &expr, double result);
  void show() const;
};

#endif