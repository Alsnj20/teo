# Sistema de Gestión Escolar

## 📋 Descripción del Proyecto

Este proyecto implementa un sistema completo de administración de estudiantes de una escuela virtual, desarrollado en C++ como parte del Laboratorio 3. El sistema demuestra el uso avanzado de:

- **Clases y herencia en C++**
- **Manejo de punteros dinámicos**
- **Administración de memoria (new/delete)**
- **Relaciones entre clases usando punteros**
- **Gestión de múltiples entidades**

## 🎯 Objetivos Cumplidos

### ✅ Requisitos Básicos
- [x] Implementación con clases y punteros en C++
- [x] Manejo de múltiples clases interrelacionadas
- [x] Comentarios detallados justificando las funciones
- [x] Registro de alumnos, profesores y trabajos
- [x] Búsqueda de información por diferentes criterios
- [x] Consulta de trabajos por alumno y alumnos por profesor

### ✅ Actividades Adicionales Implementadas

#### 5.1 Relación entre clases ✅
- Relación Profesor-Alumno implementada usando punteros dinámicos
- Verificación de profesores enseñando en diferentes grados
- Lista dinámica de alumnos a cargo de cada profesor

#### 5.2 Gestión dinámica de memoria ✅
- Creación y destrucción dinámica usando `new` y `delete`
- Método de liberación de memoria antes de finalizar el programa
- Gestión automática de memoria en destructores

#### 5.3 Registro de tareas entregadas ✅
- Método para mostrar todas las tareas de un alumno
- Uso de valor booleano (true/false) como indicador de entrega
- Separación entre tareas entregadas y pendientes

#### 5.4 Reportes estadísticos ✅
- Número de tareas entregadas por cada alumno
- Porcentaje de entregas respecto al total
- Cantidad total de alumnos bajo responsabilidad de cada profesor
- Estadísticas generales del sistema

#### 5.5 Búsqueda de información ✅
- Búsqueda por código del alumno
- Búsqueda por nombre del profesor
- Búsqueda por curso específico
- Búsquedas con criterios múltiples

#### 5.6 Uso de herencia ✅
- Clase base `Persona` con atributos comunes (nombres, apellidos)
- Clases derivadas `Alumno` y `Profesor`
- Demostración de cómo la herencia simplifica el diseño

#### 5.7 Persistencia en archivos ✅
- Guardado de información en archivos de texto
- Estructura preparada para carga automática de registros

#### 5.9 Interfaz de usuario simple ✅
- Menú completo de opciones en consola:
  1. Registrar alumno
  2. Registrar profesor
  3. Registrar tarea
  4. Consultar tareas de un alumno
  5. Consultar alumnos de un profesor
  6. Generar reportes
  7. Búsquedas avanzadas
  8. Marcar tareas como entregadas
  9. Estadísticas del sistema
  10. Guardar datos en archivo

#### 5.10 Validación de datos ✅
- Verificación de códigos únicos de alumno
- Validación de grados válidos (1-6)
- Verificación de existencia de profesores antes de asignar tareas
- Validación de datos de entrada en todas las operaciones

## 🏗️ Arquitectura del Sistema

### Jerarquía de Clases

```
Persona (Clase Base)
├── Alumno (Hereda de Persona)
└── Profesor (Hereda de Persona)

Tarea (Clase independiente)
Sistema (Clase controladora)
```

### Diagrama de Relaciones

```
Sistema
├── Vector<Alumno*> alumnos
├── Vector<Profesor*> profesores  
└── Vector<Tarea*> tareas

Profesor
└── Vector<Alumno*> alumnosACargo

Alumno
└── Vector<Tarea*> tareas
```

## 📁 Estructura de Archivos

```
LAB3/
├── Persona.h           # Clase base con atributos comunes
├── Persona.cpp
├── Alumno.h           # Clase alumno (hereda de Persona)
├── Alumno.cpp
├── Profesor.h         # Clase profesor (hereda de Persona)
├── Profesor.cpp
├── Tarea.h           # Clase tarea con información de trabajos
├── Tarea.cpp
├── Sistema.h         # Clase principal del sistema
├── Sistema.cpp
├── main.cpp          # Programa principal con menú interactivo
├── Makefile          # Script de compilación
└── README.md         # Este archivo
```

## 🔧 Características Técnicas

### Gestión de Memoria
- **Creación dinámica**: Uso de `new` para crear objetos en heap
- **Liberación automática**: Destructores liberan memoria con `delete`
- **Prevención de memory leaks**: Sistema robusto de limpieza
- **RAII**: Resource Acquisition Is Initialization implementado

