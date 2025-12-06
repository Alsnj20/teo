package lab09.eje02;

public class Main {

  public static void funcionA() {
    Logger.getInstance().log("Mensaje desde funcionA()");
  }

  public static void funcionB() {
    Logger.getInstance().log("Mensaje desde funcionB()");
  }

  public static void main(String[] args) {
    Logger logger = Logger.getInstance();
    logger.log("Inicio del programa");

    funcionA();
    funcionB();

    logger.log("Fin del programa");
    logger.close();

    System.out.println("Mensajes registrados en bitacora.log");
  }
}
