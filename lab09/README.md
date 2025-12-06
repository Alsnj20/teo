# Lab 09 - Ejercicios sobre Singleton

## Integrantes
- Jara Mamani, Mariel Alisson   

## Descripción
En este laboratorio se implementa el patrón de diseño Singleton en lenguajes como C++ y Java. El patrón Singleton asegura que una clase tenga una única instancia y proporciona un punto de acceso global a esa instancia.

## Link de los ejercicios
- [Ejercicio 01 (Básico): Implementación directa del Singleton](./eje01/)
- [Ejercicio 02 (Intermedio): Singleton con recursos compartidos](./eje02/)
- [Ejercicio 03 (Aplicado): Conexión simulada a base de datos](./eje03/)
- [Ejercicio 04 (Avanzado): Singleton en un juego](./eje04/)
- [Ejercicio 05 (Desafío): Singleton con subprocesos (thread-safe)](./eje05/)

## Cuestionario
### 1. ¿Qué desventajas tiene el patrón Singleton en pruebas unitarias?
El patrón Singleton puede dificultar las pruebas unitarias debido a su naturaleza global y estado compartido. Al tener una única instancia, puede ser complicado aislar las pruebas, ya que los cambios en el estado de la instancia pueden afectar otras pruebas. Además, puede ser difícil simular o reemplazar la instancia Singleton durante las pruebas, limitando la capacidad de probar diferentes escenarios.

**Por ejemplo:** Si una clase Singleton mantiene una conexión a una base de datos, las pruebas unitarias que dependen de esa conexión pueden fallar si la conexión no está disponible o si el estado de la base de datos cambia entre pruebas.

### 2. ¿Cuándo no es recomendable usar Singleton?
No es recomendable usar el patrón Singleton en situaciones donde se requiere flexibilidad y escalabilidad, como en aplicaciones que necesitan **varias instancias** de una clase para diferentes contextos o configuraciones. También puede ser inapropiado en entornos multihilo si no se implementa correctamente para ser thread-safe, ya que puede llevar a condiciones de carrera y problemas de concurrencia. Además, el uso excesivo de Singletons puede llevar a un diseño acoplado y dificultar la mantenibilidad del código.

### 3. ¿Cómo se diferencia de una clase estática?
Una clase estática no permite la creación de instancias y todos sus miembros son estáticos **(fijos y globales)**, lo que significa que no se puede mantener un estado individual para diferentes contextos. En contraste, una clase Singleton permite la creación de una única instancia que puede mantener un estado y comportarse como un objeto normal. Además, una clase Singleton puede implementar interfaces y heredar de otras clases, mientras que una clase estática no puede hacerlo.
