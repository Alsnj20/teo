# Documentación Técnica - Sistema de Gestión Escolar

## 📚 Explicación Detallada de las Clases

### 🧑 Clase Persona (Clase Base)

La clase `Persona` es la **clase base** del sistema que utiliza el concepto de **herencia** en C++.

#### Características:
- **Tipo**: Clase abstracta (base)
- **Propósito**: Contener atributos comunes para Alumno y Profesor
- **Patrón**: Herencia (permite reutilización de código)

#### Atributos:
```cpp
private:
  string name;        // Nombre de la persona
  string lastName;    // Apellido de la persona
```

#### Funcionalidades Principales:
1. **Encapsulación**: Los atributos son privados, accesibles solo mediante métodos
2. **Métodos Virtuales**: Permite polimorfismo con `virtual ~Persona()` y `virtual void showData() = 0`
3. **Abstracción**: Es una clase abstracta (no se puede instanciar directamente)

#### ¿Por qué es importante?
- **Evita duplicación de código**: Tanto Alumno como Profesor tienen nombres y apellidos
- **Facilita mantenimiento**: Cambios en datos personales se hacen en un solo lugar
- **Permite polimorfismo**: Se pueden tratar alumnos y profesores como Personas

---

### 📝 Clase Tarea

La clase `Tarea` representa las **asignaciones o trabajos** que se asignan a los estudiantes.

#### Características:
- **Tipo**: Clase independiente
- **Propósito**: Gestionar información de tareas/trabajos escolares
- **Patrón**: Entidad de datos con validaciones

#### Atributos:
```cpp
private:
  string course;        // Curso al que pertenece la tarea
  string teacher;       // Profesor que asignó la tarea
  string date;          // Fecha de entrega
  bool delivered;       // Estado: entregada (true) o pendiente (false)
  string studentCode;   // Código del alumno al que pertenece
```

#### Funcionalidades Principales:
1. **Gestión de Estado**: Controla si una tarea está entregada o pendiente
2. **Trazabilidad**: Mantiene relación con alumno y profesor
3. **Información Temporal**: Registra fechas de entrega
4. **Validación Booleana**: Usa true/false para estado de entrega (según requerimientos)

#### ¿Por qué es importante?
- **Seguimiento Académico**: Permite monitorear el progreso de cada estudiante
- **Relación de Datos**: Conecta alumnos con profesores a través de las tareas
- **Reportes**: Facilita generación de estadísticas de rendimiento

---

### 🎓 Clase Alumno (Hereda de Persona)

La clase `Alumno` representa a los **estudiantes** del sistema escolar.

#### Características:
- **Tipo**: Clase derivada (hereda de Persona)
- **Propósito**: Gestionar información específica de estudiantes
- **Patrón**: Herencia + Composición (tiene lista de tareas)

#### Atributos:
```cpp
private:
  string code;                    // Código único del alumno
  int grade;                      // Grado escolar (1-6)
  vector<Tarea*> assignments;     // Lista de tareas usando punteros
```

#### Funcionalidades Principales:
1. **Herencia**: Obtiene name y lastName de Persona
2. **Gestión de Tareas**: Administra su lista personal de tareas
3. **Validaciones**: Verifica que el grado sea válido (1-6)
4. **Estadísticas**: Calcula porcentajes de entregas y rendimiento
5. **Búsquedas**: Encuentra tareas específicas por curso/profesor

#### Conceptos Técnicos Demostrados:
- **Herencia**: `class Alumno : public Persona`
- **Punteros Dinámicos**: `vector<Tarea*>` usa punteros para gestión de memoria
- **Métodos Virtuales**: Sobrescribe `showData()` de Persona
- **Gestión de Memoria**: Destructor libera memoria de tareas

#### ¿Por qué usar punteros?
- **Eficiencia**: No copia objetos grandes, solo referencias
- **Memoria Dinámica**: Permite crear/eliminar tareas en tiempo de ejecución
- **Relaciones**: Multiple objetos pueden referenciar la misma tarea

