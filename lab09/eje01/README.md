# Ejercicio 01 - Implementación Directa del Singleton

## Descripción
Crear una clase Configuracion que almacene las configuraciones
generales del sistema (por ejemplo, idioma y zona horaria).
- Asegúrate de que solo exista una instancia de esta clase.
- Añade un método mostrar_configuracion() que imprima los
valores actuales.
- Verifica en el main que aunque crees varios objetos, todos
apunten al mismo.

## Implementación

### Clase `Configuracion.java` - Singleton

Esta clase:
- Contiene un atributo estático `instancia` que guarda la única instancia del objeto.
- Tiene un constructor privado para evitar la creación de objetos desde fuera.
- Expone un método público getInstancia() que devuelve la única instancia de la clase.

Funcionalidades principales:
- `mostrarConfiguracion()`: Muestra el idioma y la zona horaria actuales.
- `actualizarConfiguracion(String idioma, String zonaHoraria)`: Permite modificar los valores.

### Clase `Main.java` - Demostración

Se demuestra que aunque se llamen varias veces a getInstancia(), todas las referencias apuntan al mismo objeto Singleton.
