package main

import (
	"fmt"
	"math"
	"sync"
)

// Estructura para una tarea
type Tarea struct {
	inicio int
	fin    int
	h      float64
}

// Pool de workers
type PoolWorkers struct {
	numWorkers int
	tareas     chan Tarea
	resultados chan float64
	wg         sync.WaitGroup
}

// Crear nuevo pool de workers
func NuevoPool(numWorkers int) *PoolWorkers {
	return &PoolWorkers{
		numWorkers: numWorkers,
		tareas:     make(chan Tarea, 100),
		resultados: make(chan float64, 100),
	}
}

// Funcion a integrar
func f(x float64) float64 {
	return 2.0*x*x + 3.0*x + 0.5
}

// Worker que procesa tareas
func (p *PoolWorkers) worker(inicioIntegracion float64) {
	defer p.wg.Done()

	for tarea := range p.tareas {
		sumaLocal := 0.0

		// Calcular area de los trapecios asignados
		for i := tarea.inicio; i < tarea.fin; i++ {
			x1 := inicioIntegracion + float64(i)*tarea.h
			x2 := inicioIntegracion + float64(i+1)*tarea.h
			// Formula del trapecio
			sumaLocal += (f(x1) + f(x2)) * tarea.h / 2.0
		}

		// Enviar resultado
		p.resultados <- sumaLocal
	}
}

// Iniciar el pool
func (p *PoolWorkers) iniciar(inicioIntegracion float64) {
	// Crear workers
	for i := 0; i < p.numWorkers; i++ {
		p.wg.Add(1)
		go p.worker(inicioIntegracion)
	}
}

// Enviar tarea al pool
func (p *PoolWorkers) enviarTarea(tarea Tarea) {
	p.tareas <- tarea
}

// Cerrar el pool
func (p *PoolWorkers) cerrar() {
	close(p.tareas)
	p.wg.Wait()
	close(p.resultados)
}

// Obtener resultado
func (p *PoolWorkers) obtenerResultado() float64 {
	return <-p.resultados
}

// Estructura principal del trapecio
type TrapecioPool struct {
	inicio float64
	fin    float64
	n      int
}

// Constructor
func NuevoTrapecioPool(a, b float64, numTrapecios int) *TrapecioPool {
	return &TrapecioPool{
		inicio: a,
		fin:    b,
		n:      numTrapecios,
	}
}

// Integrar usando pool de workers
func (t *TrapecioPool) integrar(numWorkers int) float64 {
	h := (t.fin - t.inicio) / float64(t.n)
	trapeciosPorWorker := t.n / numWorkers

	// Crear pool
	pool := NuevoPool(numWorkers)
	pool.iniciar(t.inicio)

	// Enviar tareas
	for i := 0; i < numWorkers; i++ {
		inicio := i * trapeciosPorWorker
		fin := inicio + trapeciosPorWorker
		if i == numWorkers-1 {
			fin = t.n // El ultimo toma los restantes
		}

		tarea := Tarea{
			inicio: inicio,
			fin:    fin,
			h:      h,
		}
		pool.enviarTarea(tarea)
	}

	// Recoger resultados
	resultadoTotal := 0.0
	for i := 0; i < numWorkers; i++ {
		resultadoTotal += pool.obtenerResultado()
	}

	// Cerrar pool
	pool.cerrar()

	// Redondear a 2 decimales
	return math.Round(resultadoTotal*100) / 100
}

func main() {
	fmt.Println("=== Integracion con Pool de Workers===")
	fmt.Println("Funcion: f(x) = 2x^2 + 3x + 0.5")
	fmt.Println("Limites: a = 2, b = 20")

	a := 2.0
	b := 20.0
	areaAnterior := -1.0
	areaActual := 0.0
	n := 1
	numWorkers := 4

	fmt.Printf("\nCalculando area con Pool de Workers:\n")
	fmt.Printf("Workers en pool: %d\n", numWorkers)
	fmt.Println("----------------------------------------")

	// Buscar convergencia
	for {
		trapecio := NuevoTrapecioPool(a, b, n)
		areaActual = trapecio.integrar(numWorkers)

		fmt.Printf("N = %d trapecios -> Area = %.2f\n", n, areaActual)

		// Verificar convergencia
		if math.Abs(areaActual-areaAnterior) < 0.01 {
			fmt.Println("\nConvergencia alcanzada con Pool de Workers")
			break
		}

		areaAnterior = areaActual
		n++

		// Limite de seguridad
		if n > 100000 {
			fmt.Println("Limite maximo alcanzado")
			break
		}
	}

	fmt.Println("\n=== RESULTADO FINAL (Pool) ===")
	fmt.Printf("Area bajo la curva: %.2f\n", areaActual)
	fmt.Printf("Nro de trapecios: %d\n", n)
	fmt.Printf("Pool de workers utilizado: %d workers\n", numWorkers)
}
