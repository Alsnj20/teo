#include "operations.cpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

class Historial
{
private:
  vector<string> operations;

public:
  void add(const string &input, double result)
  {
    operations.push_back(input + " = " + to_string(result));
  }

  void show()
  {
    cout << "Historial de operaciones:" << endl;
    for (const auto &op : operations)
    {
      cout << op << endl;
    }
  }
};

class InputProcessor
{
public:
  vector<double> getNumber(const string &input, char ope)
  {
    vector<double> numbers;
    string token;
    string cleaned;

    // Remove spaces
    for (char c : input)
    {
      if (!isspace(c))
        cleaned.push_back(c);
    }

    stringstream ss(cleaned);

    while (getline(ss, token, ope))
    {
      if (!token.empty())
      {
        try
        {
          numbers.push_back(stod(token));
        }
        catch (const invalid_argument &e)
        {
          throw invalid_argument("Invalid number: " + token);
        }
      }
    }
    return numbers;
  }
};

class Calculator
{
private:
  Historial historial;
  InputProcessor inputProcessor;

public:
  double calculate(const string &input)
  {
    char ope = 0;
    if (input.find('+') != string::npos)
    {
      ope = '+';
    }
    else if (input.find('-') != string::npos)
    {
      ope = '-';
    }
    else if (input.find('*') != string::npos)
    {
      ope = '*';
    }
    else if (input.find('/') != string::npos)
    {
      ope = '/';
    }
    else
    {
      throw invalid_argument("Operation not supported");
    }

    vector<double> numbers = inputProcessor.getNumber(input, ope);

    Operation *operation = nullptr;
    switch (ope)
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
      throw invalid_argument("Operation not supported");
    }

    double result = operation->execute(numbers);
    historial.add(input, result);
    delete operation;
    return result;
  }

  void showHistory()
  {
    historial.show();
  }

  void calculateFromFile(const string &inFile, const string &outFile)
  {
    ifstream file(inFile);
    ofstream out(outFile, ios::app);
    if (!file.is_open())
    {
      throw runtime_error("Could not open file");
    }
    string line;
    while (getline(file, line))
    {
      try
      {
        double result = calculate(line);
        out << line << " = " << result << endl;
      }
      catch (const exception &e)
      {
        out << line << " : Error - " << e.what() << endl;
      }
    }
    file.close();
    out.close();
  }
};