---

### 👨‍🏫 Clase Profesor (Hereda de Persona)

La clase `Profesor` representa a los **docentes** del sistema escolar.

#### Características:
- **Tipo**: Clase derivada (hereda de Persona)
- **Propósito**: Gestionar información de profesores y sus relaciones con alumnos
- **Patrón**: Herencia + Agregación (referencia alumnos sin poseerlos)

#### Atributos:
```cpp
private:
  string idProfesor;                    // ID único del profesor
  vector<string> cursosImpartidos;      // Cursos que enseña
  vector<Alumno*> alumnosACargo;        // Alumnos bajo su responsabilidad
```

#### Funcionalidades Principales:
1. **Herencia**: Reutiliza atributos de Persona (name, lastName)
2. **Relación Profesor-Alumno**: Mantiene lista de alumnos usando punteros
3. **Gestión de Cursos**: Administra qué materias enseña
4. **Multigigrado**: Un profesor puede enseñar en diferentes grados
5. **Estadísticas**: Calcula cantidad de alumnos y distribución por grado

#### Conceptos Técnicos Demostrados:
- **Agregación**: Referencia alumnos sin "poseerlos" (no los crea ni destruye)
- **Punteros como Referencias**: `vector<Alumno*>` para relaciones
- **Forward Declaration**: Evita dependencias circulares con `class Alumno;`
- **Métodos de Búsqueda**: Encuentra alumnos por diferentes criterios

#### Relación Profesor-Alumno con Punteros:
```cpp
// El profesor mantiene referencias a alumnos
vector<Alumno*> alumnosACargo;

// Puede agregar/quitar alumnos sin afectar su existencia
void agregarAlumno(Alumno* alumno);
void eliminarAlumno(const string& codigoAlumno);
```

---

### 🏫 Clase Sistema (Controlador Principal)

La clase `Sistema` es el **núcleo administrativo** que coordina todas las entidades.

#### Características:
- **Tipo**: Clase controladora/manager
- **Propósito**: Administrar todas las entidades del sistema
- **Patrón**: Singleton-like (una instancia controla todo)

#### Atributos:
```cpp
private:
  vector<Alumno*> alumnos;        // Todos los alumnos del sistema
  vector<Profesor*> profesores;   // Todos los profesores del sistema
  vector<Tarea*> tareas;          // Todas las tareas del sistema
```

#### Funcionalidades Principales:

##### 1. **Registro de Entidades**
- Crea alumnos, profesores y tareas usando `new`
- Valida unicidad de códigos e IDs
- Verifica integridad referencial

##### 2. **Gestión de Memoria**
- **Creación**: Usa `new` para asignación dinámica
- **Liberación**: Usa `delete` en destructor para evitar memory leaks
- **RAII**: Resource Acquisition Is Initialization

##### 3. **Búsquedas y Consultas**
- Búsqueda por código, nombre, grado, curso
- Filtros y criterios múltiples
- Algoritmos de búsqueda lineal

##### 4. **Relaciones entre Entidades**
- Conecta automáticamente profesores con alumnos
- Asigna tareas manteniendo consistencia
- Valida existencia antes de crear relaciones

##### 5. **Reportes y Estadísticas**
- Calcula rendimiento por alumno
- Genera estadísticas de profesores
- Análisis de entregas y pendientes

##### 6. **Persistencia**
- Guarda datos en archivos de texto
- Estructura para carga de datos
- Backup del estado del sistema

#### Conceptos Técnicos Demostrados:

##### **Gestión Dinámica de Memoria**:
```cpp
// Creación dinámica
Alumno* nuevoAlumno = new Alumno(nombres, apellidos, codigo, grado);
alumnos.push_back(nuevoAlumno);

// Liberación en destructor
Sistema::~Sistema() {
    for(Alumno* alumno : alumnos) {
        delete alumno;  // Liberar memoria
    }
}
```