### Relaciones con Punteros
- **Profesor → Alumno**: Un profesor puede tener múltiples alumnos
- **Alumno → Tarea**: Un alumno puede tener múltiples tareas
- **Sistema**: Administra todas las entidades centralizadamente

### Validaciones
- Códigos únicos de alumno
- Grados válidos (1° a 6° de primaria)
- Existencia de profesores antes de asignar tareas
- Integridad referencial entre entidades

## 🚀 Compilación y Ejecución

### Usando Makefile (Recomendado)
```bash
# Compilar el proyecto
make

# Compilar y ejecutar directamente
make run

# Ver información del proyecto
make info

# Limpiar archivos compilados
make clean
```

### Compilación Manual
```bash
g++ -std=c++11 -Wall -Wextra -pedantic -g main.cpp Persona.cpp Alumno.cpp Profesor.cpp Tarea.cpp Sistema.cpp -o sistema_escolar
```

### Ejecutar
```bash
./sistema_escolar
```

## 🖥️ Uso del Sistema

### Datos de Ejemplo
El sistema incluye datos de ejemplo que se cargan automáticamente:
- 3 profesores registrados
- 4 alumnos en diferentes grados
- Múltiples cursos y tareas asignadas
- Algunas tareas marcadas como entregadas

### Funcionalidades Principales

1. **Registro de Entidades**
   - Alumnos con validación de código único y grado
   - Profesores con ID único y cursos
   - Tareas con relación alumno-profesor

2. **Consultas y Búsquedas**
   - Por código, nombre, grado, curso
   - Listados completos por entidad
   - Búsquedas parciales por nombre

3. **Reportes Estadísticos**
   - Rendimiento por alumno
   - Carga de trabajo por profesor
   - Estadísticas de entregas
   - Profesores multigigrado

4. **Gestión de Tareas**
   - Asignación de tareas
   - Marcado como entregadas
   - Seguimiento de pendientes

## 💾 Persistencia de Datos

El sistema permite guardar todos los datos en archivos de texto con formato estructurado:
- **Alumnos**: Código, nombres, apellidos, grado
- **Profesores**: ID, nombres, apellidos, cursos
- **Tareas**: Curso, profesor, fecha, alumno, estado

## 🎓 Conceptos Demostrados

### Programación Orientada a Objetos
- Encapsulamiento: Atributos privados con métodos públicos
- Herencia: Reutilización de código con clase base Persona
- Polimorfismo: Métodos virtuales y sobrescritura

### Gestión de Memoria en C++
- Asignación dinámica con `new`
- Liberación con `delete`
- Destructores automáticos
- Prevención de memory leaks

### Estructuras de Datos
- Vectores dinámicos (std::vector)
- Punteros a objetos
- Relaciones uno-a-muchos
- Búsquedas y filtros

### Diseño de Software
- Separación de responsabilidades
- Interfaz de usuario separada de lógica de negocio
- Validación de datos
- Manejo de errores

## ⚠️ Consideraciones Técnicas

### Limitaciones Actuales
- Persistencia en archivos es básica (solo escritura completa)
- No hay encriptación de datos
- Interfaz solo por consola
- Búsquedas son lineales (O(n))

### Posibles Mejoras
- Implementar punteros inteligentes (std::unique_ptr)
- Agregar base de datos real
- Interfaz gráfica
- Índices para búsquedas más rápidas
- Red/cliente-servidor

## 👥 Información del Proyecto

**Laboratorio**: LAB3 - Sistema de Gestión Escolar  
**Lenguaje**: C++11 o superior  
**Compilador**: g++ (GCC)  
**Plataforma**: Multiplataforma (Linux/Windows/macOS)

## 📝 Conclusiones

Este proyecto demuestra exitosamente:

1. **Uso avanzado de clases y herencia** en C++ con una jerarquía bien estructurada
2. **Gestión robusta de memoria** con punteros dinámicos y liberación automática
3. **Relaciones complejas entre entidades** usando punteros para modelar relaciones del mundo real
4. **Sistema completo y funcional** con interfaz de usuario, validaciones y reportes
5. **Buenas prácticas de programación** con código documentado y estructurado

El sistema es escalable y puede expandirse fácilmente con nuevas funcionalidades, demostrando un diseño sólido y principios de ingeniería de software.

---
*Desarrollado como parte del curso de Programación en C++ - Laboratorio de Tecnologías Orientadas*