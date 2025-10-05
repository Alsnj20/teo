# Tecnologia de Objetos - Laboratorio 04
## Metodo del Trapecio
### Descripcion
El método del trapecio es una técnica de integración numérica que aproxima el valor de una integral definida dividiendo el área bajo la curva en segmentos trapezoidales.

## Implementacion
### Java
- Implementación de un pool de threads usando `ExecutorService` y `Callable`.
- Uso de `Future` para manejar resultados de tareas asíncronas.
- Ejemplo de integración numérica usando el método del trapecio con un pool de threads.
- Archivos:
[Trapecio.java](./java/Trapecio.java)
[TrapecioPool.java](./java/TrapecioPool.java)


### C++
- Implementación de un pool de threads usando `std::thread`, `std::mutex`, `std::condition_variable` y `std::queue`.
- Uso de `std::future` y `std::promise` para manejar resultados de tareas asíncronas.
- Ejemplo de integración numérica usando el método del trapecio con un pool de threads.
- Archivos:
-   [Trapecio.cpp](./cpp/trapecio.cpp)
-   [TrapecioPool.cpp](./cpp/trapecioPool.cpp)

### Go
- Implementación de un pool de goroutines usando canales (`chan`) para manejar tareas.
- Uso de goroutines para ejecutar tareas concurrentemente.
- Ejemplo de integración numérica usando el método del trapecio con un pool de goroutines.
- Archivos:
-   [Trapecio.go](./go/trapecio.go)
-   [TrapecioPool.go](./go/trapecio_pool.go)


## Preguntas
### ¿Cuál de los lenguajes posee ventajas para programar paralelamente?

**Go** es claramente superior para programación paralela.  
Fue diseñado desde cero con concurrencia en mente, usando el modelo de **goroutines**, que son mucho más ligeras que los *threads* tradicionales.  

Mientras que en **C++** y **Java** cada *thread* consume más memoria, las goroutines de Go usan desde los **2KB** y permiten crear **millones** sin problema.  
Además, Go incluye **canales (channels)** que facilitan la comunicación segura entre goroutines sin necesidad de usar *mutex* complejos.

---

### Pool de Threads en cada lenguaje

| **Aspecto**        | **Go**                      | **C++**                        | **Java**                            |
|--------------------|-----------------------------|--------------------------------|-------------------------------------|
| **Creación del Pool** | `make(chan Tarea, 100)`      | `queue<function<void()>>`       | `Executors.newFixedThreadPool(4)`   |
| **Workers**         | `go worker()` (*goroutines*) | `thread workers`                | `ThreadPoolExecutor`                |
| **Cierre del Pool** | `close(canal)`               | `stop = true; notify_all()`     | `executor.shutdown()`               |
| **Complejidad del código** | Baja                        | Alta                           | Media                               |
| **Debugging**       | Fácil                       | Difícil                        | Media                               |

---

