#include "Sistema.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

Sistema::Sistema()
{
  initializeSystem();
  std::cout << "Sistema de gestión escolar inicializado correctamente." << std::endl;
}

Sistema::~Sistema()
{
  freeAllMemory();
  std::cout << "Sistema de gestión escolar cerrado. Memoria liberada." << std::endl;
}

void Sistema::initializeSystem() {}

bool Sistema::registerStudent(const std::string &nombres, const std::string &apellidos,
                              const std::string &codigo, int grado)
{
  if (!validateStudentData(codigo, grado))
  {
    return false;
  }

  Alumno *nuevoAlumno = new Alumno(nombres, apellidos, codigo, grado);

  students.push_back(nuevoAlumno);

  std::cout << "Alumno registrado exitosamente: " << nuevoAlumno->getFullName()
            << " (Código: " << codigo << ")" << std::endl;

  return true;
}

bool Sistema::registerTeacher(const std::string &nombres, const std::string &apellidos,
                              const std::string &idProfesor)
{
  // Verificar que el ID no esté duplicado
  if (teacherExists(idProfesor))
  {
    std::cout << "Error: Ya existe un profesor con ID " << idProfesor << std::endl;
    return false;
  }

  // Crear nuevo profesor usando new (gestión dinámica de memoria)
  Profesor *nuevoProfesor = new Profesor(nombres, apellidos, idProfesor);

  // Agregar al vector de profesores
  teachers.push_back(nuevoProfesor);

  std::cout << "Profesor registrado exitosamente: " << nuevoProfesor->getFullName()
            << " (ID: " << idProfesor << ")" << std::endl;

  return true;
}

bool Sistema::registerTask(const std::string &course, const std::string &teacherName,
                           const std::string &date, const std::string &studentCode)
{
  // Verificar que el alumno exista
  Alumno *alumno = findStudent(studentCode);
  if (alumno == nullptr)
  {
    std::cout << "Error: No existe alumno con código " << studentCode << std::endl;
    return false;
  }

  // Verificar que el profesor exista
  Profesor *profesor = findTeacher(teacherName);
  if (profesor == nullptr)
  {
    std::cout << "Error: No existe profesor con nombre " << teacherName << std::endl;
    return false;
  }

  // Crear nueva tarea usando new (gestión dinámica de memoria)
  Tarea *nuevaTarea = new Tarea(course, teacherName, date, studentCode);

  // Agregar al vector global de tareas
  tasks.push_back(nuevaTarea);

  // Agregar la tarea al alumno
  alumno->addAssignment(nuevaTarea);

  // Asegurar que el profesor imparte este curso
  if (!profesor->teachesCourse(course))
  {
    profesor->addCourse(course);
  }

  // Asegurar relación profesor-alumno
  if (!profesor->hasStudent(alumno->getCode()))
  {
    profesor->addStudent(alumno);
  }

  std::cout << "Tarea registrada exitosamente: " << course
            << " para " << alumno->getFullName() << std::endl;

  return true;
}

// 🔹 Guardar datos en archivo
void Sistema::saveDataToFile(const std::string &filename) const
{
  std::ofstream file(filename);
  if (!file)
  {
    std::cerr << "Error al abrir archivo para guardar." << std::endl;
    return;
  }

  // Guardar alumnos
  file << "[ALUMNOS]\n";
  for (auto a : students)
  {
    file << a->getName() << "," << a->getLastName() << "," << a->getCode() << "," << a->getGrade() << "\n";
  }

  // Guardar profesores
  file << "[PROFESORES]\n";
  for (auto p : teachers)
  {
    file << p->getName() << "," << p->getLastName() << "," << p->getIdTeacher() << "\n";
  }

  // Guardar tareas
  file << "[TAREAS]\n";
  for (auto t : tasks)
  {
    file << t->getCourse() << "," << t->getTeacher() << ","
         << t->getDate() << "," << t->getStudentCode() << ","
         << (t->isDelivered() ? "1" : "0") << "\n";
  }

  file.close();
}

