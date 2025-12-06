# Ejercicio 03 - Conexión Simulada a Base de Datos

## Descripción
Crea una clase ConexionBD que simule la conexión a una base de
datos.
- Solo debe haber una conexión activa (Singleton).
- Incluye métodos como conectar(), desconectar() y estado().
- Si alguien intenta crear otra conexión, debe devolverse la ya
existente.

## Implementación

### Clase `DBConnector.java` - Singleton

Esta clase:
- Contiene un atributo estático `instancia` que almacena la única instancia del conector.
- Tiene un constructor privado que inicializa el estado como desconectado y muestra un mensaje de creación única.
- Expone un método público `getInstancia()` que devuelve siempre la misma instancia.

#### Funcionalidades principales:

- `connect()`: Simula la conexión a la base de datos. Si ya está conectada, muestra un mensaje de advertencia.

- `disconnect()`: Simula la desconexión de la base de datos, evitando cerrar conexiones inexistentes.

- `getStatus()`: Muestra si la base de datos está conectada o no.

### Clase `Main.java` - Demostración
Se demuestra que aunque se obtengan varias referencias mediante `getInstancia()`, todas apuntan al mismo objeto Singleton, compartiendo el mismo estado de conexión.

## Flujo de Demostración
1. **Primera instancia (dbConnector1)**: Crea el objeto, imprime "instance created"
2. **Verificar estado inicial**: Muestra "not connected"
3. **Conectar**: Cambia estado y muestra "Connected to the database"
4. **Verificar estado conectado**: Confirma conexión activa
5. **Segunda "instancia" (dbConnector2)**: NO crea nuevo objeto, retorna el existente
6. **Desconectar desde dbConnector2**: Afecta el estado compartido
7. **Comparación de referencias**: Verifica que ambas variables apuntan al mismo objeto (`==` retorna `true`)
8. **Comparación de hashCodes**: Confirma que son la misma instancia (hashCodes idénticos)