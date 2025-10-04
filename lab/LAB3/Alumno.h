#ifndef ALUMNO_H
#define ALUMNO_H

#include "Persona.h"
#include "Tarea.h"
#include <vector>
#include <string>

class Alumno : public Persona
{
private:
  std::string code;
  int grade;
  std::vector<Tarea *> assignments;

public:
  Alumno(const std::string &name, const std::string &lastName,
         const std::string &code, int grade);

  virtual ~Alumno();

  // Get y set
  std::string getCode() const;
  int getGrade() const;
  const std::vector<Tarea *> &getAssignments() const;

  void setCode(const std::string &code);
  void setGrade(int grade);

  // validar el grado
  static bool isGradeValid(int grade);

  // CRUD assignment
  void addAssignment(Tarea *assignment);
  void removeAssignment(const std::string &course, const std::string &teacher);

  int countSubmittedAssignments() const;
  int countPendingAssignments() const;
  int getTotalAssignments() const;
  double getSubmissionPercentage() const;

  // Show data
  void showData() const override;
  void showSubmittedAssignments() const;
  void showPendingAssignments() const;
  void showAllAssignments() const;

  // Search assignment
  Tarea *searchAssignment(const std::string &course, const std::string &teacher) const;
  std::vector<Tarea *> searchAssignmentsByCourse(const std::string &course) const;
  std::vector<Tarea *> searchAssignmentsByTeacher(const std::string &teacher) const;

  // Clear memory
  void clearMemory();
};

#endif