package casas;

public class Sala extends Comodo {
    private int ambientes;

    public Sala(float area) {
        super(area);
    }

    public int getAmbientes() {
        return ambientes;
    }

    public void setAmbientes(int ambientes) {
        this.ambientes = ambientes;
    }
}
