package casas;

public class CasaFactory {
    public static CasaFactory cF = new CasaFactory();

    public static CasaFactory get() {
        return cF;
    }

    public Casa factory(int material, Sala sala, Cozinha cozinha){
        if(material == 1){
            return new CasaMadeira(sala, cozinha);

        }
        else if(material == 2){
            return new CasaTijolo(sala, cozinha);

        }
        else if(material == 3){
            return new CasaAco(sala, cozinha);

        }
        return null;
    }


}
