#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

class Persona
{
private:
  string name;
  string lastName;

public:
  // Constructor
  Persona(const string &name, const string &lastName);

  // Destructor
  virtual ~Persona();

  // Métodos get and set
  string getName() const;
  string getLastName() const;
  string getFullName() const;

  void setName(const string &name);
  void setLastName(const string &lastName);

  virtual void showData() const = 0;
};

#endif