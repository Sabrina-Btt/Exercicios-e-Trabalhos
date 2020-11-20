package casas;

public class Quarto extends Comodo{
    private boolean suite;

    public Quarto(float area) {
        super(area);
    }

    public boolean isSuite() {
        return suite;
    }

    public void setSuite(boolean suite) {
        this.suite = suite;
    }
}
