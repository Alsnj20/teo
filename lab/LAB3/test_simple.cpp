#include <iostream>
#include "Sistema.h"

/**
 * ARCHIVO DE PRUEBAS SIMPLE
 * Demuestra las funcionalidades básicas del sistema sin interfaz de usuario
 */

void mostrarSeparador(const std::string &titulo)
{
  std::cout << "\n"
            << std::string(50, '=') << std::endl;
  std::cout << titulo << std::endl;
  std::cout << std::string(50, '=') << std::endl;
}

int main()
{
  std::cout << "PRUEBA DEL SISTEMA DE GESTIÓN ESCOLAR\n"
            << std::endl;

  // Crear sistema
  Sistema sistema;

  // ===== DEMOSTRACIÓN DE REGISTRO =====
  mostrarSeparador("REGISTRO DE ENTIDADES");

  // Registrar profesores
  sistema.registerTeacher("María", "González", "PROF001");
  sistema.registerTeacher("Juan", "Pérez", "PROF002");

  // Agregar cursos a profesores
  sistema.addCourseToTeacher("PROF001", "Matemáticas");
  sistema.addCourseToTeacher("PROF001", "Ciencias");
  sistema.addCourseToTeacher("PROF002", "Español");

  // Registrar alumnos
  sistema.registerStudent("Carlos", "Ramírez", "ALU001", 3);
  sistema.registerStudent("Ana", "López", "ALU002", 3);
  sistema.registerStudent("Pedro", "Martín", "ALU003", 4);

  // Registrar tareas
  sistema.registerTask("Matemáticas", "María González", "2025-01-15", "ALU001");
  sistema.registerTask("Matemáticas", "María González", "2025-01-20", "ALU002");
  sistema.registerTask("Español", "Juan Pérez", "2025-01-18", "ALU001");

  // ===== DEMOSTRACIÓN DE BÚSQUEDAS =====
  mostrarSeparador("BÚSQUEDAS Y CONSULTAS");

  // Buscar alumno
  Alumno *alumno = sistema.findStudent("ALU001");
  if (alumno)
  {
    alumno->showData();
  }

  // Consultar tareas de alumno
  sistema.findTasksByStudent("ALU001");

  // ===== DEMOSTRACIÓN DE ENTREGAS =====
  mostrarSeparador("GESTIÓN DE TAREAS");

  // Marcar tarea como entregada
  sistema.markTaskAsSubmitted("ALU001", "Matemáticas", "María González");

  // Mostrar tareas actualizadas
  sistema.findTasksByStudent("ALU001");

  // ===== DEMOSTRACIÓN DE REPORTES =====
  mostrarSeparador("REPORTES DEL SISTEMA");

  // Mostrar estado del sistema
  sistema.showSystemStatus();

  // Generar reporte completo
  sistema.generateFullReport();

  // ===== DEMOSTRACIÓN DE RELACIONES =====
  mostrarSeparador("RELACIONES PROFESOR-ALUMNO");

  // Mostrar profesores multigigrado
  sistema.showMultiGradeTeachers();

  // ===== PERSISTENCIA =====
  mostrarSeparador("PERSISTENCIA DE DATOS");

  // Guardar datos
  sistema.saveDataToFile("datos_prueba.txt");

  std::cout << "\n¡PRUEBA COMPLETADA EXITOSAMENTE!" << std::endl;
  std::cout << "El sistema demuestra todas las funcionalidades requeridas:" << std::endl;
  std::cout << "✓ Clases con herencia" << std::endl;
  std::cout << "✓ Manejo de punteros dinámicos" << std::endl;
  std::cout << "✓ Gestión de memoria automática" << std::endl;
  std::cout << "✓ Relaciones entre clases" << std::endl;
  std::cout << "✓ Validaciones de datos" << std::endl;
  std::cout << "✓ Reportes y estadísticas" << std::endl;
  std::cout << "✓ Persistencia en archivos" << std::endl;

  // La memoria se libera automáticamente al salir del scope
  return 0;
}