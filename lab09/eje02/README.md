# Ejercicio 02 - Singleton con Recursos Compartidos (Logger)

## Descripción
Implemente una clase Logger que registre mensajes de log en un
archivo de texto (por ejemplo bitacora.log).
- Solo debe existir una instancia de Logger.
- Implementa un método log(mensaje) que agregue el texto al
archivo con la hora actual.
- Prueba el logger desde distintos puntos del programa y
confirma que todos usan el mismo archivo.

## Implementación

### Clase `Logger.java` - Singleton
Esta clase:

- Contiene un atributo estático `instancia` que guarda la única instancia del objeto.
- Tiene un constructor privado que abre el archivo `bitacora.log` en modo append, evitando sobrescribir el contenido anterior.
- Expone un método público `getInstancia()` que devuelve la única instancia de la clase.

#### Funcionalidades principales:
- `log(String mensaje)`: Registra un mensaje con la fecha y hora actual en el archivo `bitacora.log`.
- `close()`: Cierra el archivo correctamente y libera los recursos.

### Clase `Main.java` - Demostración
Se demuestra que aunque diferentes partes del programa obtengan el logger mediante `getInstancia()`, todas escriben en el mismo archivo compartido.

## Flujo del Programa
- Obtiene la instancia única del Logger con `getInstance()`
- Registra mensaje de inicio del programa
- Llama a `funcionA()` y `funcionB()` que acceden al mismo logger
- Cada función obtiene el logger independientemente sin pasarlo como parámetro
- Registra mensaje de fin y cierra el logger

## Conceptos Clave

**Flush Inmediato**: Los logs son visibles instantáneamente sin esperar al buffer, evitando pérdida de datos si el programa falla

**Append Mode**: Preserva logs de ejecuciones anteriores creando un historial completo

**Thread-Safety Parcial**: Suficiente para uso básico con sincronización en `getInstance()` y `log()`
