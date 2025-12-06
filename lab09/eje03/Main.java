package lab09.eje03;

public class Main {
    public static void main(String[] args) {
        DBConnector dbConnector1 = DBConnector.getInstance();
        dbConnector1.getStatus();
        dbConnector1.connect();
        dbConnector1.getStatus();

        DBConnector dbConnector2 = DBConnector.getInstance();
        dbConnector2.disconnect();
        dbConnector2.getStatus();

        System.out.println("Are both instances the same? " + (dbConnector1 == dbConnector2));

        System.out.println("HashCode of dbConnector1: " + dbConnector1.hashCode());
        System.out.println("HashCode of dbConnector2: " + dbConnector2.hashCode());
    }
}
