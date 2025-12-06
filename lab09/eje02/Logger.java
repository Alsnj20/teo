package lab09.eje02;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Logger {

  private static Logger instance;
  private static final Object lock = new Object();
  private PrintWriter writer;

  private Logger() {
    try {
      writer = new PrintWriter(new FileWriter("bitacora.log", true));
    } catch (IOException e) {
      System.err.println("No se pudo abrir bitacora.log: " + e.getMessage());
    }
  }

  public static Logger getInstance() {
    synchronized (lock) {
      if (instance == null) {
        instance = new Logger();
      }
      return instance;
    }
  }

  public void log(String mensaje) {
    synchronized (lock) {
      if (writer != null) {
        String hora = LocalDateTime.now().format(
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        writer.println("[" + hora + "] " + mensaje);
        writer.flush();
      }
    }
  }

  public void close() {
    synchronized (lock) {
      if (writer != null) {
        writer.close();
      }
    }
  }
}
