#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>

using namespace std;

class Trapecio {
private:
    double start, end;   // límites de integración
    int n;               // número de trapecios
    double result;       // área calculada
    mutex mtx;           // mutex para proteger result

    // Función a integrar: f(x) = 2x² + 3x + 0.5
    double f(double x) {
        return 2.0 * x * x + 3.0 * x + 0.5;
    }

    // Calcular área parcial para un rango de trapecios
    void calculateRange(int begin, int finish, double h) {
        double localSum = 0.0;
        
        for (int i = begin; i < finish; i++) {
            double x1 = start + i * h;
            double x2 = start + (i + 1) * h;
            // Fórmula del trapecio: (f(x1) + f(x2)) * h / 2
            localSum += (f(x1) + f(x2)) * h / 2.0;
        }
        
        // Proteger result de múltiples threads
        lock_guard<mutex> lock(mtx);
        result += localSum;
    }

    // Redondear a n decimales
    double roundTo(double value, int decimals) {
        double factor = 1.0;
        for (int i = 0; i < decimals; i++) {
            factor *= 10.0;
        }
        return round(value * factor) / factor;
    }

public:
    Trapecio(double a, double b, int numTrapecios) : start(a), end(b), n(numTrapecios), result(0.0) {}

    double integrate(int numThreads) {
        result = 0.0; 
        double h = (end - start) / n;  // ancho de cada trapecio
        vector<thread> threads;
        
        int trapezoidsPerThread = n / numThreads;

        // Crear threads para procesar rangos
        for (int i = 0; i < numThreads; i++) {
            int begin = i * trapezoidsPerThread;
            int finish = (i == numThreads - 1) ? n : (i + 1) * trapezoidsPerThread;
            
            threads.emplace_back(&Trapecio::calculateRange, this, begin, finish, h);
        }

        // Esperar que terminen todos los threads
        for (auto &thread : threads) {
            thread.join();
        }

        return roundTo(result, 2);
    }
};

int main() {
    cout << "=== Integracion por Metodo del Trapecio ===" << endl;
    cout << "Función: f(x) = 2x^2 + 3x + 0.5" << endl;
    cout << "Límites: a = 2, b = 20" << endl;
    
    double a = 2.0, b = 20.0;
    double previousArea = -1.0, currentArea = 0.0;
    int n = 1;
    int numThreads = 4;
    
    cout << "\nCalculando area con diferentes números de trapecios:" << endl;
    cout << "Threads utilizados: " << numThreads << endl;
    cout << "----------------------------------------" << endl;

    while (true) {
        Trapecio* trapecio = new Trapecio(a, b, n);
        currentArea = trapecio->integrate(numThreads);
        delete trapecio;

        cout << "N = " << n << " trapecios -> Area = " << currentArea << endl;

        // Verificar convergencia
        if (fabs(currentArea - previousArea) < 0.01) {
            cout << "\nConvergencia alcanzada" << endl;
            break;
        }

        previousArea = currentArea;
        n++;
        
        // Límite de seguridad
        if (n > 100000) {
            cout << "Límite máximo alcanzado" << endl;
            break;
        }
    }

    cout << "\n=== RESULTADO FINAL ===" << endl;
    cout << "Area bajo la curva: " << currentArea << endl;
    cout << "Nro de trapecios: " << n << endl;
    
    return 0;
}
