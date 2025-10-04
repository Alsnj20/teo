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
}