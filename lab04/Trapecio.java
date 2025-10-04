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
}