// 🔹 Cargar datos desde archivo
void Sistema::loadDataFromFile(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << "No se encontró archivo de datos, iniciando vacío." << std::endl;
    return;
  }

  freeAllMemory(); // limpiar datos previos

  std::string line;
  enum Seccion
  {
    NONE,
    ALUMNOS,
    PROFESORES,
    TAREAS
  } seccion = NONE;

  while (std::getline(file, line))
  {
    if (line == "[ALUMNOS]")
    {
      seccion = ALUMNOS;
      continue;
    }
    if (line == "[PROFESORES]")
    {
      seccion = PROFESORES;
      continue;
    }
    if (line == "[TAREAS]")
    {
      seccion = TAREAS;
      continue;
    }

    if (line.empty())
      continue;

    std::stringstream ss(line);
    std::string a, b, c, d, e;

    switch (seccion)
    {
    case ALUMNOS:
      std::getline(ss, a, ',');
      std::getline(ss, b, ',');
      std::getline(ss, c, ',');
      std::getline(ss, d, ',');
      students.push_back(new Alumno(a, b, c, std::stoi(d)));
      break;
    case PROFESORES:
      std::getline(ss, a, ',');
      std::getline(ss, b, ',');
      std::getline(ss, c, ',');
      teachers.push_back(new Profesor(a, b, c));
      break;
    case TAREAS:
      std::getline(ss, a, ',');
      std::getline(ss, b, ',');
      std::getline(ss, c, ',');
      std::getline(ss, d, ',');
      std::getline(ss, e, ',');
      tasks.push_back(new Tarea(a, b, c, d, (e == "1")));
      break;
    default:
      break;
    }
  }
}

// Searches
Alumno *Sistema::findStudent(const std::string &code) const
{
  for (Alumno *alumno : students)
  {
    if (alumno->getCode() == code)
    {
      return alumno;
    }
  }
  return nullptr;
}

std::vector<Alumno *> Sistema::findStudentsByName(const std::string &name) const
{
  std::vector<Alumno *> resultado;
  for (Alumno *alumno : students)
  {
    if (alumno->getFullName().find(name) != std::string::npos)
    {
      resultado.push_back(alumno);
    }
  }
  return resultado;
}

std::vector<Alumno *> Sistema::findStudentsByGrade(int grade) const
{
  std::vector<Alumno *> resultado;
  for (Alumno *alumno : students)
  {
    if (alumno->getGrade() == grade)
    {
      resultado.push_back(alumno);
    }
  }
  return resultado;
}

Profesor *Sistema::findTeacher(const std::string &idTeacher) const
{
  for (Profesor *profesor : teachers)
  {
    if (profesor->getIdTeacher() == idTeacher)
    {
      return profesor;
    }
  }
  return nullptr;
}

Profesor *Sistema::findTeacherByName(const std::string &name) const
{
  for (Profesor *profesor : teachers)
  {
    if (profesor->getFullName().find(name) != std::string::npos)
    {
      return profesor;
    }
  }
  return nullptr;
}

std::vector<Profesor *> Sistema::findTeachersByCourse(const std::string &course) const
{
  std::vector<Profesor *> result;
  for (Profesor *profesor : teachers)
  {
    if (profesor->teachesCourse(course))
    {
      result.push_back(profesor);
    }
  }
  return result;
}

std::vector<Tarea *> Sistema::findTasksByStudent(const std::string &studentCode) const
{
  std::vector<Tarea *> result;
  for (Tarea *tarea : tasks)
  {
    if (tarea->getStudentCode() == studentCode)
    {
      result.push_back(tarea);
    }
  }
  return result;
}

std::vector<Tarea *> Sistema::findTasksByTeacher(const std::string &teacherName) const
{
  std::vector<Tarea *> result;
  for (Tarea *task : tasks)
  {
    if (task->getTeacher() == teacherName)
    {
      result.push_back(task);
    }
  }
  return result;
}

