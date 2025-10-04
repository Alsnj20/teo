# Makefile para el Sistema de Gestión Escolar
# Compila todos los archivos .cpp y crea el ejecutable

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

# Nombre del ejecutable
TARGET = sistema_escolar

# Archivos fuente
SOURCES = main.cpp Persona.cpp Alumno.cpp Profesor.cpp Tarea.cpp Sistema.cpp

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Archivos header
HEADERS = Persona.h Alumno.h Profesor.h Tarea.h Sistema.h

# Regla principal
all: $(TARGET)

# Crear el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Compilación completada. Ejecutar con: ./$(TARGET)"

# Compilar archivos objeto
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Archivos de compilación eliminados."

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Reglas que no son archivos
.PHONY: all clean run

# Información sobre el proyecto
info:
	@echo "=========================================="
	@echo "  SISTEMA DE GESTIÓN ESCOLAR"
	@echo "=========================================="
	@echo "Archivos fuente: $(SOURCES)"
	@echo "Archivos header: $(HEADERS)"
	@echo "Ejecutable: $(TARGET)"
	@echo "Compilador: $(CXX) $(CXXFLAGS)"
	@echo "=========================================="
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make       - Compilar el proyecto"
	@echo "  make run   - Compilar y ejecutar"
	@echo "  make clean - Limpiar archivos compilados"
	@echo "  make info  - Mostrar esta información"