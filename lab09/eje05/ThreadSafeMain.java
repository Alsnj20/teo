package lab09.eje05;

public class ThreadSafeMain {
    public static void main(String[] args) {
        Runnable task = () -> {
            ThreadSafeDBConnector connection = ThreadSafeDBConnector.getInstance();
            connection.connect();
            connection.disconnect();
        };

        Thread thread1 = new Thread(task);
        Thread thread2 = new Thread(task);
        Thread thread3 = new Thread(task);

        thread1.start();
        thread2.start();
        thread3.start();
    }
}
