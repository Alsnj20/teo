#include "Profesor.h"
#include "Alumno.h"
#include <iostream>
#include <algorithm>
#include <set>

Profesor::Profesor(const std::string &name, const std::string &lastName,
                   const std::string &idTeacher)
    : Persona(name, lastName), idTeacher(idTeacher)
{
}

Profesor::~Profesor()
{
  clearStudentList();
}

std::string Profesor::getIdTeacher() const
{
  return idTeacher;
}

const std::vector<std::string> &Profesor::getCoursesTaught() const
{
  return coursesTaught;
}

const std::vector<Alumno *> &Profesor::getMyStudents() const
{
  return myStudents;
}

void Profesor::setIdTeacher(const std::string &idTeacher)
{
  this->idTeacher = idTeacher;
}

void Profesor::addCourse(const std::string &course)
{
  // Verificar que el curso no esté ya en la lista
  if (std::find(coursesTaught.begin(), coursesTaught.end(), course) == coursesTaught.end())
  {
    coursesTaught.push_back(course);
    std::cout << "Curso '" << course << "' agregado al profesor " << getFullName() << std::endl;
  }
  else
  {
    std::cout << "El profesor ya imparte el curso '" << course << "'" << std::endl;
  }
}

void Profesor::removeCourse(const std::string &course)
{
  auto it = std::find(coursesTaught.begin(), coursesTaught.end(), course);
  if (it != coursesTaught.end())
  {
    coursesTaught.erase(it);
    std::cout << "Curso '" << course << "' eliminado del profesor " << getFullName() << std::endl;
  }
  else
  {
    std::cout << "El profesor no imparte el curso '" << course << "'" << std::endl;
  }
}

bool Profesor::teachesCourse(const std::string &course) const
{
  return std::find(coursesTaught.begin(), coursesTaught.end(), course) != coursesTaught.end();
}

void Profesor::addStudent(Alumno *student)
{
  if (student != nullptr)
  {
    // Verificar que el alumno no esté ya en la lista
    if (!hasStudent(student->getCode()))
    {
      myStudents.push_back(student);
      std::cout << "Alumno " << student->getFullName()
                << " agregado a la lista del profesor " << getFullName() << std::endl;
    }
    else
    {
      std::cout << "El alumno ya está a cargo de este profesor." << std::endl;
    }
  }
}

void Profesor::removeStudent(const std::string &codigoAlumno)
{
  auto it = std::find_if(myStudents.begin(), myStudents.end(),
                         [&codigoAlumno](const Alumno *alumno)
                         {
                           return alumno->getCode() == codigoAlumno;
                         });

  if (it != myStudents.end())
  {
    std::cout << "Alumno " << (*it)->getFullName()
              << " eliminado de la lista del profesor " << getFullName() << std::endl;
    myStudents.erase(it);
  }
  else
  {
    std::cout << "No se encontró el alumno con código: " << codigoAlumno << std::endl;
  }
}

bool Profesor::hasStudent(const std::string &codigoAlumno) const
{
  return findStudent(codigoAlumno) != nullptr;
}

int Profesor::getStudentCount() const
{
  return static_cast<int>(myStudents.size());
}

int Profesor::getStudentCountByGrade(int grade) const
{
  int count = 0;
  for (const Alumno *student : myStudents)
  {
    if (student->getGrade() == grade)
    {
      count++;
    }
  }
  return count;
}

std::vector<Alumno *> Profesor::getStudentsByGrade(int grade) const
{
  std::vector<Alumno *> result;
  for (Alumno *student : myStudents)
  {
    if (student->getGrade() == grade)
    {
      result.push_back(student);
    }
  }
  return result;
}

Alumno *Profesor::findStudent(const std::string &studentCode) const
{
  for (Alumno *student : myStudents)
  {
    if (student->getCode() == studentCode)
    {
      return student;
    }
  }
  return nullptr;
}

std::vector<Alumno *> Profesor::findStudentsByName(const std::string &name) const
{
  std::vector<Alumno *> result;
  for (Alumno *student : myStudents)
  {
    if (student->getFullName().find(name) != std::string::npos)
    {
      result.push_back(student);
    }
  }
  return result;
}

void Profesor::showData() const
{
  std::cout << "\n=== INFORMACIÓN DEL PROFESOR ===" << std::endl;
  std::cout << "ID Profesor: " << idTeacher << std::endl;
  std::cout << "Nombre completo: " << getFullName() << std::endl;
  std::cout << "Cursos impartidos: " << coursesTaught.size() << std::endl;
  std::cout << "Alumnos a cargo: " << getStudentCount() << std::endl;
  std::cout << "Enseña en múltiples grados: " << (teachesInMultipleGrades() ? "Sí" : "No") << std::endl;
  std::cout << "=================================" << std::endl;
}