std::vector<Tarea *> Sistema::findTasksByCourse(const std::string &course) const
{
  std::vector<Tarea *> result;
  for (Tarea *task : tasks)
  {
    if (task->getCourse() == course)
    {
      result.push_back(task);
    }
  }
  return result;
}

bool Sistema::studentExists(const std::string &code) const
{
  return findStudent(code) != nullptr;
}

bool Sistema::teacherExists(const std::string &teacherId) const
{
  return findTeacher(teacherId) != nullptr;
}

bool Sistema::validateGrade(int grade) const
{
  return Alumno::isGradeValid(grade);
}

bool Sistema::validateStudentCode(const std::string &code) const
{
  return !code.empty() && !studentExists(code);
}

bool Sistema::validateStudentData(const std::string &code, int grade) const
{
  if (!validateStudentCode(code))
  {
    std::cout << "Error: Código de alumno inválido o duplicado: " << code << std::endl;
    return false;
  }

  if (!validateGrade(grade))
  {
    std::cout << "Error: Grado inválido: " << grade << ". Debe estar entre 1 y 6." << std::endl;
    return false;
  }

  return true;
}

bool Sistema::markTaskAsSubmitted(const std::string &studentCode,
                                  const std::string &course, const std::string &teacher)
{
  Alumno *student = findStudent(studentCode);
  if (student == nullptr)
  {
    std::cout << "Error: No se encontró alumno con código " << studentCode << std::endl;
    return false;
  }

  Tarea *task = student->searchAssignment(course, teacher);
  if (task == nullptr)
  {
    std::cout << "Error: No se encontró la tarea especificada." << std::endl;
    return false;
  }

  task->submitTask();
  std::cout << "Tarea marcada como entregada exitosamente." << std::endl;
  return true;
}

void Sistema::assignStudentToTeacher(const std::string &studentCode,
                                     const std::string &teacherId)
{
  Alumno *student = findStudent(studentCode);
  Profesor *teacher = findTeacher(teacherId);

  if (student != nullptr && teacher != nullptr)
  {
    teacher->addStudent(student);
  }
  else
  {
    std::cout << "Error: No se pudo realizar la asignación. Verificar datos." << std::endl;
  }
}

void Sistema::addCourseToTeacher(const std::string &teacherId, const std::string &course)
{
  Profesor *teacher = findTeacher(teacherId);
  if (teacher != nullptr)
  {
    teacher->addCourse(course);
  }
  else
  {
    std::cout << "Error: No se encontró profesor con ID " << teacherId << std::endl;
  }
}

void Sistema::viewStudentTasks(const std::string &studentCode) const
{
  Alumno *student = findStudent(studentCode);
  if (student == nullptr)
  {
    std::cout << "No se encontró alumno con código: " << studentCode << std::endl;
    return;
  }

  student->showData();
  student->showAllAssignments();
}

void Sistema::viewTeacherStudents(const std::string &teacherId) const
{
  Profesor *teacher = findTeacher(teacherId);
  if (teacher == nullptr)
  {
    std::cout << "No se encontró profesor con ID: " << teacherId << std::endl;
    return;
  }

  teacher->showData();
  teacher->showMyStudents();
  teacher->showStudentsByGrade();
}