##### **Validaciones de Integridad**:
```cpp
// Verificar que el profesor existe antes de asignar tarea
Profesor* profesor = buscarProfesorPorNombre(nombreProfesor);
if (profesor == nullptr) {
    return false;  // Error: profesor no existe
}
```

##### **Relaciones con Punteros**:
```cpp
// Establecer relación bidireccional
alumno->agregarTarea(nuevaTarea);           // Alumno -> Tarea
profesor->agregarAlumno(alumno);            // Profesor -> Alumno
```

#### ¿Por qué Sistema es importante?
- **Centralización**: Un punto de control para todas las operaciones
- **Consistencia**: Mantiene la integridad de datos
- **Escalabilidad**: Fácil agregar nuevas funcionalidades
- **Abstracción**: Oculta complejidad al usuario final

---

### 💻 Archivo main.cpp (Interfaz de Usuario)

El archivo `main.cpp` proporciona la **interfaz de usuario** y el **punto de entrada** del programa.

#### Funcionalidades:
1. **Menú Interactivo**: Sistema de menús navegables
2. **Validación de Entrada**: Verifica datos del usuario
3. **Demostración**: Carga datos de ejemplo
4. **Control de Flujo**: Bucle principal del programa

#### Características Técnicas:
- **Separación de Responsabilidades**: UI separada de lógica de negocio
- **Manejo de Errores**: Validación de entrada y mensajes de error
- **Experiencia de Usuario**: Menús claros y pausas para lectura

---

## 🔧 Conceptos de C++ Demostrados

### 1. **Herencia**
```cpp
class Persona { /* clase base */ };
class Alumno : public Persona { /* clase derivada */ };
class Profesor : public Persona { /* clase derivada */ };
```

### 2. **Punteros Dinámicos**
```cpp
vector<Tarea*> assignments;    // Vector de punteros
Tarea* tarea = new Tarea(...); // Crear en heap
delete tarea;                  // Liberar memoria
```

### 3. **Gestión de Memoria**
```cpp
// Constructor: crea objetos
Alumno* alumno = new Alumno(...);

// Destructor: libera memoria
~Sistema() {
    for(auto* alumno : alumnos) {
        delete alumno;
    }
}
```

### 4. **Encapsulación**
```cpp
private:
    string code;           // Atributo privado
public:
    string getCode() const; // Método público de acceso
```

### 5. **Polimorfismo**
```cpp
virtual void showData() const = 0;  // Método virtual puro
// Cada clase derivada implementa su versión
```

### 6. **Relaciones entre Objetos**
- **Composición**: Alumno "tiene" Tareas (las crea y destruye)
- **Agregación**: Profesor "referencia" Alumnos (no los posee)
- **Asociación**: Sistema coordina todas las entidades

---

## 🎯 Objetivos de Aprendizaje Cumplidos

### ✅ **Clases en C++**
- Implementación de múltiples clases interrelacionadas
- Uso de constructores y destructores
- Métodos públicos y privados

### ✅ **Manejo de Punteros**
- Punteros dinámicos para gestión de memoria
- Vectores de punteros para relaciones
- Referencias entre objetos

### ✅ **Administración de Memoria**
- Uso correcto de `new` y `delete`
- Prevención de memory leaks
- RAII (Resource Acquisition Is Initialization)

### ✅ **Diseño Orientado a Objetos**
- Herencia para reutilización de código
- Encapsulación para proteger datos
- Polimorfismo para flexibilidad
- Abstracción para simplicidad

---

## 📊 Flujo del Sistema

```
1. Sistema se inicia
   ↓
2. Carga datos de ejemplo
   ↓
3. Usuario selecciona opción del menú
   ↓
4. Sistema valida entrada
   ↓
5. Ejecuta operación solicitada
   ↓
6. Actualiza relaciones entre entidades
   ↓
7. Muestra resultados al usuario
   ↓
8. Regresa al menú principal
```

Este sistema demuestra de manera práctica y completa el uso de conceptos avanzados de C++, especialmente la gestión de memoria dinámica, relaciones entre clases mediante punteros, y un diseño orientado a objetos robusto y escalable.