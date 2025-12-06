package lab09.eje01;

public class Configuracion {
    private static Configuracion instancia;
    private String idioma;
    private String zonaHoraria;

    private Configuracion() {
        this.idioma = "español";
        this.zonaHoraria = "UTC-5";
    }

    public static Configuracion getInstancia() {
        if (instancia == null) {
            instancia = new Configuracion();
        }
        return instancia;
    }

    public void mostrarConfiguracion() {
        System.out.println("Idioma: " + idioma);
        System.out.println("Zona Horaria: " + zonaHoraria);
    }

    public void actualizarConfiguracion(String idioma, String zonaHoraria) {
        if (idioma != null) {
            this.idioma = idioma;
        }
        if (zonaHoraria != null) {
            this.zonaHoraria = zonaHoraria;
        }
    }

    // Getters y Setters
    public String getIdioma() {
        return idioma;
    }

    public void setIdioma(String idioma) {
        this.idioma = idioma;
    }

    public String getZonaHoraria() {
        return zonaHoraria;
    }

    public void setZonaHoraria(String zonaHoraria) {
        this.zonaHoraria = zonaHoraria;
    }
}