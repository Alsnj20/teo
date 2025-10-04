#ifndef PROFESOR_H
#define PROFESOR_H

#include "Persona.h"
#include "Alumno.h"
#include <vector>
#include <string>

class Profesor : public Persona
{
private:
  std::string idTeacher;
  std::vector<std::string> coursesTaught;
  std::vector<Alumno *> myStudents;

public:
  // Constructor parametrizado
  Profesor(const std::string &name, const std::string &lastName,
           const std::string &idTeacher);

  // Destructor
  virtual ~Profesor();

  // Métodos getter
  std::string getIdTeacher() const;
  const std::vector<std::string> &getCoursesTaught() const;
  const std::vector<Alumno *> &getMyStudents() const;

  // Métodos setter
  void setIdTeacher(const std::string &idTeacher);

  // Gestión de cursos
  void addCourse(const std::string &course);
  void removeCourse(const std::string &course);
  bool teachesCourse(const std::string &course) const;

  // Gestión de alumnos usando punteros
  void addStudent(Alumno *student);
  void removeStudent(const std::string &studentCode);
  bool hasStudent(const std::string &studentCode) const;

  // Consultas sobre alumnos
  int getStudentCount() const;
  int getStudentCountByGrade(int grade) const;
  std::vector<Alumno *> getStudentsByGrade(int grade) const;

  // Búsqueda de alumnos
  Alumno *findStudent(const std::string &studentCode) const;
  std::vector<Alumno *> findStudentsByName(const std::string &name) const;

  // Mostrar información
  void showData() const override;
  void showMyStudents() const;
  void showStudentsByGrade() const;
  void showCoursesTaught() const;

  // Reportes estadísticos
  void showStudentReport() const;
  void showTaskStatistics() const;

  bool teachesInMultipleGrades() const;
  std::vector<int> getGradesTaught() const;

  void clearStudentList();
};

#endif // PROFESOR_H