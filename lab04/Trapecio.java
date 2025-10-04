package lab04;

import java.util.*;
import java.util.concurrent.atomic.AtomicReference;

public class Trapecio {

  // Interfaz para funciones matemáticas
  public interface Function {
    double eval(double x);
  }

  // Define nuestra funcion 2x^2 + 3x + 0.5
  public static class Quadratic implements Function {
    public double eval(double x) {
      return 2.0 * x * x + 3.0 * x + 0.5;
    }
  }

  // Suma los trapecios de [startIndex, endIndex) donde cada índice i corresponde
  // al subintervalo [a + i*h, a + (i+1)*h]
  public static class TrapezoidWorker extends Thread {
    private final double a;
    private final double h;
    private final long startIndex;
    private final long endIndex;
    private final Function f;
    private double partialSum = 0.0;

    public TrapezoidWorker(double a, double h, long startIndex, long endIndex, Function f) {
      this.a = a;
      this.h = h;
      this.startIndex = startIndex;
      this.endIndex = endIndex;
      this.f = f;
    }

    @Override
    public void run() {
      double sum = 0.0;
      // Para cada trapecio i, computamos f(x_i) + f(x_{i+1})
      for (long i = startIndex; i < endIndex; i++) {
        double x_i = a + i * h;
        double x_next = x_i + h;
        sum += 0.5 * (f.eval(x_i) + f.eval(x_next)) * h;
      }
      partialSum = sum;
    }

    public double getPartialSum() {
      return partialSum;
    }
  }

  // Integración del trapecio usando múltiples threads
  public static double integrateWithThreads(Function f, double a, double b, long n, int numThreads)
      throws InterruptedException {
    if (n <= 0)
      return 0.0;
    double h = (b - a) / (double) n;
    // Si n < numThreads, no tiene sentido usar más threads que n
    int threadsToUse = (int) Math.min(numThreads, n);
    long base = n / threadsToUse;
    long rem = n % threadsToUse;

    TrapezoidWorker[] workers = new TrapezoidWorker[threadsToUse];
    long index = 0;
    for (int t = 0; t < threadsToUse; t++) {
      long take = base + (t < rem ? 1 : 0);
      long start = index;
      long end = index + take;
      workers[t] = new TrapezoidWorker(a, h, start, end, f);
      index = end;
      workers[t].start();
    }

    double total = 0.0;
    for (int t = 0; t < threadsToUse; t++) {
      workers[t].join();
      total += workers[t].getPartialSum();
    }
    return total;
  }

  // Verifica si un valor ya ha sido visto, usando un conjunto de hashes
  private static boolean repeated(double value, Set<Long> seenHashes, double epsilon) {
    // No podemos comparar doubles exactamente; usamos redondeo a bits mediante
    // escalado.
    // Creamos un hash largo redondeando al bucket más cercano definido por epsilon
    long bucket = Math.round(value / epsilon);
    if (seenHashes.contains(bucket))
      return true;
    seenHashes.add(bucket);
    return false;
  }
}