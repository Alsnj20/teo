#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include <cmath>

using namespace std;

// Pool de threads reutilizable
class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queueMutex;
    condition_variable condition;
    bool stop;

public:
    ThreadPool(size_t numThreads) : stop(false) {
        for(size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while(true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(this->queueMutex);
                        this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty()) return;
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<class F>
    void enqueue(F&& f) {
        {
            unique_lock<mutex> lock(queueMutex);
            tasks.emplace(forward<F>(f));
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for(thread &worker: workers) worker.join();
    }
};

class TrapecioPool {
private:
    double start, end;
    int n;
    double result;
    mutex resultMutex;

    double f(double x) {
        return 2.0 * x * x + 3.0 * x + 0.5;
    }

public:
    TrapecioPool(double a, double b, int numTrapecios) : start(a), end(b), n(numTrapecios), result(0.0) {}

    double integrate(ThreadPool& pool, int numThreads) {
        result = 0.0;
        double h = (end - start) / n;
        int trapezoidsPerThread = n / numThreads;
        
        // Contador para saber cuando terminan todos los threads
        mutex counterMutex;
        condition_variable cv;
        int completedTasks = 0;

        for (int i = 0; i < numThreads; i++) {
            int begin = i * trapezoidsPerThread;
            int finish = (i == numThreads - 1) ? n : (i + 1) * trapezoidsPerThread;
            
            pool.enqueue([this, begin, finish, h, &counterMutex, &cv, &completedTasks, numThreads]() {
                double localSum = 0.0;
                for (int j = begin; j < finish; j++) {
                    double x1 = start + j * h;
                    double x2 = start + (j + 1) * h;
                    localSum += (f(x1) + f(x2)) * h / 2.0;
                }
                
                {
                    lock_guard<mutex> lock(resultMutex);
                    result += localSum;
                }
                
                {
                    lock_guard<mutex> lock(counterMutex);
                    completedTasks++;
                    if (completedTasks == numThreads) {
                        cv.notify_one();
                    }
                }
            });
        }

        // Esperar a que terminen todas las tareas
        unique_lock<mutex> lock(counterMutex);
        cv.wait(lock, [&completedTasks, numThreads]() { return completedTasks == numThreads; });

        return round(result * 100.0) / 100.0;
    }
};

int main() {
    cout << "=== Integracion con Pool de Threads ===" << endl;
    cout << "Funcion: f(x) = 2x^2 + 3x + 0.5" << endl;
    cout << "Limites: a = 2, b = 20" << endl;
    
    double a = 2.0, b = 20.0;
    double previousArea = -1.0, currentArea = 0.0;
    int n = 1;
    int numThreads = 4;
    
    // Creacion de pool de threads una sola vez
    ThreadPool pool(numThreads);
    
    cout << "\nCalculando area con Pool de Threads:" << endl;
    cout << "Threads en pool: " << numThreads << endl;
    cout << "----------------------------------------" << endl;

    while (true) {
        TrapecioPool* trapecio = new TrapecioPool(a, b, n);
        currentArea = trapecio->integrate(pool, numThreads);
        delete trapecio;

        cout << "N = " << n << " trapecios -> Area = " << currentArea << endl;

        // Verificar convergencia
        if (fabs(currentArea - previousArea) < 0.01) {
            cout << "\nConvergencia alcanzada con Pool de Threads" << endl;
            break;
        }

        previousArea = currentArea;
        n++;
        
        // Limite de seguridad
        if (n > 100000) {
            cout << "Limite maximo alcanzado" << endl;
            break;
        }
    }

    cout << "\n=== RESULTADO FINAL (Pool) ===" << endl;
    cout << "Area bajo la curva: " << currentArea << endl;
    cout << "Nro de trapecios: " << n << endl;
    cout << "Pool de threads utilizado: " << numThreads << " threads" << endl;
    
    return 0;
}