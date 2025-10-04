#include <iostream>
#include <string>
#include <limits>
#include "Sistema.h"

using namespace std;

// Prototipos de funciones
void showMenu();
void pause();
void clearBuffer();

void handleStudentRegistration(Sistema &sistema);
void handleTeacherRegistration(Sistema &sistema);
void handleTaskRegistration(Sistema &sistema);
void handleStudentTasksQuery(Sistema &sistema);
void handleTeacherStudentsQuery(Sistema &sistema);
void handleReports(Sistema &sistema);
void handleSearches(Sistema &sistema);
bool confirmExit();

int main()
{
  Sistema sistema;
  std::cout << "\nBienvenido al Sistema de Gestion Escolar!" << std::endl;

  std::cout << "\nCargando datos..." << std::endl;
  sistema.loadDataFromFile("datos.txt");

  std::cout << "Datos cargados correctamente.\n"
            << std::endl;

  bool running = true;

  while (running)
  {
    showMenu();
    int option;
    cout << "Seleccione una opcion: ";
    if (!(cin >> option))
    {
      cout << "Entrada invalida. Intente nuevamente." << endl;
      cin.clear();
      clearBuffer();
      pause();
      continue;
    }
    clearBuffer();

    switch (option)
    {
    case 1:
      handleStudentRegistration(sistema);
      break;
    case 2:
      handleTeacherRegistration(sistema);
      break;
    case 3:
      handleTaskRegistration(sistema);
      break;
    case 4:
      handleStudentTasksQuery(sistema);
      break;
    case 5:
      handleTeacherStudentsQuery(sistema);
      break;
    case 6:
      handleReports(sistema);
      break;
    case 7:
      handleSearches(sistema);
      break;
    case 8:
      sistema.showSystemStatus();
      pause();
      break;
    case 0:
      if (confirmExit())
        running = false;
      break;
    default:
      cout << "Opcion no valida. Intente nuevamente." << endl;
      pause();
      break;
    }
  }

  return 0;
}

void showMenu()
{
  cout << "\n=== SISTEMA DE GESTION ESCOLAR ===" << endl;
  cout << "1. Registrar alumno" << endl;
  cout << "2. Registrar profesor" << endl;
  cout << "3. Registrar tarea" << endl;
  cout << "4. Consultar tareas de un alumno" << endl;
  cout << "5. Consultar alumnos de un profesor" << endl;
  cout << "6. Reportes" << endl;
  cout << "7. Busquedas" << endl;
  cout << "8. Marcar tarea como entregada" << endl;
  cout << "10. Guardar datos" << endl;
  cout << "0. Salir" << endl;
}

void pause()
{
  cout << "\nPresione ENTER para continuar...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.clear();
}

void clearBuffer()
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool confirmExit()
{
  char choice;
  cout << "¿Seguro que desea salir? (s/n): ";
  cin >> choice;
  clearBuffer();
  return (choice == 's' || choice == 'S');
}

// ==================== IMPLEMENTACIONES ====================

void handleStudentRegistration(Sistema &sistema)
{
  cout << "\n=== REGISTRAR NUEVO ALUMNO ===" << endl;
  string nombres, apellidos, codigo;
  int grado;

  cout << "Ingrese nombres: ";
  getline(cin, nombres);
  cout << "Ingrese apellidos: ";
  getline(cin, apellidos);
  cout << "Ingrese codigo del alumno: ";
  getline(cin, codigo);
  cout << "Ingrese grado (1-6): ";
  if (!(cin >> grado))
  {
    cout << "Error: Grado invalido." << endl;
    cin.clear();
    clearBuffer();
    pause();
    return;
  }
  clearBuffer();

  if (sistema.registerStudent(nombres, apellidos, codigo, grado))
  {
    cout << "Alumno registrado exitosamente!" << endl;
  }
  else
  {
    cout << "Error al registrar el alumno." << endl;
  }

  pause();
}

