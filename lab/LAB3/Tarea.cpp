#include "Tarea.h"
#include <iostream>

Tarea::Tarea(const std::string &course, const std::string &teacher,
             const std::string &date, const std::string &studentCode,
             bool delivered)
    : course(course), teacher(teacher), date(date),
      delivered(delivered), studentCode(studentCode)
{
}

Tarea::~Tarea()
{
}

std::string Tarea::getCourse() const
{
  return course;
}

std::string Tarea::getTeacher() const
{
  return teacher;
}

std::string Tarea::getDate() const
{
  return date;
}

bool Tarea::isDelivered() const
{
  return delivered;
}

std::string Tarea::getStudentCode() const
{
  return studentCode;
}

void Tarea::setCourse(const std::string &course)
{
  this->course = course;
}

void Tarea::setTeacher(const std::string &teacher)
{
  this->teacher = teacher;
}

void Tarea::setDate(const std::string &date)
{
  this->date = date;
}

void Tarea::setDelivered(bool delivered)
{
  this->delivered = delivered;
}

void Tarea::setStudentCode(const std::string &studentCode)
{
  this->studentCode = studentCode;
}

void Tarea::submitTask()
{
  delivered = true;
}

void Tarea::showData() const
{
  std::cout << "=== INFORMACIÓN DE TAREA ===" << std::endl;
  std::cout << "Curso: " << course << std::endl;
  std::cout << "Profesor: " << teacher << std::endl;
  std::cout << "Fecha: " << date << std::endl;
  std::cout << "Código Alumno: " << studentCode << std::endl;
  std::cout << "Estado: " << getDeliveryStatus() << std::endl;
  std::cout << "=========================" << std::endl;
}

std::string Tarea::getDeliveryStatus() const
{
  return delivered ? "Entregada" : "Pendiente";
}