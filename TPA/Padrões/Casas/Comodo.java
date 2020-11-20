package casas;

public class Comodo {
    private float area;
    private String piso;

    public Comodo(float area) {
        this.area = area;
        this.piso = "simples";
    }

    public String getPiso() {
        return piso;
    }

    public void setPiso(String piso) {
        this.piso = piso;
    }

    public float getArea() {
        return area;
    }

    public void setArea(float area) {
        this.area = area;
    }
}