void handleTeacherRegistration(Sistema &sistema)
{
  cout << "\n=== REGISTRAR NUEVO PROFESOR ===" << endl;
  string nombres, apellidos, curso;

  cout << "Ingrese nombres: ";
  getline(cin, nombres);
  cout << "Ingrese apellidos: ";
  getline(cin, apellidos);
  cout << "Ingrese curso que dicta: ";
  getline(cin, curso);

  if (sistema.registerTeacher(nombres, apellidos, curso))
  {
    cout << "Profesor registrado exitosamente!" << endl;
  }
  else
  {
    cout << "Error al registrar el profesor." << endl;
  }

  pause();
}

void handleTaskRegistration(Sistema &sistema)
{
  cout << "\n=== REGISTRAR NUEVA TAREA ===" << endl;
  string curso, profesor, codigoAlumno, descripcion;

  cout << "Ingrese curso: ";
  getline(cin, curso);
  cout << "Ingrese nombre del profesor: ";
  getline(cin, profesor);
  cout << "Ingrese codigo del alumno: ";
  getline(cin, codigoAlumno);
  cout << "Ingrese descripcion de la tarea: ";
  getline(cin, descripcion);

  if (sistema.registerTask(curso, profesor, codigoAlumno, descripcion))
  {
    cout << "Tarea registrada exitosamente!" << endl;
  }
  else
  {
    cout << "Error al registrar la tarea." << endl;
  }

  pause();
}

void handleStudentTasksQuery(Sistema &sistema)
{
  cout << "\n=== CONSULTA DE TAREAS POR ALUMNO ===" << endl;
  string codigo;
  cout << "Ingrese codigo del alumno: ";
  getline(cin, codigo);

  sistema.findTasksByStudent(codigo);
  pause();
}

void handleTeacherStudentsQuery(Sistema &sistema)
{
  cout << "\n=== CONSULTA DE ALUMNOS POR PROFESOR ===" << endl;
  string nombreProfesor;
  cout << "Ingrese nombre del profesor: ";
  getline(cin, nombreProfesor);

  Profesor *profesor = sistema.findTeacher(nombreProfesor);

  profesor->showMyStudents();
  pause();
}

void handleReports(Sistema &sistema)
{
  cout << "\n=== REPORTES ===" << endl;
  sistema.generateFullReport();
  pause();
}

void handleSearches(Sistema &sistema)
{
  cout << "\n=== BÚSQUEDAS ===" << endl;
  int choice;
  cout << "1. Buscar alumno por código" << endl;
  cout << "2. Buscar profesor por nombre" << endl;
  cout << "3. Buscar profesores por curso" << endl;
  cout << "Seleccione una opción: ";
  if (!(cin >> choice))
  {
    cout << "Entrada inválida. Intente nuevamente." << endl;
    cin.clear();
    clearBuffer();
    pause();
    return;
  }

  switch (choice)
  {
  case 1:
  {
    string codigo;
    cout << "Ingrese código del alumno: ";
    getline(cin, codigo);
    Alumno *alumno = sistema.findStudent(codigo);
    if (alumno)
      alumno->showData();
    else
      cout << "Alumno no encontrado." << endl;
    break;
  }
  case 2:
  {
    string nombre;
    cout << "Ingrese nombre del profesor: ";
    getline(cin, nombre);
    Profesor *profesor = sistema.findTeacherByName(nombre);
    if (profesor)
      profesor->showData();
    else
      cout << "Profesor no encontrado." << endl;
    break;
  }
  case 3:
  {
    string curso;
    cout << "Ingrese nombre del curso: ";
    getline(cin, curso);
    vector<Profesor *> profesores = sistema.findTeachersByCourse(curso);
    if (!profesores.empty())
    {
      cout << "Profesores que dictan " << curso << ":" << endl;
      for (const auto &profesor : profesores)
      {
        profesor->showData();
      }
    }
    else
    {
      cout << "No se encontraron profesores para el curso especificado." << endl;
    }
    break;
  }
  default:
    cout << "Opción no válida." << endl;
    break;
  }
  pause();
}
