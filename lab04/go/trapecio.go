package main

import (
	"fmt"
	"math"
	"sync"
)

// Estructura para el trapecio
type Trapecio struct {
	inicio    float64
	fin       float64
	n         int
	resultado float64
	mutex     sync.Mutex
}

// Constructor del trapecio
func NuevoTrapecio(a, b float64, numTrapecios int) *Trapecio {
	return &Trapecio{
		inicio:    a,
		fin:       b,
		n:         numTrapecios,
		resultado: 0.0,
	}
}

// Funcion a integrar
func (t *Trapecio) f(x float64) float64 {
	return 2.0*x*x + 3.0*x + 0.5
}

// Calcular area parcial para un rango de trapecios
func (t *Trapecio) calcularRango(inicio, fin int, h float64, wg *sync.WaitGroup) {
	defer wg.Done() // Avisar que termino esta goroutine

	sumaLocal := 0.0

	// Calcular area de los trapecios asignados
	for i := inicio; i < fin; i++ {
		x1 := t.inicio + float64(i)*h
		x2 := t.inicio + float64(i+1)*h
		// Formula del trapecio: (f(x1) + f(x2)) * h / 2
		sumaLocal += (t.f(x1) + t.f(x2)) * h / 2.0
	}

	// Proteger el resultado compartido
	t.mutex.Lock()
	t.resultado += sumaLocal
	t.mutex.Unlock()
}

// Integrar usando goroutines
func (t *Trapecio) integrar(numGoroutines int) float64 {
	t.resultado = 0.0
	h := (t.fin - t.inicio) / float64(t.n)

	var wg sync.WaitGroup
	trapeciosPorGoroutine := t.n / numGoroutines

	// Crear goroutines para procesar rangos
	for i := 0; i < numGoroutines; i++ {
		inicio := i * trapeciosPorGoroutine
		fin := inicio + trapeciosPorGoroutine
		if i == numGoroutines-1 {
			fin = t.n // El ultimo toma los restantes
		}

		wg.Add(1) // Agregar una goroutine al contador
		go t.calcularRango(inicio, fin, h, &wg)
	}

	// Esperar que terminen todas las goroutines
	wg.Wait()

	// Redondear a 2 decimales
	return math.Round(t.resultado*100) / 100
}

func main() {
	fmt.Println("=== Integracion por Metodo del Trapecio===")
	fmt.Println("Funcion: f(x) = 2x^2 + 3x + 0.5")
	fmt.Println("Limites: a = 2, b = 20")

	a := 2.0
	b := 20.0
	areaAnterior := -1.0
	areaActual := 0.0
	n := 1
	numGoroutines := 4

	fmt.Printf("\nCalculando area con diferentes numeros de trapecios:\n")
	fmt.Printf("Goroutines utilizadas: %d\n", numGoroutines)
	fmt.Println("----------------------------------------")

	// Buscar convergencia
	for {
		trapecio := NuevoTrapecio(a, b, n)
		areaActual = trapecio.integrar(numGoroutines)

		fmt.Printf("N = %d trapecios -> Area = %.2f\n", n, areaActual)

		// Verificar convergencia
		if math.Abs(areaActual-areaAnterior) < 0.01 {
			fmt.Println("\nConvergencia alcanzada")
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

	fmt.Println("\n=== RESULTADO FINAL ===")
	fmt.Printf("Area bajo la curva: %.2f\n", areaActual)
	fmt.Printf("Nro de trapecios: %d\n", n)
}
