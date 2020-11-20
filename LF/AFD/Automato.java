import java.util.ArrayList;

public class Automato {
    private int S;
    private ArrayList<Integer> F = new ArrayList<>();
    private ArrayList<Estado> estados = new ArrayList<>();

    public int getS() {
        return S;
    }

    public void setS(int s) {
        S = s;
    }

    public ArrayList<Integer> getF() { return F; }

    public void addF(int c) { F.add(c); }

    public void addE(Estado e){
        estados.add(e);
    }

    public ArrayList<Estado> getEstados() { return estados; }
}