void Profesor::showMyStudents() const
{
  std::cout << "\n=== ALUMNOS A CARGO - " << getFullName() << " ===" << std::endl;

  if (myStudents.empty())
  {
    std::cout << "No tiene alumnos a cargo." << std::endl;
  }
  else
  {
    for (size_t i = 0; i < myStudents.size(); ++i)
    {
      const Alumno *student = myStudents[i];
      std::cout << (i + 1) << ". " << student->getFullName()
                << " (Código: " << student->getCode()
                << ", Grado: " << student->getGrade() << "°)" << std::endl;
    }
  }
  std::cout << "============================================\n"
            << std::endl;
}

void Profesor::showStudentsByGrade() const
{
  std::cout << "\n=== ALUMNOS POR GRADO - " << getFullName() << " ===" << std::endl;

  for (int grade = 1; grade <= 6; ++grade)
  {
    std::vector<Alumno *> studentsInGrade = getStudentsByGrade(grade);
    if (!studentsInGrade.empty())
    {
      std::cout << "\n"
                << grade << "° Grado (" << studentsInGrade.size() << " alumnos):" << std::endl;
      for (const Alumno *student : studentsInGrade)
      {
        std::cout << "  - " << student->getFullName()
                  << " (Código: " << student->getCode() << ")" << std::endl;
      }
    }
  }
  std::cout << "\n===============================================" << std::endl;
}

void Profesor::showCoursesTaught() const
{
  std::cout << "\n=== CURSOS IMPARTIDOS - " << getFullName() << " ===" << std::endl;

  if (coursesTaught.empty())
  {
    std::cout << "No imparte ningún curso registrado." << std::endl;
  }
  else
  {
    for (size_t i = 0; i < coursesTaught.size(); ++i)
    {
      std::cout << (i + 1) << ". " << coursesTaught[i] << std::endl;
    }
  }
  std::cout << "===============================================\n"
            << std::endl;
}

void Profesor::showStudentReport() const
{
  std::cout << "\n=== REPORTE DE ALUMNOS - " << getFullName() << " ===" << std::endl;
  std::cout << "Total de alumnos a cargo: " << getStudentCount() << std::endl;

  std::cout << "\nDistribución por grados:" << std::endl;
  for (int grade = 1; grade <= 6; ++grade)
  {
    int count = getStudentCountByGrade(grade);
    if (count > 0)
    {
      std::cout << "  " << grade << "° Grado: " << count << " alumno(s)" << std::endl;
    }
  }

  std::cout << "\nCursos impartidos: " << coursesTaught.size() << std::endl;
  std::cout << "================================================\n"
            << std::endl;
}

void Profesor::showTaskStatistics() const
{
  std::cout << "\n=== ESTADÍSTICAS DE TAREAS - " << getFullName() << " ===" << std::endl;

  if (myStudents.empty())
  {
    std::cout << "No hay alumnos a cargo para mostrar estadísticas." << std::endl;
    return;
  }

  int totalTareas = 0;
  int totalEntregadas = 0;

  for (const Alumno *alumno : myStudents)
  {
    totalTareas += alumno->getTotalAssignments();
    totalEntregadas += alumno->countSubmittedAssignments();
  }

  std::cout << "Total de tareas asignadas: " << totalTareas << std::endl;
  std::cout << "Total de tareas entregadas: " << totalEntregadas << std::endl;
  std::cout << "Total de tareas pendientes: " << (totalTareas - totalEntregadas) << std::endl;

  if (totalTareas > 0)
  {
    double porcentaje = (static_cast<double>(totalEntregadas) / totalTareas) * 100.0;
    std::cout << "Porcentaje general de entregas: " << porcentaje << "%" << std::endl;
  }

  std::cout << "==================================================\n"
            << std::endl;
}

bool Profesor::teachesInMultipleGrades() const
{
  std::set<int> uniqueGrades;
  for (const Alumno *student : myStudents)
  {
    uniqueGrades.insert(student->getGrade());
  }
  return uniqueGrades.size() > 1;
}

std::vector<int> Profesor::getGradesTaught() const
{
  std::set<int> uniqueGrades;
  for (const Alumno *student : myStudents)
  {
    uniqueGrades.insert(student->getGrade());
  }

  return std::vector<int>(uniqueGrades.begin(), uniqueGrades.end());
}

void Profesor::clearStudentList()
{
  myStudents.clear();
}