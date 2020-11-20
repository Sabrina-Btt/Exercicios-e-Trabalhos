package casas;

public class Cozinha extends Comodo{
    private String tipoPia;

    public Cozinha(float area) {
        super(area);
        tipoPia = "simples";
    }

    public String getTipoPia() {
        return tipoPia;
    }

    public void setTipoPia(String tipoPia) {
        this.tipoPia = tipoPia;
    }
    
}
