# Ejercicio 04 - Singleton en un Juego

## Descripción del Ejercicio
Desarrolla una clase ControlJuego para manejar el estado global de un juego (nivel actual, puntaje, vidas).
- Usa Singleton para que todos los componentes (jugador,
enemigos, interfaz) consulten y modifiquen el mismo estado.
- Simula en el main cómo distintos módulos acceden al mismo
ControlJuego.

## Implementación

### Clase `GameState.java` - Singleton

Esta clase:
- Contiene un atributo estático instancia que guarda la única instancia del estado del juego.
- Posee un constructor privado que inicializa los valores iniciales (puntaje 0, 3 vidas, nivel 1).
- Expone un método getInstancia() sincronizado que devuelve siempre la misma instancia.

#### Funcionalidades principales:

- `addScore(int points)`: Suma puntos al puntaje y sube de nivel automáticamente al alcanzar el umbral.
- `loseLife()`: Resta una vida y finaliza el juego si llega a 0.
- `reset()`: Reinicia el juego restaurando valores iniciales.
- `toString()`: Muestra el estado actual del juego (puntaje, vidas y nivel).

### Integración con Otras Clases

- **Player.java**: Obtiene la instancia de GameState y actualiza el estado según el movimiento o colisiones.
- **FallingObject.java**: Accede al estado para aumentar puntaje o restar vidas según el resultado.
- **GamePanel.java**: Controla la interfaz del juego, reinicia con reset() y muestra el HUD con toString().

### Clase `Main.java` - Demostración
Inicializa el juego y demuestra que todos los componentes comparten el mismo estado, incluso tras reiniciar o perder vidas.

## Flujo del Juego

**Atrapar objeto**: addScore(10) → Si score ≥ nivel×100 → levelUp() → Velocidad aumenta

**Objeto perdido**: loseLife() → Si lives ≤ 0 → gameOver() → Juego se detiene


## Cómo Ejecutar

**Controles**:
- **Flechas izquierda/derecha o A/D**: Mover jugador (se recomienda usar ambas porque el juego es sospechosamente imposible de otra manera)
- **R**: Reiniciar tras perder todas las vidas

**Compilar y ejecutar**:
```bash
# Compilar
javac *.java

# Ejecutar
java Main

# O usar el script
chmod +x run.sh
bash ./run.sh
```