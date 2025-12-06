package lab09.eje05;

public class ThreadSafeDBConnector {
    private static volatile ThreadSafeDBConnector instance;

    private boolean connected;

    private ThreadSafeDBConnector() {
        this.connected = false;
        System.out.println("ThreadSafeDBConnector instance created.");
    }

    public static ThreadSafeDBConnector getInstance() {
        if (instance == null) {
            synchronized (ThreadSafeDBConnector.class) {
                if (instance == null) {
                    instance = new ThreadSafeDBConnector();
                }
            }
        }
        return instance;
    }

    public void connect() {
        if (!this.connected) {
            this.connected = true;
            System.out.println(Thread.currentThread().getName() + " is connected to the database.");
        } else {
            System.out.println(Thread.currentThread().getName() + " is already connected to the database.");
        }
    }

    public void disconnect() {
        if (this.connected) {
            this.connected = false;
            System.out.println(Thread.currentThread().getName() + " is disconnected from the database.");
        } else {
            System.out.println(Thread.currentThread().getName() + " is not connected to the database.");
        }
    }

    public void isConnected() {
        if (this.connected) {
            System.out.println(Thread.currentThread().getName() + " is connected.");
        } else {
            System.out.println(Thread.currentThread().getName() + " is not connected.");
        }
    }
}