void Sistema::generateFullReport() const
{
  std::cout << "\n================= REPORTE COMPLETO DEL SISTEMA =================" << std::endl;

  std::cout << "ESTADÍSTICAS GENERALES:" << std::endl;
  std::cout << "- Total de alumnos registrados: " << getStudentCount() << std::endl;
  std::cout << "- Total de profesores registrados: " << getTeacherCount() << std::endl;
  std::cout << "- Total de tareas asignadas: " << getTaskCount() << std::endl;

  int totalDelivered = 0;
  for (const Tarea *task : tasks)
  {
    if (task->isDelivered())
    {
      totalDelivered++;
    }
  }

  std::cout << "- Tareas entregadas: " << totalDelivered << std::endl;
  std::cout << "- Tareas pendientes: " << (getTaskCount() - totalDelivered) << std::endl;

  if (getTaskCount() > 0)
  {
    double percentage = (static_cast<double>(totalDelivered) / getTaskCount()) * 100.0;
    std::cout << "- Porcentaje general de entregas: " << std::fixed << std::setprecision(2) << percentage << "%" << std::endl;
  }

  std::cout << "\n";
  generateStudentReport();
  generateTeacherReport();

  std::cout << "================================================================\n"
            << std::endl;
}

void Sistema::generateStudentReport() const
{
  std::cout << "\n=== REPORTE DE ALUMNOS ===" << std::endl;

  if (students.empty())
  {
    std::cout << "No hay alumnos registrados." << std::endl;
    return;
  }

  for (int grade = 1; grade <= 6; ++grade)
  {
    std::vector<Alumno *> studentsByGrade = findStudentsByGrade(grade);
    if (!studentsByGrade.empty())
    {
      std::cout << "\n"
                << grade << "° GRADO (" << studentsByGrade.size() << " alumnos):" << std::endl;
      for (const Alumno *student : studentsByGrade)
      {
        std::cout << "  • " << student->getFullName()
                  << " (Código: " << student->getCode() << ")"
                  << " - Tareas: " << student->countSubmittedAssignments()
                  << "/" << student->getTotalAssignments() << " entregadas"
                  << " (" << std::fixed << std::setprecision(1)
                  << student->getSubmissionPercentage() << "%)" << std::endl;
      }
    }
  }
  std::cout << "=========================" << std::endl;
}

void Sistema::generateTeacherReport() const
{
  std::cout << "\n=== REPORTE DE PROFESORES ===" << std::endl;

  if (teachers.empty())
  {
    std::cout << "No hay profesores registrados." << std::endl;
    return;
  }

  for (const Profesor *teacher : teachers)
  {
    std::cout << "\nProfesor: " << teacher->getFullName()
              << " (ID: " << teacher->getIdTeacher() << ")" << std::endl;
    std::cout << "  - Alumnos a cargo: " << teacher->getStudentCount() << std::endl;
    std::cout << "  - Cursos impartidos: " << teacher->getCoursesTaught().size() << std::endl;
    std::cout << "  - Enseña en múltiples grados: " << (teacher->teachesInMultipleGrades() ? "Sí" : "No") << std::endl;

    if (teacher->teachesInMultipleGrades())
    {
      std::cout << "  - Grados: ";
      std::vector<int> grades = teacher->getGradesTaught();
      for (size_t i = 0; i < grades.size(); ++i)
      {
        std::cout << grades[i] << "°";
        if (i < grades.size() - 1)
          std::cout << ", ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << "==============================" << std::endl;
}
void Sistema::showMainMenu() const
{
  std::cout << "\n=== MENU PRINCIPAL ===\n";
  std::cout << "1. Registrar alumno\n";
  std::cout << "2. Registrar profesor\n";
  std::cout << "3. Registrar tarea\n";
  std::cout << "...\n";
  std::cout << "0. Salir\n";
  std::cout << "Seleccione una opcion: ";
}

void Sistema::showSystemStatus() const
{
  std::cout << "\nEstado actual del sistema:\n";
  std::cout << "Alumnos: " << getStudentCount() << "\n";
  std::cout << "Profesores: " << getTeacherCount() << "\n";
  std::cout << "Tareas: " << getTaskCount() << "\n";
}

void Sistema::freeAllMemory()
{
}

int Sistema::getStudentCount() const { return students.size(); }
int Sistema::getTeacherCount() const { return teachers.size(); }
int Sistema::getTaskCount() const { return tasks.size(); }
