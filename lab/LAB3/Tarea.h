#ifndef TAREA_H
#define TAREA_H

#include <string>

class Tarea
{
private:
  std::string course;
  std::string teacher;
  std::string date;
  bool delivered;
  std::string studentCode;

public:
  Tarea(const std::string &course, const std::string &teacher,
        const std::string &date, const std::string &studentCode,
        bool delivered = false);

  // Destructor
  ~Tarea();

  // Métodos getter
  std::string getCourse() const;
  std::string getTeacher() const;
  std::string getDate() const;
  bool isDelivered() const;
  std::string getStudentCode() const;

  // Métodos setter
  void setCourse(const std::string &course);
  void setTeacher(const std::string &teacher);
  void setDate(const std::string &date);
  void setDelivered(bool delivered);
  void setStudentCode(const std::string &studentCode);

  void submitTask();

  void showData() const;

  std::string getDeliveryStatus() const;
};

#endif