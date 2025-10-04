#ifndef SISTEMA_H
#define SISTEMA_H

#include "Alumno.h"
#include "Profesor.h"
#include "Tarea.h"
#include <vector>
#include <string>
#include <fstream>

class Sistema
{
private:
  std::vector<Alumno *> students;
  std::vector<Profesor *> teachers;
  std::vector<Tarea *> tasks;

public:
  Sistema();
  ~Sistema();

  bool registerStudent(const std::string &firstName, const std::string &lastName,
                       const std::string &code, int grade);

  bool registerTeacher(const std::string &firstName, const std::string &lastName,
                       const std::string &teacherId);

  bool registerTask(const std::string &course, const std::string &teacherName,
                    const std::string &date, const std::string &studentCode);

  // Alumno search
  Alumno *findStudent(const std::string &code) const;
  std::vector<Alumno *> findStudentsByName(const std::string &name) const;
  std::vector<Alumno *> findStudentsByGrade(int grade) const;

  // Profesor search
  Profesor *findTeacher(const std::string &teacherId) const;
  Profesor *findTeacherByName(const std::string &name) const;
  std::vector<Profesor *> findTeachersByCourse(const std::string &course) const;

  // Task search
  std::vector<Tarea *> findTasksByStudent(const std::string &studentCode) const;
  std::vector<Tarea *> findTasksByTeacher(const std::string &teacherName) const;
  std::vector<Tarea *> findTasksByCourse(const std::string &course) const;

  // Check uniqueness of IDs
  bool studentExists(const std::string &code) const;
  bool teacherExists(const std::string &teacherId) const;

  // Data validation
  bool validateGrade(int grade) const;
  bool validateStudentCode(const std::string &code) const;

  // CRUD TASKS
  bool markTaskAsSubmitted(const std::string &studentCode,
                           const std::string &course, const std::string &teacherName);

  void assignStudentToTeacher(const std::string &studentCode,
                              const std::string &teacherId);

  void addCourseToTeacher(const std::string &teacherId, const std::string &course);

  // Alumno information queries
  void viewStudentTasks(const std::string &studentCode) const;
  void viewTeacherStudents(const std::string &teacherId) const;

  // Reports
  void generateFullReport() const;
  void generateStudentReport() const;
  void generateTeacherReport() const;
  void generateTaskReport() const;

  // Specific statistics
  void showSubmissionStatistics() const;
  void showMultiGradeTeachers() const;

  // Listings
  void listAllStudents() const;
  void listAllTeachers() const;
  void listAllTasks() const;

  // Memory management
  void freeAllMemory();
  void clearStudents();
  void clearTeachers();
  void clearTasks();

  // File persistence
  void saveDataToFile(const std::string &fileName) const;
  void loadDataFromFile(const std::string &fileName);

  // Getters
  const std::vector<Alumno *> &getStudents() const;
  const std::vector<Profesor *> &getTeachers() const;
  const std::vector<Tarea *> &getTasks() const;

  // Count getters
  int getStudentCount() const;
  int getTeacherCount() const;
  int getTaskCount() const;

  // Other utilities
  void showMainMenu() const;
  void showSystemStatus() const;

private:
  // Helpers
  void initializeSystem();
  bool validateStudentData(const std::string &code, int grade) const;
  std::string generateUniqueCode() const;
};

#endif