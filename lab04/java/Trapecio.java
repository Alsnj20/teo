package lab04.java;

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

  public static void main(String[] args) throws InterruptedException {
    double a = 2.0;
    double b = 20.0;
    long maxN = 200000L; // para evitar bucles infinitos
    int threads = Math.max(1, Runtime.getRuntime().availableProcessors());
    double epsilon = 1e-12;

    if (args.length >= 2) {
      a = Double.parseDouble(args[0]);
      b = Double.parseDouble(args[1]);
    }
    if (args.length >= 3) {
      maxN = Long.parseLong(args[2]);
    }
    if (args.length >= 4) {
      threads = Integer.parseInt(args[3]);
    }
    if (args.length >= 5) {
      epsilon = Double.parseDouble(args[4]);
    }

    Function f = new Quadratic();

    System.out.printf("Integración por trapecio (paralela con Thread) sobre [%f, %f]\n", a, b);
    System.out.printf("Máx n: %d, threads: %d, epsilon: %.1e\n", maxN, threads, epsilon);

    Set<Long> seen = new HashSet<>();
    double prevValue = Double.NaN;
    boolean stopped = false;

    // Iterate n from 1 to maxN
    for (long n = 1; n <= maxN; n++) {
      double approx = integrateWithThreads(f, a, b, n, threads);

      // Show some progress for powers of 2 or first few ns
      if (n <= 16 || (n <= 1024 && (n & (n - 1)) == 0) || n % 10000 == 0) {
        System.out.printf("n=%d -> approx=%.15f\n", n, approx);
      }

      // Check repetition using epsilon
      long bucket = Math.round(approx / epsilon);
      if (seen.contains(bucket)) {
        System.out.printf("Valor repetido detectado en n=%d (approx=%.15f). Deteniendo.\n", n, approx);
        stopped = true;
        break;
      } else {
        seen.add(bucket);
      }
      prevValue = approx;
    }

    if (!stopped) {
      System.out.println("No se detectó repetición antes de maxN.");
    }
    System.out.println("Fin.");
  }
}