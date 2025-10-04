#include "Persona.h"
#include <iostream>

Persona::Persona(const std::string &name, const std::string &lastName)
    : name(name), lastName(lastName) {}

Persona::~Persona() {}

std::string Persona::getName() const
{
  return name;
}

std::string Persona::getLastName() const
{
  return lastName;
}

std::string Persona::getFullName() const
{
  return name + " " + lastName;
}

void Persona::setName(const std::string &name)
{
  this->name = name;
}

void Persona::setLastName(const std::string &lastName)
{
  this->lastName = lastName;
}