#include "Alumno.h"
#include <iostream>
#include <algorithm>

Alumno::Alumno(const std::string &name, const std::string &lastName,
               const std::string &code, int grade)
    : Persona(name, lastName), code(code), grade(grade)
{
  // Validar grado
  if (!isGradeValid(grade))
  {
    std::cout << "¡Advertencia! Grado inválido: " << grade
              << ". Debe estar entre 1 y 6." << std::endl;
  }
}

Alumno::~Alumno()
{
  clearMemory();
}

// getter
std::string Alumno::getCode() const
{
  return code;
}

int Alumno::getGrade() const
{
  return grade;
}

const std::vector<Tarea *> &Alumno::getAssignments() const
{
  return assignments;
}

// setter
void Alumno::setCode(const std::string &code)
{
  this->code = code;
}

void Alumno::setGrade(int grade)
{
  if (isGradeValid(grade))
  {
    this->grade = grade;
  }
  else
  {
    std::cout << "Error: Grado inválido. Debe estar entre 1 y 6." << std::endl;
  }
}

// Functionality
bool Alumno::isGradeValid(int grade)
{
  return grade >= 1 && grade <= 6;
}

void Alumno::addAssignment(Tarea *assignment)
{
  if (assignment != nullptr)
  {
    assignments.push_back(assignment);
    std::cout << "Tarea agregada al alumno " << code << std::endl;
  }
}

void Alumno::removeAssignment(const std::string &course, const std::string &teacher)
{
  auto it = std::find_if(assignments.begin(), assignments.end(),
                         [&course, &teacher](const Tarea *assignment)
                         {
                           return assignment->getCourse() == course && assignment->getTeacher() == teacher;
                         });

  if (it != assignments.end())
  {
    // clear memory
    delete *it;
    assignments.erase(it);
    std::cout << "Tarea eliminada del curso " << course << std::endl;
  }
  else
  {
    std::cout << "No se encontró la tarea especificada." << std::endl;
  }
}

int Alumno::countSubmittedAssignments() const
{
  int count = 0;
  for (const Tarea *assignment : assignments)
  {
    if (assignment->isDelivered())
    {
      count++;
    }
  }
  return count;
}

int Alumno::countPendingAssignments() const
{
  return getTotalAssignments() - countSubmittedAssignments();
}

int Alumno::getTotalAssignments() const
{
  return static_cast<int>(assignments.size());
}

double Alumno::getSubmissionPercentage() const
{
  int total = getTotalAssignments();
  if (total == 0)
    return 0.0;

  return (static_cast<double>(countSubmittedAssignments()) / total) * 100.0;
}

void Alumno::showData() const
{
  std::cout << "\n=== INFORMACIÓN DEL ALUMNO ===" << std::endl;
  std::cout << "Código: " << code << std::endl;
  std::cout << "Nombre completo: " << getFullName() << std::endl;
  std::cout << "Grado: " << grade << "° año de primaria" << std::endl;
  std::cout << "Total de tareas: " << getTotalAssignments() << std::endl;
  std::cout << "Tareas entregadas: " << countSubmittedAssignments() << std::endl;
  std::cout << "Tareas pendientes: " << countPendingAssignments() << std::endl;
  std::cout << "Porcentaje de entregas: " << getSubmissionPercentage() << "%" << std::endl;
  std::cout << "===============================" << std::endl;
}

void Alumno::showSubmittedAssignments() const
{
  std::cout << "\n=== TAREAS ENTREGADAS - " << getFullName() << " ===" << std::endl;
  bool hasAssignments = false;

  for (const Tarea *assignment : assignments)
  {
    if (assignment->isDelivered())
    {
      std::cout << "- " << assignment->getCourse() << " (Prof. " << assignment->getTeacher()
                << ") - Fecha: " << assignment->getDate() << std::endl;
      hasAssignments = true;
    }
  }

  if (!hasAssignments)
  {
    std::cout << "No hay tareas entregadas." << std::endl;
  }
  std::cout << "==============================================\n"
            << std::endl;
}

void Alumno::showPendingAssignments() const
{
  std::cout << "\n=== TAREAS PENDIENTES - " << getFullName() << " ===" << std::endl;
  bool hasAssignments = false;

  for (const Tarea *assignment : assignments)
  {
    if (!assignment->isDelivered())
    {
      std::cout << "- " << assignment->getCourse() << " (Prof. " << assignment->getTeacher()
                << ") - Fecha límite: " << assignment->getDate() << std::endl;
      hasAssignments = true;
    }
  }

  if (!hasAssignments)
  {
    std::cout << "No hay tareas pendientes." << std::endl;
  }
  std::cout << "===============================================\n"
            << std::endl;
}

void Alumno::showAllAssignments() const
{
  std::cout << "\n=== TODAS LAS TAREAS - " << getFullName() << " ===" << std::endl;

  if (assignments.empty())
  {
    std::cout << "No hay tareas asignadas." << std::endl;
  }
  else
  {
    for (size_t i = 0; i < assignments.size(); ++i)
    {
      const Tarea *assignment = assignments[i];
      std::cout << (i + 1) << ". " << assignment->getCourse()
                << " (Prof. " << assignment->getTeacher()
                << ") - " << assignment->getDeliveryStatus()
                << " - Fecha: " << assignment->getDate() << std::endl;
    }
  }
  std::cout << "============================================\n"
            << std::endl;
}

Tarea *Alumno::searchAssignment(const std::string &course, const std::string &teacher) const
{
  for (Tarea *assignment : assignments)
  {
    if (assignment->getCourse() == course && assignment->getTeacher() == teacher)
    {
      return assignment;
    }
  }
  return nullptr;
}

std::vector<Tarea *> Alumno::searchAssignmentsByCourse(const std::string &curso) const
{
  std::vector<Tarea *> resultado;
  for (Tarea *tarea : assignments)
  {
    if (tarea->getCourse() == curso)
    {
      resultado.push_back(tarea);
    }
  }
  return resultado;
}

std::vector<Tarea *> Alumno::searchAssignmentsByTeacher(const std::string &profesor) const
{
  std::vector<Tarea *> resultado;
  for (Tarea *tarea : assignments)
  {
    if (tarea->getTeacher() == profesor)
    {
      resultado.push_back(tarea);
    }
  }
  return resultado;
}

void Alumno::clearMemory()
{
  for (Tarea *tarea : assignments)
  {
    delete tarea;
  }
  assignments.clear();
}