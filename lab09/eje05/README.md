# Ejercicio 05 - Singleton Thread-Safe (Desafío)

## Descripción del Ejercicio
Modifica el ejercicio 3 (conexión a BD) o el 2 (Logger) para
hacerlo seguro en entornos multihilo.
- Usa bloqueo o una verificación doble (double-checked locking)
para evitar que se creen múltiples instancias en hilos
distintos.

## Implementación

### Clase `ThreadSafeDBConnector.java` - Singleton Thread-Safe

Esta clase:
- Usa una variable estática volatile instance para asegurar la visibilidad de cambios entre hilos.
- Aplica double-checked locking en el método getInstance() para evitar la creación múltiple de instancias bajo concurrencia.
- El constructor es privado, evitando instanciación directa.

#### Funcionalidades principales:

- `connect()`: Simula el establecimiento de la conexión e informa qué hilo la realizó.
- `disconnect()`: Simula el cierre de la conexión del hilo correspondiente.
- `isConnected()`: Indica si el hilo actual mantiene una conexión activa.

### Clase `ThreadSafeMain.java` - Demostración Multihilo

Simula un entorno multihilo donde varios hilos intentan obtener la instancia del conector simultáneamente.
Se demuestra que todos los hilos acceden a la misma instancia Singleton, garantizando la seguridad frente a condiciones de carrera.