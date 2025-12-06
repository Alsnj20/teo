package lab09.eje03;

public class DBConnector {
    private static DBConnector instance;

    private boolean connected;

    private DBConnector() {
        this.connected = false;
        System.out.println("DatabaseConnector instance created.");
    }

    public static DBConnector getInstance() {
        if (instance == null) {
            instance = new DBConnector();
        }
        return instance;
    }

    public void connect() {
        if (!this.connected) {
            this.connected = true;
            System.out.println("Connected to the database.");
        } else {
            System.out.println("Already connected to the database.");
        }
    }

    public void disconnect() {
        if (this.connected) {
            this.connected = false;
            System.out.println("Disconnected from the database.");
        } else {
            System.out.println("No active database connection to disconnect.");
        }
    }

    public void getStatus() {
        if (this.connected) {
            System.out.println("Database is connected.");
        } else {
            System.out.println("Database is not connected.");
        }
    }
}