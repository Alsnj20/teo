package lab09.eje01;

public class Main {
    public static void main(String[] args) {
        System.out.println("PRUEBA DEL PATRON SINGLETON");

        Configuracion config1 = Configuracion.getInstancia();
        config1.mostrarConfiguracion();

        Configuracion config2 = Configuracion.getInstancia();
        System.out.println("¿Misma instancia? " + (config1 == config2));

        config1.actualizarConfiguracion("ingles", "UTC+0");
        config2.mostrarConfiguracion();
    }
}
