package lab04.java;

import java.util.*;
import java.util.concurrent.*;

public class TrapecioPool {

  public interface Function {
    double eval(double x);
  }

  public static class Quadratic implements Function {
    public double eval(double x) {
      return 2.0 * x * x + 3.0 * x + 0.5;
    }
  }

  // Callable que devuelve la suma parcial de los trapecios asignados
  public static class TrapezoidCallable implements Callable<Double> {
    private final double a;
    private final double h;
    private final long startIndex;
    private final long endIndex;
    private final Function f;

    public TrapezoidCallable(double a, double h, long startIndex, long endIndex, Function f) {
      this.a = a;
      this.h = h;
      this.startIndex = startIndex;
      this.endIndex = endIndex;
      this.f = f;
    }

    @Override
    public Double call() {
      double sum = 0.0;
      for (long i = startIndex; i < endIndex; i++) {
        double x_i = a + i * h;
        double x_next = x_i + h;
        sum += 0.5 * (f.eval(x_i) + f.eval(x_next)) * h;
      }
      return sum;
    }
  }

  public static double integrateWithPool(Function f, double a, double b, long n, int poolSize)
      throws InterruptedException, ExecutionException {
    if (n <= 0)
      return 0.0;
    double h = (b - a) / (double) n;
    int workers = (int) Math.min(poolSize, n);
    long base = n / workers;
    long rem = n % workers;

    ExecutorService executor = Executors.newFixedThreadPool(workers);
    List<Future<Double>> futures = new ArrayList<>(workers);

    long index = 0;
    for (int i = 0; i < workers; i++) {
      long take = base + (i < rem ? 1 : 0);
      long start = index;
      long end = index + take;
      futures.add(executor.submit(new TrapezoidCallable(a, h, start, end, f)));
      index = end;
    }

    double total = 0.0;
    for (Future<Double> fut : futures) {
      total += fut.get();
    }
    executor.shutdown();
    executor.awaitTermination(1, TimeUnit.MINUTES);
    return total;
  }

  private static boolean repeated(double value, Set<Long> seenHashes, double epsilon) {
    long bucket = Math.round(value / epsilon);
    if (seenHashes.contains(bucket))
      return true;
    seenHashes.add(bucket);
    return false;
  }

  public static void main(String[] args) throws InterruptedException, ExecutionException {
    double a = 2.0;
    double b = 20.0;
    long maxN = 200000L;
    int poolSize = Math.max(1, Runtime.getRuntime().availableProcessors());
    double epsilon = 1e-12;

    if (args.length >= 2) {
      a = Double.parseDouble(args[0]);
      b = Double.parseDouble(args[1]);
    }
    if (args.length >= 3) {
      maxN = Long.parseLong(args[2]);
    }
    if (args.length >= 4) {
      poolSize = Integer.parseInt(args[3]);
    }
    if (args.length >= 5) {
      epsilon = Double.parseDouble(args[4]);
    }

    Function f = new Quadratic();

    System.out.printf("Integración por trapecio (Thread Pool) sobre [%f, %f]\n", a, b);
    System.out.printf("Máx n: %d, poolSize: %d, epsilon: %.1e\n", maxN, poolSize, epsilon);

    Set<Long> seen = new HashSet<>();
    boolean stopped = false;

    for (long n = 1; n <= maxN; n++) {
      double approx = integrateWithPool(f, a, b, n, poolSize);

      if (n <= 16 || (n <= 1024 && (n & (n - 1)) == 0) || n % 10000 == 0) {
        System.out.printf("n=%d -> approx=%.15f\n", n, approx);
      }

      long bucket = Math.round(approx / epsilon);
      if (seen.contains(bucket)) {
        System.out.printf("Valor repetido detectado en n=%d (approx=%.15f). Deteniendo.\n", n, approx);
        stopped = true;
        break;
      } else {
        seen.add(bucket);
      }
    }

    if (!stopped) {
      System.out.println("No se detectó repetición antes de maxN.");
    }
    System.out.println("Fin.");
  }
}